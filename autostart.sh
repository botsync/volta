#!/bin/bash
rossetup=/opt/ros/melodic/setup.bash
rossetup2=/home/volta/catkin_volta/devel/setup.bash
launcher="roslaunch volta_base bringup.launch"
pathfile=/home/volta
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
