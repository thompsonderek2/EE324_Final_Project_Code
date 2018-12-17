/*
 * audio_controller.c
 *
 *  Created on: Dec 13, 2018
 *      Author: jessi
 */

#include <stdio.h>
#include <unistd.h>
#include "audio_controller.h"

#define NOTE_VALUE *(uint32_t *) 0x43C00014   //note value for audio signal



/*
 *
 *     Notes:
    A3:   888    # 110 Hz
    B3:   794    # 123 Hz
    C3:   745     # 131 Hz , 8
    D3:   664     # 147 Hz , 12
    E3:   592     # 165 Hz , 16
    F3:   558     # 175 Hz , 20
    G3:   498     # 196 Hz , 24

    A4:   444      # 220 Hz , 28
    B4:   395      # 247 Hz , 32
    C4:   373      # 262 Hz , 36
    D4:   332      # 294 Hz , 40
    E4:   296      # 330 Hz , 44
    F4:   280      # 349 Hz , 48
    G4:   249      # 392 Hz , 52

    A5:   222      # 440 Hz , 56
    B5:   198      # 494 Hz , 60
    C5:   187      # 523 Hz , 64
    D5:   166      # 587 Hz , 68
    E5:   148      # 659 Hz , 72
    F5:   140      # 698 Hz , 76
    G5:   125      # 784 Hz , 80

    A6:   111      # 880 Hz , 84
    B6:   99      # 988 Hz , 88
    C6:   93      # 1047 Hz , 92
    D6:   83      # 1175 Hz , 96
    E6:   74      # 1319 Hz , 100
    F6:   71       # 1397 Hz , 104
    G6:   62       # 1568 Hz , 108

    A7:   55       # 1760 Hz , 112
    B7:   49       # 1976 Hz , 116
    C7:   47       # 2093 Hz , 120
    D7:   42       # 2349 Hz , 124
    E7:   37       # 2637 Hz , 128
    F7:   35       # 2794 Hz , 132
    G7:   31       # 3164 Hz , 136
 *
 *
 *
 */




/*##########################################################
 * int readSoundSel()
 * inputs: none
 * outputs: int sound
 * variables modified: sound
 * Register: SOUND
 * functions: none
 * Description: reads value from SOUND_SEL register
 * #########################################################*/
int readSoundSel(){
	int sound;
	sound = NOTE_VALUE;
	return sound;
}

/*##########################################################
 * void writeSoundSel(int tone)
 * inputs: int tone
 * outputs: none
 * variables modified: SOUND_SEL
 * Register: SOUND_SEL
 * functions: none
 * Description: changes value in SOUND_SEL Register
 * #########################################################*/
void writeSoundSel(int tone){
	NOTE_VALUE = tone;
}


/*##########################################################
 * void deathSound()
 * inputs: none
 * outputs: none
 * variables modified: SOUND_SEL
 * Register: SOUND_SEL
 * functions: writeSoundSel(int tone)
 * Description: plays sound sequence for losing the game.
 * Note that this takes time to complete.
 * #########################################################*/
void deathSound(){
	writeSoundSel(498); usleep(300000);
	writeSoundSel(558); usleep(300000);
	writeSoundSel(592); usleep(300000);
	writeSoundSel(745); usleep(800000);
	writeSoundSel(0); usleep(500000); // can take away if needed, for effect oooooOOOOOoooo
}

void startGameSound(){
	writeSoundSel(222); usleep(100000);
	writeSoundSel(197); usleep(100000);
	writeSoundSel(187); usleep(100000);
	writeSoundSel(166); usleep(100000);
	writeSoundSel(148); usleep(100000);
	writeSoundSel(140); usleep(250000);
	writeSoundSel(125); usleep(100000);
	writeSoundSel(111); usleep(100000);
	writeSoundSel(0);

}
