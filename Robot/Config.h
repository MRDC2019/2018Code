#ifndef CONFIG_H
#define CONFIG_H

// Pin mappings
#define GYRO_PIN      53
#define DRIVE_FL_PIN  7
#define DRIVE_BL_PIN  9
#define DRIVE_FR_PIN  2
#define DRIVE_BR_PIN  3
#define JUMP_PIN      36
#define SONIC_T_F_PIN 49
#define SONIC_E_F_PIN 49
#define SONIC_T_L_PIN 49
#define SONIC_E_L_PIN 49
#define SONIC_T_R_PIN 49
#define SONIC_E_R_PIN 49
#define SONIC_T_B_PIN 49
#define SONIC_E_B_PIN 49

#define SHOULDER_MOTOR_PIN  4
#define WRIST_MOTOR_PIN     10
#define SHOULDER_POT_PIN    7
#define WRIST_POT_PIN       1
#define KEY_GRABBER_PIN     40

#define INTAKE_PIN    5
#define SCORE_PIN     42
#define DOOR_OUT_PIN  34
#define DOOR_UP_PIN   38

#define COMMS_RESET_PIN     44
#define COMPRESSOR_PIN      32

// Comms
#define BAUD_RATE     9600
#define READ_LEN      15

#endif /* CONFIG_H */
