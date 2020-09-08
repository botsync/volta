# Volta_Rules
Create Udev Rules for device binding.

# Setup Instructions
1. For each device added,find the ATTRS{idVendor},  ATTRS{idProduct} and  ATTRS{product} using ```udevadm info -a -p $(udevadm info -q path -n <devpath>)```
2. Run the following command to create udev rules
```rosrun volta_rules create_udev_rules```
