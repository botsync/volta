#include <volta_teleoperator/ackermann_joy_teleop.h>

AckermannJoyControl::AckermannJoyControl():
    nh_("~")
{
    current_speed = 0.5;
    nh_.param("dead_man_button", dead_man_button, DEFAULT_DEAD_MAN_BUTTON);
    nh_.param("stop_button", stop_button, DEFAULT_STOP_BUTTON);
    nh_.param("e_stop_button", e_stop_button, DEFAULT_E_STOP_BUTTON);
    nh_.param("speed_increase_button", speed_increase_button, DEFAULT_SPEED_INCREASE_BUTTON);
    nh_.param("speed_decrease_button", speed_decrease_button, DEFAULT_SPEED_DECREASE_BUTTON);
    
    nh_.param("linear_speed_axis", linear_speed_axis, DEFAULT_LINEAR_SPEED_AXIS);
    nh_.param("angular_speed_axis", angular_speed_axis, DEFAULT_ANGULAR_SPEED_AXIS);
    
    nh_.param("max_linear_speed", max_linear_speed, DEAULT_MAX_LINEAR_SPEED);
    nh_.param("max_angular_speed", max_angular_speed, DEFAULT_MAX_ANGULAR_SPEED);

    nh_.param("desired_frequency", desired_frequency, DEFAULT_HZ);

    nh_.param("joy_topic", joy_topic, std::string(DEFAULT_JOY));
    nh_.param("cmd_vel_topic", cmd_vel_topic, std::string(DEFAULT_CMD));

    this->cmd_vel_pub = nh_.advertise<geometry_msgs::Twist>(this->cmd_vel_topic, 1);
    this->stop_pub = nh_.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 1);
    this->joy_sub = nh_.subscribe<sensor_msgs::Joy>(this->joy_topic, 1, &AckermannJoyControl::joyCallback, this);

    for (int i=0; i<6; i++) {
        axis_values.push_back(0.0);
    }
    for (int i=0; i<12; i++) {
        Button b;
        button_values.push_back(b);
    }
}

void AckermannJoyControl::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {
    for (int i=0; i<6; i++) {
        this->axis_values[i] = joy->axes[i];
    }
    for (int i=0; i<12; i++) {
        this->button_values[i].Press(joy->buttons[i]);
    }
}

void AckermannJoyControl::controlLoop() {
    double desired_linear_speed = 0.0;
    double desired_angular_speed = 0.0;

    geometry_msgs::Twist vel_msg;

    vel_msg.angular.x = 0.0;
    vel_msg.angular.y = 0.0;
    vel_msg.angular.z = 0.0;
    vel_msg.linear.x = 0.0;
    vel_msg.linear.y = 0.0;
    vel_msg.linear.z = 0.0;

    ros::Rate r(this->desired_frequency);

    while (ros::ok()) {
        if (this->button_values[stop_button].IsReleased()) {
            vel_msg.linear.x = 0.0;
            vel_msg.angular.z = 0.0;

            cmd_vel_pub.publish(vel_msg);

            actionlib_msgs::GoalID goal_id = actionlib_msgs::GoalID();
            stop_pub.publish(goal_id);
        } else if(this->button_values[dead_man_button].IsPressed()) {
            desired_linear_speed = max_linear_speed * current_speed * axis_values[linear_speed_axis];
            desired_angular_speed = desired_linear_speed * axis_values[angular_speed_axis];
            
            vel_msg.linear.x =  desired_linear_speed;
            vel_msg.angular.z = desired_angular_speed;

            cmd_vel_pub.publish(vel_msg);

            if (this->button_values[speed_increase_button].IsReleased()) {
                current_speed += 0.1;
                if (current_speed > 1.0)
                    current_speed = 1.0;
            } else if (this->button_values[speed_decrease_button].IsReleased()) {
                current_speed -= 0.1;
                if (current_speed < 0.0) {
                    current_speed = 0.0;
                }
            }
        } else if(this->button_values[dead_man_button].IsReleased()) {
            vel_msg.linear.x = 0.0;
            vel_msg.angular.z = 0.0;
            cmd_vel_pub.publish(vel_msg);
        }
        ros::spinOnce();
        r.sleep();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ackermann_joy_teleop");
    AckermannJoyControl joy_control;
    
    joy_control.controlLoop();   
}
