/*
Copyright (c) 2018, Botsync Pte. Ltd.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Botsync Pte. Ltd. nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

\author Botsync Pte. Ltd.
*/

#include <volta_base/volta_hardware.h>
#include <controller_manager/controller_manager.h>
#include <ros/callback_queue.h>

#include <boost/chrono.hpp>

typedef boost::chrono::steady_clock time_source;

void controlLoop(volta_base::voltaHardware &volta, controller_manager::ControllerManager &cm, time_source::time_point &last_time, ros::Time &last_time_d) {
    time_source::time_point this_time = time_source::now();
    boost::chrono::duration<double> elapsed_duration = this_time - last_time;
    ros::Duration elapsed(elapsed_duration.count());
    last_time = this_time;
    //ROS_ERROR("%lf", 1.0/ros::Duration(ros::Time::now()-last_time_d).toSec());
    last_time_d = ros::Time::now();
    volta.update_encoder_readings_to_joints();
    cm.update(ros::Time::now(), elapsed);
    volta.send_velocity_to_motors_from_joints();
}

int main(int argc, char *argv[]) {
ROS_ERROR("Start -------------------------------------------");
    ros::init(argc, argv, "volta_base");
    ros::NodeHandle nh, private_nh("~");

    double control_freq;
    private_nh.param<double>("control_frequency", control_freq, 10.0);
    volta_base::voltaHardware volta(nh, private_nh, control_freq);
    controller_manager::ControllerManager cm(&volta
);
    ros::CallbackQueue queue;
    ros::AsyncSpinner spinner(1, &queue);

    time_source::time_point last_time = time_source::now();
    ros::Time last_time_d = ros::Time::now();
    ros::TimerOptions control_timer(
    ros::Duration(1 / control_freq),
    boost::bind(controlLoop, boost::ref(volta), boost::ref(cm), boost::ref(last_time), boost::ref(last_time_d)),&queue);
    ROS_ERROR("Done");
    ros::Timer control_loop = nh.createTimer(control_timer);

    spinner.start();

    ros::spin();

    return 0;
}
