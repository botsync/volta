bool LOWBATTERY_FLAG
bool CHARGING_FLAG
bool MOTOR_ALARM_FLAG
bool BMS_ALARM_FLAG
bool HIGH_TEMP_FLAG
bool COMM_ERROR_FLAG

uint16 BMS_SOC
uint16 BMS_SOH
uint16 BMS_Voltage
int16 BMS_Current
uint16 BMS_voltageDiff
uint16 BMS_tempDiff
uint16 BMS_BCUMode
uint16 BMS_Alarm

uint16[2] M_State
uint16[2] M_Alarm
uint16[2] M_Power
uint16[2] M_Voltage
uint16[2] M_Current
uint8[2] M_Comm

float32 Relay_Temp
float32 PowerConn_Temp
float32 PreCharge_Temp
float32 Power_Supply_Temp


float32 Battery_In_Volt
float32 PRE_CHARGE_Volt
float32 HW_ESTOP_Volt
float32 SW_ESTOP_Volt

uint16[2] Motor_Alarm_Code
uint32[2] Motor_Fun_Fail

uint16[2] M_INIT
uint16[2] M_CW
uint16[2] M_CCW
uint16[2] M_STOP
uint16[2] M_BREAK
uint16[2] M_SETRPM
uint16[2] M_GETRPM
uint16[2] M_PARAM
uint16[2] M_ALARM

uint8 PRECHARGE_FUSE
uint8 MOTOR_FUSE
uint8 LED_STATE
