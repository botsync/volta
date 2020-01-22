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

