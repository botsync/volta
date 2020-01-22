#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <actionlib_msgs/GoalID.h>
#include <std_msgs/Bool.h>
#include <std_srvs/Empty.h>
#include <map>

#define DEFAULT_DEAD_MAN_BUTTON 5
#define DEFAULT_STOP_BUTTON 2
#define DEFAULT_E_STOP_BUTTON 9
#define DEFAULT_SPEED_INCREASE_BUTTON 3
#define DEFAULT_SPEED_DECREASE_BUTTON 1

#define DEFAULT_LINEAR_SPEED_AXIS 1
#define DEFAULT_ANGULAR_SPEED_AXIS 2

#define DEAULT_MAX_LINEAR_SPEED 2.0
#define DEFAULT_MAX_ANGULAR_SPEED 1.0

#define DEFAULT_JOY "/joy1"
#define DEFAULT_CMD "/joy1/cmd_vel"
#define DEFAULT_HZ 50.0

class Button {
	int iPressed;
	bool bReleased;
	
	public:
	
	Button(){
		iPressed = 0;
		bReleased = false;
	}
	//! Set the button as 'pressed'/'released'
	void Press(int value){		
		if(iPressed and !value){
			bReleased = true;
			
		}else if(bReleased and value)
			bReleased = false;
			
		iPressed = value;
			
	}
	
	int IsPressed(){
		return iPressed;
	}
	
	bool IsReleased(){
		bool b = bReleased;
		bReleased = false;
		return b;
	}
};

class AckermannJoyControl {
private:
    void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
    // void eStopCallback(const volta_msgs::EStop::ConstPtr& e_stop);

    ros::NodeHandle nh_;

    int dead_man_button, stop_button, e_stop_button, speed_increase_button, speed_decrease_button;
    int linear_speed_axis, angular_speed_axis;
    double max_linear_speed, max_angular_speed;
    double current_speed;
    double desired_frequency;

    ros::Publisher cmd_vel_pub, e_stop_pub, stop_pub;
    ros::Subscriber joy_sub;

    std::string joy_topic, cmd_vel_topic;
    std::vector<Button> button_values;
    std::vector<double> axis_values;

public: 
	AckermannJoyControl();
	void controlLoop();
};
