#!/usr/bin/python
import usb.core
import rospkg

existing_idvendor_list = []
existing_idproduct_list = []
new_idvendor_list = []
new_idproduct_list = []

def Diff(list1, list2):
    return (list(list(set(list1)-set(list2)) + list(set(list2)-set(list1))))

def add_leading_zeros(product_id):
    if(product_id != 0):
	if(len(product_id)==3):
		return ('0'+product_id)
	elif(len(product_id)==2):
		return ('00'+product_id)
	elif(len(product_id)==1):
		return ('000'+product_id)
	else:
		return product_id

raw_input("Unplug all the USB devices from the system and press 'Enter'" + '\n')
dev = usb.core.find(find_all=True)
for cfg in dev:
    existing_idvendor_list.append(str(cfg.idVendor))
    existing_idproduct_list.append(str(cfg.idProduct))

####################### To read the idproduct and idvendor for MCU #######################
raw_input("Plug MCU board and press 'Enter'")
dev = usb.core.find(find_all=True)
for cfg in dev:
    new_idvendor_list.append(str(cfg.idVendor))
    new_idproduct_list.append(str(cfg.idProduct))

MCU_idvendor = ''.join(Diff(new_idvendor_list, existing_idvendor_list))
existing_idvendor_list.append(MCU_idvendor)
if(MCU_idvendor == ""):
    MCU_idvendor = 0

MCU_idvendor = add_leading_zeros(format(int(MCU_idvendor), 'x'))
MCU_idproduct = ''.join(Diff(new_idproduct_list, existing_idproduct_list))
existing_idproduct_list.append(MCU_idproduct)
if(MCU_idproduct == ""):
    MCU_idproduct = 0

MCU_idproduct = add_leading_zeros(format(int(MCU_idproduct), 'x'))
if (MCU_idvendor == '0' or MCU_idproduct == '0'):
    print ("Not binding MCU" + '\n')
else:
    print("MCU_idvendor : " + MCU_idvendor + "," +" MCU_idproduct : " + MCU_idproduct + '\n')

####################### To read the idproduct and idvendor for rplidar #######################
raw_input("Plug rplidar and press 'Enter'")
dev = usb.core.find(find_all=True)
for cfg in dev:
    new_idvendor_list.append(str(cfg.idVendor))
    new_idproduct_list.append(str(cfg.idProduct))

rplidar_idvendor = ''.join(Diff(new_idvendor_list, existing_idvendor_list))
existing_idvendor_list.append(rplidar_idvendor)
if(rplidar_idvendor == ""):
    rplidar_idvendor = 0

rplidar_idvendor = add_leading_zeros(format(int(rplidar_idvendor), 'x'))
rplidar_idproduct = ''.join(Diff(new_idproduct_list, existing_idproduct_list))
existing_idproduct_list.append(rplidar_idproduct)
if(rplidar_idproduct == ""):
    rplidar_idproduct = 0

rplidar_idproduct = add_leading_zeros(format(int(rplidar_idproduct), 'x'))
if (rplidar_idvendor == '0' or rplidar_idproduct == '0'):
    print ("Not binding rplidar" + '\n')
else:
    print("rplidar_idvendor : " + rplidar_idvendor + "," + " rplidar_idproduct : " + rplidar_idproduct + '\n')

####################### To read the idproduct and idvendor for IMU sensor #######################
raw_input("plug imu sensor and press 'Enter'")
dev = usb.core.find(find_all=True)
for cfg in dev:
    new_idvendor_list.append(str(cfg.idVendor))
    new_idproduct_list.append(str(cfg.idProduct))

imu_idvendor = ''.join(Diff(new_idvendor_list, existing_idvendor_list))
existing_idvendor_list.append(imu_idvendor)
if(imu_idvendor == ""):
    imu_idvendor = 0

imu_idvendor = add_leading_zeros(format(int(imu_idvendor), 'x'))
imu_idproduct = ''.join(Diff(new_idproduct_list, existing_idproduct_list))
existing_idproduct_list.append(imu_idproduct)
if(imu_idproduct == ""):
    imu_idproduct = 0

imu_idproduct = add_leading_zeros(format(int(imu_idproduct), 'x'))
if (imu_idvendor == '0' or imu_idproduct == '0'):
    print ("Not binding IMU" + '\n')
else:
    print("imu_idvendor : " + imu_idvendor + "," + " imu_idproduct : " + imu_idproduct + '\n')

####################### To read the idproduct and idvendor for camera #######################
raw_input("plug camera and press 'Enter'")
dev = usb.core.find(find_all=True)
for cfg in dev:
    new_idvendor_list.append(str(cfg.idVendor))
    new_idproduct_list.append(str(cfg.idProduct))

camera_idvendor = ''.join(Diff(new_idvendor_list, existing_idvendor_list))
existing_idvendor_list.append(camera_idvendor)
if(camera_idvendor == ""):
    camera_idvendor = 0

camera_idvendor = add_leading_zeros(format(int(camera_idvendor), 'x'))
camera_idproduct = ''.join(Diff(new_idproduct_list, existing_idproduct_list))
existing_idproduct_list.append(camera_idproduct)
if(camera_idproduct == ""):
    camera_idproduct = 0

camera_idproduct = add_leading_zeros(format(int(camera_idproduct), 'x'))
if (camera_idvendor == '0' or camera_idproduct == '0'):
    print ("Not binding camera" + '\n')
else:
    print("camera_idvendor : " + camera_idvendor + "," + " camera_idproduct : " + camera_idproduct + '\n')

####################### print all the values#######################
print("MCU_idvendor : " + MCU_idvendor + "," +" MCU_idproduct : " + MCU_idproduct)
print("rplidar_idvendor : " + rplidar_idvendor + "," + " rplidar_idproduct : " + rplidar_idproduct)
print("imu_idvendor : " + imu_idvendor + "," + " imu_idproduct : " + imu_idproduct)
print("camera_idvendor : " + camera_idvendor + "," + " camera_idproduct : " + camera_idproduct)

###################### copying the data to udev rules
rospack = rospkg.RosPack()
path = rospack.get_path('volta_rules')
f= open(path + "/udev_rules.rules","w+")
f.write('KERNEL=="ttyUSB*", ATTRS{idVendor}=="'+MCU_idvendor+'", ATTRS{idProduct}=="'+MCU_idproduct+'", MODE:="0777", SYMLINK+="mcu"'+ '\n')

# For rplidar
f.write('KERNEL=="ttyUSB*", ATTRS{idVendor}=="'+rplidar_idvendor+'", ATTRS{idProduct}=="'+rplidar_idproduct+'", MODE:="0777", SYMLINK+="rplidar"'+ '\n')

# For imu
f.write('KERNEL=="ttyUSB*", ATTRS{idVendor}=="'+imu_idvendor+'", ATTRS{idProduct}=="'+imu_idproduct+'", MODE:="0777", SYMLINK+="imu"'+ '\n')

# For camera
f.write('KERNEL=="ttyUSB*", ATTRS{idVendor}=="'+camera_idvendor+'", ATTRS{idProduct}=="'+camera_idproduct+'", MODE:="0777", SYMLINK+="camera"')

f.close()
