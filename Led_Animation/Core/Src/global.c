/*
 * global.c
 *
 *  Created on: Nov 1, 2022
 *      Author: HP PV
 */


#include "global.h"

//int status = 0;

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};

int hour = 15;
int minute = 8;
int second = 50;

void display7SEG(int num) {
	int dis_arr[10] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f };
	int bit_var, var2;

	var2 = ~dis_arr[num];
	bit_var = var2 & 0x01;
	HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, bit_var);

	bit_var = (var2>>1) & 0x01;
	HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, bit_var);

	bit_var = (var2>>2) & 0x01;
	HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, bit_var);

	bit_var = (var2>>3) & 0x01;
	HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, bit_var);

	bit_var = (var2>>4) & 0x01;
	HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, bit_var);

	bit_var = (var2>>5) & 0x01;
	HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, bit_var);

	bit_var = (var2>>6) & 0x01;
	HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, bit_var);
}

void update7SEG(int index) {
	switch(index) {
	case 0:
	// Display the first 7 SEG with led_buffer [0]
		display7SEG(led_buffer[index]);
		index_led = 1;
		HAL_GPIO_WritePin(GPIOA, en1_Pin, SET);
		HAL_GPIO_WritePin(GPIOA, en2_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en3_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en4_Pin, RESET);
		break ;
	case 1:
	 // Display the second 7 SEG with led_buffer [1]
		display7SEG(led_buffer[index]);
		index_led = 2;
		HAL_GPIO_WritePin(GPIOA, en1_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en2_Pin, SET);
		HAL_GPIO_WritePin(GPIOA, en3_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en4_Pin, RESET);
		break ;
	case 2:
	// Display the third 7 SEG with led_buffer [2]
		display7SEG(led_buffer[index]);
		index_led = 3;
		HAL_GPIO_WritePin(GPIOA, en1_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en2_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en3_Pin, SET);
		HAL_GPIO_WritePin(GPIOA, en4_Pin, RESET);
		break ;
	case 3:
	// Display the forth 7 SEG with led_buffer [3]
		display7SEG(led_buffer[index]);
		index_led = 0;
		HAL_GPIO_WritePin(GPIOA, en1_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en2_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en3_Pin, RESET);
		HAL_GPIO_WritePin(GPIOA, en4_Pin, SET);
		break ;
	default :
		break ;
	}
}

int count1 = 0;
int count2 = 0;

void updateClockBuffer() {

//	//update hour
//	if(hour >= 10)
//		led_buffer[0] = hour/10;
//	else
//		led_buffer[0] = 0;
//	led_buffer[1] = hour%10;
//
//	//update minute
//	if(minute >= 10)
//		led_buffer[2] = minute/10;
//	else
//		led_buffer[2] = 0;
//	led_buffer[3] = minute%10;

	// display traffic light 1 and led 7 segments 1
	if(count1 < RedCounter) { //red 1 first
		led_buffer[0] = (RedCounter-count1)/10;
		led_buffer[1] = (RedCounter-count1)%10;
		//update7SEG(index_led);
	}
	else {
		if(count1 < (RedCounter + GreenCounter)) { //then green 1
			led_buffer[0] = (RedCounter+GreenCounter-count1)/10;
			led_buffer[1] = (RedCounter+GreenCounter-count1)%10;
			//update7SEG(index_led);
		}
		else { //and finally yellow 1
			led_buffer[0] = (RedCounter+GreenCounter+YellowCounter-count1)/10;
			led_buffer[1] = (RedCounter+GreenCounter+YellowCounter-count1)%10;
			//update7SEG(index_led);
		}
	}
	count1++;
	if(count1 >= RedCounter+GreenCounter+YellowCounter)
		count1 = 0; //back to red 1

	// display traffic light 2 and led 7 segments 2
	if(count2 < GreenCounter) { // green 2 first
		led_buffer[2] = (GreenCounter-count2)/10;
		led_buffer[3] = (GreenCounter-count2)%10;
		//update7SEG(index_led);
	}
	else {
		if(count2 < (GreenCounter + YellowCounter)) { //then yellow 2
			led_buffer[2] = (GreenCounter+YellowCounter-count2)/10;
			led_buffer[3] = (GreenCounter+YellowCounter-count2)%10;
			//update7SEG(index_led);
		}
		else { //and finally red 2
			led_buffer[2] = (RedCounter+GreenCounter+YellowCounter-count2)/10;
			led_buffer[3] = (RedCounter+GreenCounter+YellowCounter-count2)%10;
			//update7SEG(index_led);
		}
	}
	count2++;
	if(count2 >= RedCounter+GreenCounter+YellowCounter)
		count2 = 0; //back to green 2
	//setTimer1(1000);
}
