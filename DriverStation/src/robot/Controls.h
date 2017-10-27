#pragma once
#include <SFML/Window/Joystick.hpp>

#define JOY0					(0)
#define JOY1					(1)

// Control macros
#define LX						(sf::Joystick::X)
#define LY						(sf::Joystick::Y)
#define RX						(sf::Joystick::U)
#define RY						(sf::Joystick::R)
#define TG						(sf::Joystick::Z)
#define POVX					(sf::Joystick::PovX)
#define POVY					(sf::Joystick::PovY)

#define A_BUT					(0)
#define B_BUT					(1)
#define X_BUT					(2)
#define Y_BUT					(3)
#define LB						(4)
#define RB						(5)
#define BACK					(6)
#define START					(7)
#define L_CLICK					(8)
#define R_CLICK					(9)

#define RAW_AXIS(IN, AXIS)		(sf::Joystick::getAxisPosition(IN, AXIS)/100.0f)
#define DB_CONST				(0.15f)
#define DEADBAND(VAL)			((fabs(VAL) < DB_CONST)? 0.0f: VAL)
#define EXP(VAL)				(VAL*(DB_CONST*DB_CONST - VAL*VAL)/(DB_CONST*DB_CONST - 1))
#define DB_AXIS(IN, AXIS)		(DEADBAND(RAW_AXIS(IN, AXIS)))
#define EXP_AXIS(IN, AXIS)		(EXP(RAW_AXIS(IN, AXIS)))

#define GET_BUTTON(IN, BUT)		(sf::Joystick::isButtonPressed(IN, BUT))
#define TG_DB					(0.3f)
#define GET_RT(IN)		        (RAW_AXIS(IN, TG) < -TG_DB)
#define GET_LT(IN)		        (RAW_AXIS(IN, TG) > TG_DB)

// Controls
#define CTRL_TRANS_X            ( DB_AXIS(JOY0, LX))
#define CTRL_TRANS_Y            (-DB_AXIS(JOY0, LY))
#define CTRL_ROT                ( DB_AXIS(JOY0, RX))
#define CTRL_TANK_LEFT          (-DB_AXIS(JOY0, LY))
#define CTRL_TANK_RIGHT         (-DB_AXIS(JOY0, RY))

#define CTRL_GYRO_RESET         (false)//GET_BUTTON(JOY0, A_BUT))
#define CTRL_GYRO_ROT_CCW       (GET_BUTTON(JOY0, LB))
#define CTRL_GYRO_ROT_CW        (GET_BUTTON(JOY0, RB))
#define CTRL_TOGGLE_MODE        (GET_BUTTON(JOY0, START))
#define CTRL_AUTO_MODE			(false)//GET_BUTTON(JOY0, B_BUT))
#define CTRL_COMP_ON	        (GET_BUTTON(JOY0, A_BUT))
#define CTRL_COMP_OFF			(GET_BUTTON(JOY0, B_BUT))

#define CTRL_GRAB_KEY           (GET_BUTTON(JOY1, LB))
#define CTRL_MAN_SHOULDER       (-DB_AXIS(JOY1, RY))
#define CTRL_MAN_WRIST          (-DB_AXIS(JOY1, LY))
#define CTRL_STOP_HOLD          (GET_LT(JOY1))

#define CTRL_INTAKE             (GET_BUTTON(JOY1, Y_BUT))
#define CTRL_INTAKE_REV         (GET_BUTTON(JOY1, RB))
#define CTRL_DOOR_OUT           (GET_BUTTON(JOY1, B_BUT))
#define CTRL_DOOR_UP            (GET_BUTTON(JOY1, A_BUT))
#define CTRL_SCORE              (GET_BUTTON(JOY1, X_BUT))
