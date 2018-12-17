/*
 * registers.c
 *
 *  Created on: Dec 12, 2018
 *      Author: jessi
 */


/*
 * registers.c
 *
 *  Created on: Dec 11, 2018
 *      Author: Danie
 */

#include <stdio.h>
#include <unistd.h>
#include "registers.h"

//Registers
//#define COLOR *(uint32_t *) 0x43C00000			// Chooses color
//#define PIX_Y *(uint32_t *) 0x43C00004			// location of y for objects
//#define CHAR_SEL *(uint32_t *) 0x43C00008		// chooses which character will be selected based from Ascii table
//#define PIX_X *(uint32_t *) 0x43C0000C			// location of x for objects
//#define OUTPUT_SEL *(uint32_t *) 0x43C00010		// chooses which object a number from 1 - 8
//#define SOUND_SEL *(uint32_t *) 0x43C00014		// chooses which tone to be played from sine rom
//#define BTN *(uint32_t *) 0x43C10004			// Register that determines which BTN has been pressed and when
//#define PIX_X1 *(uint32_t *) 0x43C00018			// location of x for platform1
//#define PIX_Y1 *(uint32_t *) 0x43C0001C			// location of y for platform1

#define OPEN_REG_1 *(uint32_t *) 0x43C00000   //no function
#define SQUID_PIX_Y *(uint32_t *) 0x43C00004  //location of y for squid [31:0]
#define LEVEL_NUM *(uint32_t *) 0x43C00008    //number of the level the user is on [31:0]
#define SQUID_PIX_X *(uint32_t *) 0x43C0000C  //location of x for squid [31:0]
#define OPEN_REG_2 *(uint32_t *) 0x43C00010   //no function
#define PLAT_1_PIX *(uint32_t *) 0x43C00018   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_2_PIX *(uint32_t *) 0x43C0001C   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_3_PIX *(uint32_t *) 0x43C00020   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_4_PIX *(uint32_t *) 0x43C00024   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_5_PIX *(uint32_t *) 0x43C00028   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_6_PIX *(uint32_t *) 0x43C0002C   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_7_PIX *(uint32_t *) 0x43C00030   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_8_PIX *(uint32_t *) 0x43C00034   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_9_PIX *(uint32_t *) 0x43C00038   //platform 1 pixels y [31:16]  and x[15:0]
#define PLAT_10_PIX *(uint32_t *) 0x43C0003C  //platform 1 pixels y [31:16]  and x[15:0]
#define LEVEL_PIX *(uint32_t *) 0x43C00040    //word "level" pixels y [31:16] and x [15:0]
#define SQUID_COLOR *(uint32_t *) 0x43C00044  //Red [7:0]  Green [15:8]  Blue [23:15] value for the squid
#define PLAT_1_COLOR *(uint32_t *) 0x43C00048 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform1
#define PLAT_2_COLOR *(uint32_t *) 0x43C0004C //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform2
#define PLAT_3_COLOR *(uint32_t *) 0x43C00050 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform3
#define PLAT_4_COLOR *(uint32_t *) 0x43C00054 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform4
#define PLAT_5_COLOR *(uint32_t *) 0x43C00058 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform5
#define PLAT_6_COLOR *(uint32_t *) 0x43C0005C //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform6
#define PLAT_7_COLOR *(uint32_t *) 0x43C00060 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform7
#define PLAT_8_COLOR *(uint32_t *) 0x43C00064 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform8
#define PLAT_9_COLOR *(uint32_t *) 0x43C00068 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform9
#define PLAT_10_COLOR *(uint32_t *) 0x43C0006C //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform10
#define LEVEL_COLOR *(uint32_t *) 0x43C00070 //Red [7:0]  Green [15:8]  Blue [23:15] value for the word level

#define BTN *(uint32_t *) 0x43C10004			// Register that determines which BTN has been pressed and when
//#########################Function Definitions###########################

/*##########################################################
 * int readColor()
 * inputs: none
 * outputs: outputs value in COLOR Register
 * variables modified: none
 * Register: COLOR
 * functions: none
 * Description: outputs value in COLOR Register
 * #########################################################*/
