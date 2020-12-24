/*

Copyright (c) 2020, Botsync Pte. Ltd.
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

*/

#include <volta_teleoperator/joy_teleop.h>

int main(int argc, char** argv) {
    ros::init(argc, argv, "joy_teleop_node");

    ros::NodeHandle nh;

    nh.param<int>("enable_button", enable_button, 1);
    nh.param<int>("stop_button", stop_button, 2);
    nh.param<int>("e_stop_button", e_stop_button, 3);
    nh.param<int>("linear_speed_axis", linear_speed_axis, 1);
    nh.param<int>("angular_speed_axis", angular_speed_axis, 0);

    nh.param<double>("max_linear_speed", max_linear_speed, 0.3);
    nh.param<double>("max_angular_speed", max_angular_speed, 0.3);

    nh.param<int>("enable_e_stop", enable_e_stop, 0);

    std::string cmd_vel_topic, e_stop_pub_topic, joy_topic, e_stop_sub_topic;

    nh.param<std::string>("cmd_vel_topic", cmd_vel_topic, "joy/cmd_vel");
    nh.param<std::string>("e_stop_pub_topic", e_stop_pub_topic, "/e_stop_sw_enable");

    nh.param<std::string>("joy_topic", joy_topic, "/joy");

    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>(cmd_vel_topic, 1);

    joy_subscriber = nh.subscribe(joy_topic, 1, joy_callback);

    if (enable_e_stop) {
        ROS_INFO("Enable e-stop: %d", enable_e_stop);
        e_stop_pub = nh.advertise<std_msgs::Bool>(e_stop_pub_topic, 1);
    }

    ros::Rate r(5);
    while (ros::ok()) {
        if (dead_man) {
            cmd_vel_pub.publish(cmd_to_send);
        }
        r.sleep();
        ros::spinOnce();
    }

    return 0;
    //ros::spin();
}
