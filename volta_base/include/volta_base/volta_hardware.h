#ifndef VOLTA_BASE_VOLTA_HARDWARE_H
#define VOLTA_BASE_VOLTA_HARDWARE_H

#include <ros/ros.h>
#include <ros/time.h>
#include "hardware_interface/joint_state_interface.h"
#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/robot_hw.h"
#include <string>
#include "sensor_msgs/JointState.h"

#include <volta_base/constants.h>


#include "std_msgs/Int16.h"
#include <volta_msgs/RPM.h>

namespace volta_base {
class voltaHardware: public hardware_interface::RobotHW {
public:
    voltaHardware(ros::NodeHandle nh, ros::NodeHandle private_nh, double target_control_freq);
	
	void rpmCallback(const volta_msgs::RPM::ConstPtr& rpmTemp);
		
	
    void update_encoder_readings_to_joints();
    void send_velocity_to_motors_from_joints();
    void register_controllers();
private:
	ros::Time t;
	uint8_t timeFlag;
	int16_t prevRPMLeft,prevRPMRight;
	int16_t	subMotorRPMRight,subMotorRPMLeft , pubMotorRPMRight,pubMotorRPMLeft;
	
	ros::Publisher rpm_pub ;
	ros::Subscriber rpm_sub ;
	
    void set_speeds(double left, double right);
    void limit_speeds(int16_t &left, int16_t &right);
    double convert_rpm_to_radians(double rpm);
    double convert_radians_to_rpm(double radians);
    
    hardware_interface::JointStateInterface joint_state_interface_;
    hardware_interface::VelocityJointInterface velocity_joint_interface_;

    double target_control_freq;
    double wheel_diameter_, max_acceleration_, max_speed_, max_rpm_;
    int baud_;
    std::string port_;
    ros::NodeHandle nh_, private_nh_;


    struct Joint {
        double position;
        double position_offset;
        double velocity;
        double effort;
        double velocity_command;

        Joint() :
            position(0),velocity(0),effort(0),velocity_command(0)
            {
            }
    } joints_[4];
};
}

#endif

