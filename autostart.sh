#!/bin/bash
rossetup=/opt/ros/kinetic/setup.bash
rossetup2=/home/copernicus/ros_workspace/devel/setup.bash
launcher="roslaunch copernicus_base copernicus_bringup.launch"
pathfile=/home/copernicus
pathfile2=/lib/systemd/system
cat <<EOF >$pathfile/vehiclestart.sh
#!/bin/bash
bash -c "source $rossetup && source $rossetup2 && $launcher"
EOF

sudo chmod u+x $pathfile/vehiclestart.sh

cat <<EOF >$pathfile2/vehiclestart.service
[Unit]
Description=Vehicle Auto Start
After=multi-user.target

[Service]
Type=idle
ExecStart=$pathfile/vehiclestart.sh

[Install]
WantedBy=multi-user.target
EOF
sudo chmod 644 $pathfile2/vehiclestart.service
sudo systemctl daemon-reload
sudo systemctl enable vehiclestart.service
sudo systemctl start vehiclestart.service
