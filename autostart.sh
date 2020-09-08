#!/bin/bash
rossetup=/opt/ros/kinetic/setup.bash
rossetup2=/home/volta2/catkin_ws/devel/setup.bash
launcher="roslaunch volta_base volta_bringup.launch"
pathfile=/home/volta2
pathfile2=/lib/systemd/system
cat <<EOF >$pathfile/volta_start.sh
#!/bin/bash
bash -c "source $rossetup && source $rossetup2 && $launcher"
EOF

sudo chmod u+x $pathfile/volta_start.sh

cat <<EOF >$pathfile2/volta_start.service
[Unit]
Description=Vehicle Auto Start
After=multi-user.target

[Service]
Type=idle
ExecStart=$pathfile/volta_start.sh

[Install]
WantedBy=multi-user.target
EOF
sudo chmod 644 $pathfile2/volta_start.service
sudo systemctl daemon-reload
sudo systemctl enable volta_start.service
sudo systemctl start volta_start.service
