/*
 * fsm_manual.c
 *
 *  Created on: Nov 1, 2022
 *      Author: HP PV
 */

#include "fsm_manual.h"

int RedCounter = 5;
int YellowCounter = 2;
int GreenCounter = 3;

void fsm_manual_run(){
	switch(status){
	case MODE2:
		clearTimer2();
		clearTimer3();
		clearTimer4();
		HAL_GPIO_WritePin(yellow1_GPIO_Port, yellow1_Pin, 1);
		HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, 1);
		HAL_GPIO_WritePin(yellow2_GPIO_Port, yellow2_Pin, 1);
		HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, 1);

		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(red1_GPIO_Port, red1_Pin);
			HAL_GPIO_TogglePin(red2_GPIO_Port, red2_Pin);
			setTimer1(500);
		}

		if(timer5_flag == 1) {
			led_buffer[0] = 0;
			led_buffer[1] = 2;
			led_buffer[2] = RedCounter/10;
			led_buffer[3] = RedCounter%10;
			update7SEG(index_led);
			setTimer5(125);
		}

		if(isButton1Pressed() == 1){
			status = MODE3;
		}

		if(isButton2Pressed() == 1){
			status = RED_INCREASE;
		}

		if(isButton3Pressed() == 1){};
		break;
	case RED_INCREASE:
		clearTimer2();
		clearTimer3();
		clearTimer4();
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(red1_GPIO_Port, red1_Pin);
			HAL_GPIO_TogglePin(red2_GPIO_Port, red2_Pin);
			setTimer1(500);
		}

		if(timer5_flag == 1) {
			led_buffer[0] = 0;
			led_buffer[1] = 2;
			led_buffer[2] = RedCounter/10;
			led_buffer[3] = RedCounter%10;
			update7SEG(index_led);
			setTimer5(125);
		}

		if(isButton2Pressed() == 1){
			if(RedCounter >= 99) {
				RedCounter = 1;
			}
			else
				RedCounter++;
		}

		if(isButton1Pressed() == 1){};

		if(RedCounter > YellowCounter){
			if(isButton3Pressed() == 1){
				GreenCounter = RedCounter - YellowCounter;
				status = MODE2;
			}
		} else
			if(isButton3Pressed() == 1){};
		break;
	case MODE3:
		clearTimer2();
		clearTimer3();
		clearTimer4();
		HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, 1);
		HAL_GPIO_WritePin(green1_GPIO_Port, green1_Pin, 1);
		HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, 1);
		HAL_GPIO_WritePin(green2_GPIO_Port, green2_Pin, 1);

		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(yellow1_GPIO_Port, yellow1_Pin);
			HAL_GPIO_TogglePin(yellow2_GPIO_Port, yellow2_Pin);
			setTimer1(500);
		}

		if(timer5_flag == 1) {
			led_buffer[0] = 0;
			led_buffer[1] = 3;
			led_buffer[2] = YellowCounter/10;
			led_buffer[3] = YellowCounter%10;
			update7SEG(index_led);
			setTimer5(125);
		}

		if(isButton1Pressed() == 1){
			status = MODE4;
		}

		if(isButton2Pressed() == 1){
			status = YELLOW_INCREASE;
		}

		if(isButton3Pressed() == 1){};
		break;
	case YELLOW_INCREASE:
		clearTimer2();
		clearTimer3();
		clearTimer4();
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(yellow1_GPIO_Port, yellow1_Pin);
			HAL_GPIO_TogglePin(yellow2_GPIO_Port, yellow2_Pin);
			setTimer1(500);
		}

		if(timer5_flag == 1) {
			led_buffer[0] = 0;
			led_buffer[1] = 3;
			led_buffer[2] = YellowCounter/10;
			led_buffer[3] = YellowCounter%10;
			update7SEG(index_led);
			setTimer5(125);
		}

		if(isButton2Pressed() == 1){
			if(YellowCounter >= 5)
				YellowCounter = 1;
			else
				YellowCounter++;
		}

		if(isButton1Pressed() == 1){};

		if(RedCounter > YellowCounter){
			if(isButton3Pressed() == 1){
				GreenCounter = RedCounter - YellowCounter;
				status = MODE3;
			}
		} else
			if(isButton3Pressed() == 1){};
		break;
	case MODE4:
		clearTimer2();
		clearTimer3();
		clearTimer4();
		HAL_GPIO_WritePin(red1_GPIO_Port, red1_Pin, 1);
		HAL_GPIO_WritePin(yellow1_GPIO_Port, yellow1_Pin, 1);
		HAL_GPIO_WritePin(red2_GPIO_Port, red2_Pin, 1);
		HAL_GPIO_WritePin(yellow2_GPIO_Port, yellow2_Pin, 1);

		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
			HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
			setTimer1(500);
		}

		if(timer5_flag == 1) {
			led_buffer[0] = 0;
			led_buffer[1] = 4;
			led_buffer[2] = GreenCounter/10;
			led_buffer[3] = GreenCounter%10;
			update7SEG(index_led);
			setTimer5(125);
		}
//
//		clearTimer2();
//		clearTimer3();
//		clearTimer4();

		if(isButton1Pressed() == 1){
			status = MODE1;
			clearTimer2();
			clearTimer3();
			clearTimer4();
			count1 = 0;
			count2 = 0;
			timer2_flag = 1;
			timer3_flag = 1;
			timer4_flag = 1;
		}

		if(isButton2Pressed() == 1){
			status = GREEN_INCREASE;
		}

		if(isButton3Pressed() == 1){};
		break;
	case GREEN_INCREASE:
		clearTimer2();
		clearTimer3();
		clearTimer4();
		if(timer1_flag == 1){
			HAL_GPIO_TogglePin(green1_GPIO_Port, green1_Pin);
			HAL_GPIO_TogglePin(green2_GPIO_Port, green2_Pin);
			setTimer1(500);
		}

		if(timer5_flag == 1) {
			led_buffer[0] = 0;
			led_buffer[1] = 4;
			led_buffer[2] = GreenCounter/10;
			led_buffer[3] = GreenCounter%10;
			update7SEG(index_led);
			setTimer5(125);
		}

		if(isButton2Pressed() == 1){
			if(GreenCounter >= 99)
				GreenCounter = 1;
			else
				GreenCounter++;
		}

		if(isButton1Pressed() == 1){};

		if(GreenCounter + YellowCounter < 100 && GreenCounter > YellowCounter){
			if(isButton3Pressed() == 1){
				RedCounter = GreenCounter + YellowCounter;
				status = MODE4;
			}
		} else
			if(isButton3Pressed() == 1){};
		break;
	default:
		break;
	}
}
