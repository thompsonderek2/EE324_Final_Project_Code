
/*
 * registers.h
 * Created on: Dec 11, 2018
 *  Author: Daniel Aucoin
 *  Description: Includes all the function to read and write from the registers
 */
/*
#define COLOR *(uint32_t *) 0x43C00000			// Chooses color
#define PIX_Y *(uint32_t *) 0x43C00004			// location of y for objects
#define CHAR_SEL *(uint32_t *) 0x43C00008		// chooses which character will be selected based from Ascii table
#define PIX_X *(uint32_t *) 0x43C0000C			// location of x for objects
#define OUTPUT_SEL *(uint32_t *) 0x43C00010		// chooses which object a number from 1 - 8
#define SOUND_SEL *(uint32_t *) 0x43C00014		// chooses which tone to be played from sine rom
#define BTN *(uint32_t *) 0x43C10004			// Register that determines which BTN has been pressed and when
#define PIX_X1 *(uint32_t *) 0x43C00018			// location of x for platform1
#define PIX_Y1 *(uint32_t *) 0x43C0001C			// location of y for platform1
*/

// Global Variables
#ifndef SRC_REGISTERS_H_
#define SRC_REGISTERS_H_

int readColor ();
void writeColor (int color);
int readPixY();
void writePixY(int pix_y);
int  readPixX();
void writePixX(int pix_x);
int readSoundSel();
void writeSoundSel(int tone);
int readBtn();
int readPixX1();
void writePixX1(int pix_x1);
int readPixY1();
void writePixY1(int pix_y1);

#endif /* SRC_REGISTERS_H_ */