//int readColor(){
//	int color;
//	color = COLOR;
//	return color;
//}

/*##########################################################
 * int void writeColor (int color);
 * inputs: int color
 * outputs: none
 * variables modified: COLOR
 * Register: COLOR
 * functions: none
 * Description: changes value in COLOR Register
 * #########################################################*/
//void writeColor (int color){
//	COLOR = color;
//}

/*##########################################################
 *int readPixY();
 * inputs: none
 * outputs: PIX_Y value
 * variables modified: none
 * Register: PIX_Y
 * functions: none
 * Description: returns the value in PIX_Y
 * #########################################################*/
//int readPixY(){
//	int pix_y;
//	pix_y = PIX_Y;
//	return pix_y;
//}

/*##########################################################
 * void writePixY(int pix_y)
 * inputs: int pix_y
 * outputs: none
 * variables modified: PIX_Y
 * Register: PIX_Y
 * functions: none
 * Description: changes value in PIX_Y
 * #########################################################*/
//void writePixY(int pix_y){
//	PIX_Y = pix_y;
//}

/*##########################################################
 * int  readPixX();
 * inputs: none
 * outputs: PIX_X value
 * variables modified: none
 * Register: PIX_X
 * functions: none
 * Description: reads value from PIX_X
 * #########################################################*/
//int  readPixX(){
//	int pix_x;
//	pix_x = PIX_X;
//	return pix_x;
//}

/*##########################################################
 * void writePixX(int pix_x);
 * inputs: int pix_x
 * outputs: none
 * variables modified: PIX_X
 * Register: PIX_X
 * functions: none
 * Description: changes value in PIX_X
 * #########################################################*/
//void writePixX(int pix_x){
//	PIX_X = pix_x;
//}

/*##########################################################
 * int readSoundSel()
 * inputs: none
 * outputs: int sound
 * variables modified: sound
 * Register: SOUND
 * functions: none
 * Description: reads value from SOUND_SEL register
 * #########################################################*/
//int readSoundSel(){
//	int sound;
//	sound = SOUND_SEL;
//	return sound;
//}
//
///*##########################################################
// * void writeSoundSel(int tone)
// * inputs: int tone
// * outputs: none
// * variables modified: SOUND_SEL
// * Register: SOUND_SEL
// * functions: none
// * Description: changes value in SOUND_SEL Register
// * #########################################################*/
//void writeSoundSel(int tone){
//	SOUND_SEL = tone;
//}

/*##########################################################
 * int readBtn()
 * inputs: none
 * outputs: int btn
 * variables modified: none
 * Register: BTN
 * functions: none
 * Description: gets value from BTN Register
 * #########################################################*/
int readBtn(){
	int btn;
	btn = BTN;
	return btn;
}

/*##########################################################
 * int readPixX1
 * inputs: none
 * outputs: pix_x1
 * variables modified: pix_x1
 * Register: PIX_X1
 * functions: none
 * Description: reads the value from PIX_X1 Register
 * #########################################################*/
//int readPixX1(){
//	int pix_x1;
//	pix_x1 = PIX_X1;
//	return pix_x1;
//}

/*##########################################################
 * void writePixX1(int pix_x1)
 * inputs: int pix_x1
 * outputs: none
 * variables modified: PIX_X1
 * Register: PIX_X1
 * functions: none
 * Description: changes value in PIX_X1 Register
 * #########################################################*/
//void writePixX1(int pix_x1){
//	PIX_X1 = pix_x1;
//}

/*##########################################################
 * int readPixY1()
 * inputs: none
 * outputs: int pix_y1
 * variables modified: pix_y1
 * Register: PIX_Y1
 * functions: none
 * Description: reads the value in PIX_Y1 Register
 * #########################################################*/
//int readPixY1(){
//	int pix_y1 = PIX_Y1;
//	return pix_y1;
//}

/*##########################################################
 * void writePixY1(int pix_y1)
 * inputs: int pix_y1
 * outputs: none
 * variables modified: int pix_y1
 * Register: PIX_Y1
 * functions: none
 * Description: writes a new value in PIX_Y1
 * #########################################################*/
//void writePixY1(int pix_y1){
//	PIX_Y1 = pix_y1;
//}
