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

void joy_callback(const sensor_msgs::Joy::ConstPtr& joy) {
    geometry_msgs::Twist cmd;

    if (enable_e_stop && joy->buttons[e_stop_button] && !e_stop_status) {
        std_msgs::Bool e_stop_msg;

        e_stop_msg.data = true;
        e_stop_status = true;

        // Publish 0 velocity
        cmd.linear.x = 0.0;
        cmd.linear.y = 0.0;
        cmd.linear.z = 0.0;
        cmd.angular.x = 0.0;
        cmd.angular.y = 0.0;
        cmd.angular.z = 0.0;

        e_stop_pub.publish(e_stop_msg);
    } else if (enable_e_stop && joy->buttons[e_stop_button] && e_stop_status) {
        std_msgs::Bool e_stop_msg;

        e_stop_msg.data = false;
        e_stop_status = false;

        // Publish 0 velocity
        cmd.linear.x = 0.0;
        cmd.linear.y = 0.0;
        cmd.linear.z = 0.0;
        cmd.angular.x = 0.0;
        cmd.angular.y = 0.0;
        cmd.angular.z = 0.0;

        e_stop_pub.publish(e_stop_msg);
    } else if (joy->buttons[stop_button]) {
        // Publish 0 velocity
        cmd.linear.x = 0.0;
        cmd.linear.y = 0.0;
        cmd.linear.z = 0.0;
        cmd.angular.x = 0.0;
        cmd.angular.y = 0.0;
        cmd.angular.z = 0.0;

    } else if (joy->buttons[enable_button]) {
        cmd.linear.x = max_linear_speed * joy->axes[linear_speed_axis];
        cmd.linear.y = 0.0;
        cmd.linear.z = 0.0;
        cmd.angular.x = 0.0;
        cmd.angular.y = 0.0;
        cmd.angular.z = max_angular_speed * joy->axes[angular_speed_axis];
	dead_man = true;
	cmd_to_send = cmd;

    } else {
        cmd.linear.x = 0.0;
        cmd.linear.y = 0.0;
        cmd.linear.z = 0.0;
        cmd.angular.x = 0.0;
        cmd.angular.y = 0.0;
        cmd.angular.z = 0.0;
	dead_man = false;
    }

    cmd_vel_pub.publish(cmd);
}
