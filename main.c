/* #######################################################################################################################################
 * Programmer: Daniel Aucoin
 * Project Name: Simon Says Game
 * Date: 11/10/2018
 * Description: 4 squares that are to light up in a given sequence. Each new level determines the number of squares to light up
 * level 1 = 1 square; level 2 = 2 squares. The previous squares are to light up each new round until the new square shows. The user
 * are then given time to match the sequence.
 * ########################################################################################################################################*/


//#include "xil_types.h"
#include <stdio.h>
#include <unistd.h>
#include "audio_controller.h"
#include "UART.h"

//Registers
#define OPEN_REG_1 *(uint32_t *) 0x43C00000   //no function
#define SQUID_PIX_Y *(uint32_t *) 0x43C00004  //location of y for squid [31:0]
#define LEVEL_NUM *(uint32_t *) 0x43C00008    //number of the level the user is on [31:0]
#define SQUID_PIX_X *(uint32_t *) 0x43C0000C  //location of x for squid [31:0]
#define OPEN_REG_2 *(uint32_t *) 0x43C00010   //no function
#define NOTE_VALUE *(uint32_t *) 0x43C00014   //note value for audio signal
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

#define BTN *(uint32_t *) 0x43C10004 // Register that determines which BTN has been pressed and when
#define UART_FIFO *(uint32_t *)0xE0001030



// Global Variables

// variables keep track of the x and y locations for a given object
// used with the PIX_Y and PIX_X Registers
//int pix_x_char = 870;
//int pix_y_char = 60;
//int pix_x_sprite1 = 870;
//int pix_y_sprite1 = 0;
int lost = 0;
// struct sprite platform1 = {800, 0, 10, 0, 0, 500, 0, 0, 20, 0, 0, 20, 0, 0};
struct sprite{
	int object_x_location;
	int object_y_location;
	int object_up_velocity;
	int object_vel_up_prev_count;
	int up_flag;
	int object_down_velocity;
	int object_vel_down_prev_count;
	int down_flag;
	int object_right_velocity;
	int object_vel_right_prev_count;
	int right_flag;
	int object_left_velocity;
	int object_vel_left_prev_count;
	int left_flag;
	int jump_timer;
	//sprite() : object_x_location(800)
	//{}

};

//functions define
//changes objects location
//void changeObjSpecs(int REG_X, int REG_Y, struct sprite choose_obj_x, struct sprite choose_obj_y);
void objectVelocityCounterUp(struct sprite *focus_obj);
void objectVelocityCounterDown(struct sprite *focus_obj);
void objectVelocityCounterRight(struct sprite *focus_obj);
void objectVelocityCounterLeft(struct sprite *focus_obj);
//void displayObjects(struct sprite *focus_obj);
void changeObjectVelocity(struct sprite *focus_obj);
void jump(struct sprite *char_obj);
void movePlatform(struct sprite *plat_obj);
//int platformDetection(struct sprite *char_obj, struct sprite *plat_obj);
int platformDetection(struct sprite *char_obj, struct sprite * plat_obj);
int incrementPlatforms =0;

char level_inc = '1'; //tracks level
int timeCount = 0;



int main()
{
	//variables
	int compare_inc = 0; //tracks which array element is being compared with user input
	int track_game = 0; //controls when to enter game logic
	int display_array_values = 1; //controls display of array
	int game_menu = 1; //controls display of menu
	int has_hit = 0; //determines when ball has hit ground to bounce until reaches its hieght
	char direction[1];
	int bounce_hieght = 100; // 100 pixels
	int object_velocity_counter = 0;

	//text placement

	// x loc, y lox, up vel, up count, up display, down vel, down count, down display, right vel, right count, right display, left vel, left count, left display
	struct sprite character = {800, 300, 100, 0, 0, 50, 0, 0, 50, 0, 0, 50, 0, 0};
//	struct sprite level = {1000, 300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	struct sprite level = {1000, 500, 10, 0, 0, 10, 0, 0, 20, 0, 0, 20, 0, 0};


	// Create an array of sprite objects for the platforms with the default initializations for each object
	struct sprite platform[6];


	for (int i =0; i<6; i++){
		platform[i].object_x_location=800;
		platform[i].object_y_location=300;
		platform[i].object_up_velocity=10;
		platform[i].object_vel_up_prev_count=0;
		platform[i].up_flag=0;
		platform[i].object_down_velocity=200;
		platform[i].object_vel_down_prev_count=0;
		platform[i].down_flag=0;
		platform[i].object_right_velocity=10;
		platform[i].object_vel_right_prev_count=0;
		platform[i].right_flag=0;
		platform[i].object_left_velocity=1;
		platform[i].object_vel_left_prev_count=0;
		platform[i].left_flag=0;
		platform[i].jump_timer=0;
	}

	SQUID_COLOR = 0xFFF; // initialize squid color to Red
	PLAT_1_COLOR = 0x00ffff;
	PLAT_2_COLOR = 0xffff00;
	PLAT_3_COLOR = 0x0000ff;
	PLAT_4_COLOR = 0xFF0000;
	PLAT_5_COLOR = 0x00ff00;
	PLAT_6_COLOR = 0xff00ff;
	LEVEL_COLOR = 0x0;

    while (1)
    {
    	platform[1].object_x_location=800;
    	platform[1].object_y_location=175;
    	platform[2].object_x_location=800;
    	platform[2].object_y_location=600;
    	platform[3].object_x_location=1000;
    	platform[3].object_y_location=325;
    	platform[4].object_x_location=600;
    	platform[4].object_y_location=475;
    	platform[5].object_x_location=1200;
    	platform[5].object_y_location=625;
    	platform[6].object_x_location=400;
    	platform[6].object_y_location=550;
    	character.object_x_location = 0;
    	character.object_y_location = 0;
    	level.object_x_location=400;
    	level.object_y_location=40;



    	PLAT_1_PIX  = platform[0].object_x_location + (platform[0].object_y_location << 16);
    	PLAT_2_PIX  = platform[1].object_x_location + (platform[1].object_y_location << 16);
    	PLAT_3_PIX  = platform[2].object_x_location + (platform[2].object_y_location << 16);
    	PLAT_4_PIX  = platform[3].object_x_location + (platform[3].object_y_location << 16);
    	PLAT_5_PIX  = platform[4].object_x_location + (platform[4].object_y_location << 16);
    	PLAT_6_PIX  = platform[5].object_x_location + (platform[5].object_y_location << 16);
    	SQUID_PIX_X = character.object_x_location;
    	SQUID_PIX_Y = character.object_y_location;
    	LEVEL_PIX = level.object_x_location + (level.object_y_location << 16);
		lost = 0;
		level_inc = '1';
		timeCount++;
		rand(timeCount);
		for(int j = 0; j < 6;j++){
			platform[j].object_down_velocity = 200;
		}


    	int buttons = BTN & 0b1111;
    	if(buttons){

        	character.object_x_location = 825;
        	character.object_y_location = 500;
        	SQUID_PIX_X = character.object_x_location;
        	SQUID_PIX_Y = character.object_y_location;
        startGameSound();
        usleep(10000);

        while(!lost){
        	// determines objects velocities
        	    	//character
//
        			if(LEVEL_NUM != level_inc && platform[0].object_down_velocity > 20){
        				for(int j = 0; j < 6;j++){
        					platform[j].object_down_velocity = platform[j].object_down_velocity - 20;
        				}

        			}
        			LEVEL_NUM = level_inc;

//        			UART_POLLING();
//        			direction[0] = UART_FIFO;

        	    	objectVelocityCounterUp(&character);
        	    	objectVelocityCounterDown(&character);
        	    	objectVelocityCounterRight(&character);
        	    	objectVelocityCounterLeft(&character);
        	    	jump(&character);

        	    	//platform1
        	    	for (int i =0; i<6; i++){
        				objectVelocityCounterUp(&platform[i]);
        				objectVelocityCounterDown(&platform[i]);
        				objectVelocityCounterRight(&platform[i]);
        				objectVelocityCounterLeft(&platform[i]);
        				//displayObjects(&character);
        	    	}

        	    	//######################## user controller logic ##############################
//        	    	for (int i = 0; i<6; i++){
        	    	    	// GO UP
        	    	//    		    			if ((BTN & 0b1) == 0b1 && character.up_flag == 1){
        	    	//    		    				if(character.object_y_location >= 24){
        	    	//    		    					//pix_y_char = pix_y_char - 1;
        	    	//    		    					character.object_y_location = character.object_y_location - 1;
        	    	//    		    				}
        	    	//    		    			}


        	    								if ((platformDetection(&character, platform)==0) || character.up_flag == 1){
        	    	    		    				if (character.jump_timer == 0 && character.up_flag == 0){
        	    	        		    				character.jump_timer = 23000;
        	    	    		    				}
        	    	    		    				else if((character.object_y_location) >= 24 && (character.up_flag ==1) && character.jump_timer !=0){
        	    										//pix_y_char = pix_y_char - 1;
        	    										character.object_y_location = character.object_y_location - 1;
        	    									}
        	    								}
        	    								 if((character.object_y_location <= 720) && (character.object_y_location >= 23) && (character.down_flag == 1) && (platformDetection(&character, platform))){
													//pix_y_char = pix_y_char + 1;
													character.object_y_location = character.object_y_location + 1;
													}
        	    	//    		    			if ((BTN & 0b1) ==0b1 ){
        	    	//    		    				if (character.jump_timer == 0){
        	    	//        		    				character.jump_timer = 100000;
        	    	//    		    				}
        	    	//    		    			}

        	    	    		    			// GO LEFT
        	    	    		    			if ((BTN & 0b1000) == 0b1000 && character.left_flag == 1){
        	    	    		    				if(character.object_x_location >= 260){
        	    	    		    					//pix_x_char = pix_x_char - 1;
        	    	    		    					character.object_x_location = character.object_x_location - 1;
        	    	    		    				}
        	    	    		    				if(character.object_y_location <= 720 && character.down_flag == 1 && (platformDetection(&character, platform))){
        	    	    		    						//pix_y_char = pix_y_char + 1;
        	    	    		    						character.object_y_location = character.object_y_location + 1;
        	    	    		    				}
        	    	    		    			}
        	    	    		    			// GO RIGHT
        	    	    		    			else if((BTN & 0b0100) == 0b0100 &&  character.right_flag == 1){
        	    	    							if(character.object_x_location <= 1474){
        	    	    								//pix_x_char = pix_x_char + 1;
        	    	    								character.object_x_location = character.object_x_location + 1;
        	    	    							}
        	    	    							if(character.object_y_location <= 720 && character.down_flag == 1 && (platformDetection(&character, platform))){
        	    	    								//pix_y_char = pix_y_char + 1;
        	    	    								character.object_y_location = character.object_y_location + 1;
        	    	    							}
        	    	    						}
        	    								// GO DOWN

//        	    							}//for loop

//        	    	/////FOR UART
//        	    	for (int i = 0; i<6; i++){
//        	    	// GO UP
//        	//    		    			if ((BTN & 0b1) == 0b1 && character.up_flag == 1){
//        	//    		    				if(character.object_y_location >= 24){
//        	//    		    					//pix_y_char = pix_y_char - 1;
//        	//    		    					character.object_y_location = character.object_y_location - 1;
//        	//    		    				}
//        	//    		    			}
//        								if (direction[0] == 'w' || character.up_flag == 1){
//        	    		    				if (character.jump_timer == 0){
//        	        		    				character.jump_timer = 10000;
//        	    		    				}
//        	    		    				else if((character.object_y_location) >= 24 && (character.up_flag ==1)){
//        										//pix_y_char = pix_y_char - 1;
//        										character.object_y_location = character.object_y_location - 1;
//        									}
//        								}
//        	//    		    			if ((BTN & 0b1) ==0b1 ){
//        	//    		    				if (character.jump_timer == 0){
//        	//        		    				character.jump_timer = 100000;
//        	//    		    				}
//        	//    		    			}
//
//        	    		    			// GO LEFT
//        	    		    			else if (direction[0] == 'a' && character.left_flag == 1){
//        	    		    				if(character.object_x_location >= 260){
//        	    		    					//pix_x_char = pix_x_char - 1;
//        	    		    					character.object_x_location = character.object_x_location - 1;
//        	    		    				}
//        	    		    				if(character.object_y_location <= 680 && character.down_flag == 1 && (platformDetection(&character, &platform[i]))){
//        	    		    						//pix_y_char = pix_y_char + 1;
//        	    		    						character.object_y_location = character.object_y_location + 4;
//        	    		    				}
//        	    		    			}
//        	    		    			// GO RIGHT
//        	    		    			else if(direction[0] == 'd' &&  character.right_flag == 1){
//        	    							if(character.object_x_location <= 1474){
//        	    								//pix_x_char = pix_x_char + 1;
//        	    								character.object_x_location = character.object_x_location + 1;
//        	    							}
//        	    							if(character.object_y_location <= 680 && character.down_flag == 1 && (platformDetection(&character, &platform[i]))){
//        	    								//pix_y_char = pix_y_char + 1;
//        	    								character.object_y_location = character.object_y_location + 4;
//        	    							}
//        	    						}
//        								// GO DOWN
//        	    		    			else if((character.object_y_location <= 680) && (character.object_y_location >= 23) && (character.down_flag == 1) && (BTN == 0) && (platformDetection(&character, &platform[i]))){
//        	    							//pix_y_char = pix_y_char + 1;
//        	    							character.object_y_location = character.object_y_location + 1;
//        	    							}
//        							}



        	    		    			//######################## platform moving down ##############################
        	    		    			//reset plateform to start from above the screen
        	//    		    			if(platform1.object_y_location > 740 && platform1.down_flag == 1){
        	//    		    				platform1.object_y_location = 25;
        	//    		    			}
        	//    		    			// constant down velocity
        	//    		    			else if(platform1.object_y_location <= 740 && platform1.down_flag == 1){
        	//    		    				platform1.object_y_location = platform1.object_y_location + 1;
        	//    		    			}
        	    		    			for (int i =0; i<6; i++){
        	    		    				movePlatform( &platform[i] );
        	    		    			}


        			//display char
        	    	SQUID_PIX_X = character.object_x_location;
        	    	SQUID_PIX_Y = character.object_y_location;

        			//display platform1
        	    	PLAT_1_PIX  = platform[0].object_x_location + (platform[0].object_y_location << 16);
        	    	PLAT_2_PIX  = platform[1].object_x_location + (platform[1].object_y_location << 16);
        	    	PLAT_3_PIX  = platform[2].object_x_location + (platform[2].object_y_location << 16);
        	    	PLAT_4_PIX  = platform[3].object_x_location + (platform[3].object_y_location << 16);
        	    	PLAT_5_PIX  = platform[4].object_x_location + (platform[4].object_y_location << 16);
        	    	PLAT_6_PIX  = platform[5].object_x_location + (platform[5].object_y_location << 16);

        	    	if(character.object_y_location >= 720){// you lose
        	    		deathSound();
        	    		lost = 1;

        	    	}

        	    	// wait before displaying master refresh rate base clock for all objects
        	    	usleep(100);
        }
    	}
    }
    return 0;
}



/*##########################################################
 * int objectVelocityCounter(int object_velocities, int object_velocity_count)
 * inputs: struct object focus_obj
 * outputs: int current_count: put into object_vel_prev_count
 * variables modified: none
 * Register: none
 * functions: none
 * Description: clk divides the count and adds onto previous count
 * #########################################################*/
void objectVelocityCounterUp(struct sprite *focus_obj){
	int obj_vel_up = focus_obj->object_up_velocity;
	int obj_vel_count = focus_obj->object_vel_up_prev_count;
	int jump_count = focus_obj->jump_timer;

	obj_vel_count++;

	focus_obj->object_vel_up_prev_count = obj_vel_count;

	if(obj_vel_count > obj_vel_up){
		//reset count value
		focus_obj->object_vel_up_prev_count = 0;
		if (jump_count != 0){
			focus_obj->up_flag = 1;
		}

	}else {

		focus_obj->up_flag = 0;

	}
}

/*##########################################################
 * int objectVelocityCounter(int object_velocities, int object_velocity_count)
 * inputs: struct object focus_obj
 * outputs: int current_count: put into object_vel_prev_count
 * variables modified: none
 * Register: none
 * functions: none
 * Description: clk divides the count and adds onto previous count
 * #########################################################*/
void objectVelocityCounterDown(struct sprite *focus_obj){
	int obj_vel_down = focus_obj->object_down_velocity;
	int obj_vel_count = focus_obj->object_vel_down_prev_count;
	int jump_count = focus_obj->jump_timer;

	obj_vel_count++;
	focus_obj->object_vel_down_prev_count = obj_vel_count;
	if(obj_vel_count > obj_vel_down ){
		//reset count value
		focus_obj->object_vel_down_prev_count = 0;
		if (jump_count == 0){
			focus_obj->down_flag = 1;
		}
	}else {
		focus_obj->down_flag = 0;
	}
}

/*##########################################################
 * int objectVelocityCounter(int object_velocities, int object_velocity_count)
 * inputs: struct object focus_obj
 * outputs: int current_count: put into object_vel_prev_count
 * variables modified: none
 * Register: none
 * functions: none
 * Description: clk divides the count and adds onto previous count
 * #########################################################*/
void objectVelocityCounterRight(struct sprite *focus_obj){
	int obj_vel_right = focus_obj->object_right_velocity;
	int obj_vel_count = focus_obj->object_vel_right_prev_count;
	obj_vel_count++;
	focus_obj->object_vel_right_prev_count = obj_vel_count;
	if(obj_vel_count > obj_vel_right){
		//reset count value
		focus_obj->object_vel_right_prev_count = 0;
		focus_obj->right_flag = 1;
	}else {
		focus_obj->right_flag = 0;
	}

}

/*##########################################################
 * int objectVelocityCounter(int object_velocities, int object_velocity_count)
 * inputs: struct object focus_obj
 * outputs: int current_count: put into object_vel_prev_count
 * variables modified: none
 * Register: none
 * functions: none
 * Description: clk divides the count and adds onto previous count
 * #########################################################*/
void objectVelocityCounterLeft(struct sprite *focus_obj){
	int obj_vel_left = focus_obj->object_left_velocity;
	int obj_vel_count = focus_obj->object_vel_left_prev_count;
	obj_vel_count++;
	focus_obj->object_vel_left_prev_count = obj_vel_count;
	if(obj_vel_count > obj_vel_left){
		//reset count value
		focus_obj->object_vel_left_prev_count = 0;
		focus_obj->left_flag = 1;
	}else {
		focus_obj->left_flag = 0;
	}
}

/*##########################################################
 * void platformDetection(struct object *char_obj, struct sprite *plat_obj)
 * inputs: struct object focus_obj
 * outputs: none
 * variables modified: struct object focus_obj
 * Register: none
 * functions: none
 * Description: changes the objects x and y values and logic to show object on screen
 * #########################################################*/
int platformDetection(struct sprite *char_obj, struct sprite * plat_obj){


        int plat1_x_loc = plat_obj[1].object_x_location;
        int plat1_y_loc = plat_obj[1].object_y_location-32;
        int plat2_x_loc = plat_obj[2].object_x_location;
        int plat2_y_loc = plat_obj[2].object_y_location-32;
        int plat3_x_loc = plat_obj[3].object_x_location;
        int plat3_y_loc = plat_obj[3].object_y_location-32;
        int plat4_x_loc = plat_obj[4].object_x_location;
        int plat4_y_loc = plat_obj[4].object_y_location-32;
        int plat5_x_loc = plat_obj[5].object_x_location;
        int plat5_y_loc = plat_obj[5].object_y_location-32;
        int plat6_x_loc = plat_obj[6].object_x_location;
        int plat6_y_loc = plat_obj[6].object_y_location-32;
        int char_x_loc = char_obj->object_x_location;
        int char_y_loc = char_obj->object_y_location+32;

        if( ((plat1_x_loc-64) <= char_x_loc) && (char_x_loc <= (plat1_x_loc + 96)) && ( (plat1_y_loc <= char_y_loc-1) && (char_y_loc <= (plat1_y_loc+20))) ||
                ((plat2_x_loc-64) <= char_x_loc) && (char_x_loc <= (plat2_x_loc + 96)) && ( (plat2_y_loc <= char_y_loc-1) && (char_y_loc <= (plat2_y_loc+20))) ||
                ((plat3_x_loc-64) <= char_x_loc) && (char_x_loc <= (plat3_x_loc + 96)) && ( (plat3_y_loc <= char_y_loc-1) && (char_y_loc <= (plat3_y_loc+20))) ||
                ((plat4_x_loc-64) <= char_x_loc) && (char_x_loc <= (plat4_x_loc + 96)) && ( (plat4_y_loc <= char_y_loc-1) && (char_y_loc <= (plat4_y_loc+20))) ||
                ((plat5_x_loc-64) <= char_x_loc) && (char_x_loc <= (plat5_x_loc + 96)) && ( (plat5_y_loc <= char_y_loc-1) && (char_y_loc <= (plat5_y_loc+20))) ||
                ((plat6_x_loc-64) <= char_x_loc) && (char_x_loc <= (plat6_x_loc + 96)) && ( (plat6_y_loc <= char_y_loc-1) && (char_y_loc <= (plat6_y_loc+20)))
        ){
            return 0;
        }
        else {
            return 1;
        }
    }


/*##########################################################
 * void jump(struct object *char_obj, struct sprite *plat_obj)
 * inputs: struct object focus_obj
 * outputs: none
 * variables modified: struct object focus_obj
 * Register: none
 * functions: none
 * Description: changes the objects x and y values and logic to show object on screen
 * #########################################################*/
void jump(struct sprite *char_obj){
	int jump_timer = char_obj->jump_timer;
	if (jump_timer != 0){
		jump_timer--;
		char_obj->jump_timer = jump_timer;
	}
}

void movePlatform(struct sprite *plat_obj){
	//reset plateform to start from above the screen
	if(plat_obj->object_y_location > 740 && plat_obj->down_flag == 1){
		plat_obj->object_y_location = 25;
		incrementPlatforms++;
		plat_obj->object_x_location = (rand() % 1100) + 260;
		if(incrementPlatforms%5 == 0 ){
			level_inc++;
		}
	}
	// constant down velocity
	else if(plat_obj->object_y_location <= 740 && plat_obj->down_flag == 1){
		plat_obj->object_y_location = plat_obj->object_y_location + 1;
	}
}

//
//
//
//
//
//
////#include "xil_types.h"
//#include <stdio.h>
//#include <unistd.h>
//
//#define OPEN_REG_1 *(uint32_t *) 0x43C00000   //no function
//#define SQUID_PIX_Y *(uint32_t *) 0x43C00004  //location of y for squid [31:0]
//#define LEVEL_NUM *(uint32_t *) 0x43C00008    //number of the level the user is on [31:0]
//#define SQUID_PIX_X *(uint32_t *) 0x43C0000C  //location of x for squid [31:0]
//#define OPEN_REG_2 *(uint32_t *) 0x43C00010   //no function
//#define NOTE_VALUE *(uint32_t *) 0x43C00014   //note value for audio signal
//#define PLAT_1_PIX *(uint32_t *) 0x43C00018   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_2_PIX *(uint32_t *) 0x43C0001C   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_3_PIX *(uint32_t *) 0x43C00020   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_4_PIX *(uint32_t *) 0x43C00024   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_5_PIX *(uint32_t *) 0x43C00028   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_6_PIX *(uint32_t *) 0x43C0002C   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_7_PIX *(uint32_t *) 0x43C00030   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_8_PIX *(uint32_t *) 0x43C00034   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_9_PIX *(uint32_t *) 0x43C00038   //platform 1 pixels y [31:16]  and x[15:0]
//#define PLAT_10_PIX *(uint32_t *) 0x43C0003C  //platform 1 pixels y [31:16]  and x[15:0]
//#define LEVEL_PIX *(uint32_t *) 0x43C00040    //word "level" pixels y [31:16] and x [15:0]
//#define SQUID_COLOR *(uint32_t *) 0x43C00044  //Red [7:0]  Green [15:8]  Blue [23:15] value for the squid
//#define PLAT_1_COLOR *(uint32_t *) 0x43C00048 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform1
//#define PLAT_2_COLOR *(uint32_t *) 0x43C0004C //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform2
//#define PLAT_3_COLOR *(uint32_t *) 0x43C00050 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform3
//#define PLAT_4_COLOR *(uint32_t *) 0x43C00054 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform4
//#define PLAT_5_COLOR *(uint32_t *) 0x43C00058 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform5
//#define PLAT_6_COLOR *(uint32_t *) 0x43C0005C //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform6
//#define PLAT_7_COLOR *(uint32_t *) 0x43C00060 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform7
//#define PLAT_8_COLOR *(uint32_t *) 0x43C00064 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform8
//#define PLAT_9_COLOR *(uint32_t *) 0x43C00068 //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform9
//#define PLAT_10_COLOR *(uint32_t *) 0x43C0006C //Red [7:0]  Green [15:8]  Blue [23:15] value for the platform10
//#define LEVEL_COLOR *(uint32_t *) 0x43C00070 //Red [7:0]  Green [15:8]  Blue [23:15] value for the word level
//
//#define BTN *(uint32_t *) 0x43C10004			// Register that determines which BTN has been pressed and when
//
///* #######################################################################################################################################
// * Programmer: Daniel Aucoin
// * Project Name: Simon Says Game
// * Date: 11/10/2018
// * Description: 4 squares that are to light up in a given sequence. Each new level determines the number of squares to light up
// * level 1 = 1 square; level 2 = 2 squares. The previous squares are to light up each new round until the new square shows. The user
// * are then given time to match the sequence.
// * ########################################################################################################################################*/
//
//
////#include "xil_types.h"
//#include <stdio.h>
//#include <unistd.h>
//#include "registers.h"
//#include "sprite.h"
//#include "audio_controller.h"
//#include "UART.h"
////Registers
////#define COLOR *(uint32_t *) 0x43C00000			// Chooses color
////#define PIX_Y *(uint32_t *) 0x43C00004			// location of y for objects
////#define CHAR_SEL *(uint32_t *) 0x43C00008		// chooses which character will be selected based from Ascii table
////#define PIX_X *(uint32_t *) 0x43C0000C			// location of x for objects
////#define OUTPUT_SEL *(uint32_t *) 0x43C00010		// chooses which object a number from 1 - 8
////#define SOUND_SEL *(uint32_t *) 0x43C00014		// chooses which tone to be played from sine rom
////#define BTN *(uint32_t *) 0x43C10004			// Register that determines which BTN has been pressed and when
////#define PIX_X1 *(uint32_t *) 0x43C00018			// location of x for platform1
////#define PIX_Y1 *(uint32_t *) 0x43C0001C			// location of y for platform1
//// Global Variables
//
//// variables keep track of the x and y locations for a given object
//// used with the PIX_Y and PIX_X Registers
//int pix_x_char = 870;
//int pix_y_char = 60;
//int pix_x_sprite1 = 870;
//int pix_y_sprite1 = 0;
//
////functions define
////changes objects location
////void changeObjSpecs(int REG_X, int REG_Y, struct sprite choose_obj_x, struct sprite choose_obj_y);
//void objectVelocityCounterUp(struct sprite *focus_obj);
//void objectVelocityCounterDown(struct sprite *focus_obj);
//void objectVelocityCounterRight(struct sprite *focus_obj);
//void objectVelocityCounterLeft(struct sprite *focus_obj);
//void displayObjects(struct sprite *focus_obj);
//void changeObjectVelocity(struct sprite *focus_obj);
//
//#define UART_FIFO *(uint32_t *)0xE0001030
//
//int main()
//{
//
//	setup_UART();
//
//	//variables
//	int level_inc = 0; //tracks level
//	int compare_inc = 0; //tracks which array element is being compared with user input
//	int track_game = 0; //controls when to enter game logic
//	int display_array_values = 1; //controls display of array
//	int game_menu = 1; //controls display of menu
//	int has_hit = 0; //determines when ball has hit ground to bounce until reaches its hieght
//	int object_hit = 0;
//
//	int bounce_hieght = 100; // 100 pixals
//	int object_velocity_counter = 0;
//	//text placement
//
//	// x loc, y lox, up vel, up count, up display, down vel, down count, down display, right vel, right count, right display, left vel, left count, left display
//	struct sprite character = {880, 200, 40, 0, 0, 300, 0, 0, 40, 0, 0, 40, 0, 0};
//	struct sprite platform1 = {800, 200, 10, 0, 0, 500, 0, 0, 20, 0, 0, 20, 0, 0};
//	struct sprite platform[0] = {800, 0, 10, 0, 0, 500, 0, 0, 20, 0, 0, 20, 0, 0}; // platform sprite [0:11] = 0 1 2 ... 11
//
//		LEVEL_COLOR = 0xFF00;
//		PLAT_1_COLOR = 0xFFff00;
//		PLAT_2_COLOR = 0x00ffff;
//		PLAT_3_COLOR = 0x0000ff;
//		PLAT_4_COLOR = 0xFF0000;
//		PLAT_5_COLOR = 0x00ff00;
//		PLAT_6_COLOR = 0xff00ff;
//		PLAT_7_COLOR = 0xFF0000;
//		PLAT_8_COLOR = 0xFF0000;
//		PLAT_9_COLOR = 0xFF0000;
//		PLAT_10_COLOR = 0xFF0000;
//		SQUID_COLOR = 0xff00ff;
//		int lose = 0;
//
//
//
////    	SQUID_PIX_X = character.object_x_location;
////    	SQUID_PIX_Y = character.object_y_location;
//
//    while (1)
//    {
//
//		//setup
//   		PLAT_1_PIX = 0x02580352;
//    	PLAT_2_PIX = 0x01900352;
//    	PLAT_3_PIX = 0x01FC041a;
//    	PLAT_4_PIX = 0x01FC028a;
//    	PLAT_5_PIX = 0x00C80514;
//    	PLAT_6_PIX = 0x00c80190;
//    	buttons = readbtn();
//
//    	//Game Play starts with any btn press
//    	if(buttons){
//        	startGameSound();
//        	//display character
//    		while(lose){ //while lose is 0, which means you are doin' okay
//
//
//
//
//
//
//    		}
//
//    	}
//
//
//
//
//		UART_POLLING();
//		direction = UART_FIFO;
//
//
//    	// determines objects velocities
//    	for(int i = 0; i < 2; i++){
//    		objectVelocityCounterUp(&platform[i]);
//    		objectVelocityCounterDown(&platform[i]);
//			objectVelocityCounterRight(&platform[i]);
//			objectVelocityCounterLeft(&platform[i]);
//    	}
//
//
//    	//character
//    	objectVelocityCounterUp(&character);
//    	objectVelocityCounterDown(&character);
//    	objectVelocityCounterRight(&character);
//    	objectVelocityCounterLeft(&character);
//    	//platform1
//    	objectVelocityCounterUp(&platform1);
//		objectVelocityCounterDown(&platform1);
//		objectVelocityCounterRight(&platform1);
//		objectVelocityCounterLeft(&platform1);
//    	//displayObjects(&character);
//
//    	//######################## user controller logic ##############################
//    						// go down
//    		    			if ((BTN == 0b0001|| BTN == 0b0010) && character.show_down == 1){
//    		    				if(character.object_y_location <= 730){
//    		    					//pix_y_char = pix_y_char + 1;
//    		    					character.object_y_location = character.object_y_location + 1;
//    		    				}
//    		    			// go up
//    		    			}
//    		    			else if (BTN == 0b0001 && character.show_up == 1){
//    		    				if(character.object_y_location >= 24){
//    		    					//pix_y_char = pix_y_char - 1;
//    		    					//character.object_y_location = character.object_y_location - 1;
//    		    					object_hit = jump(&character, 60, object_hit);
//    		    				}
//    		    			}
//    		    			// go left
//    		    			else if (BTN == 0b0100 && character.show_left == 1){
//    		    				if(character.object_x_location >= 330){
//    		    					//pix_x_char = pix_x_char - 1;
//    		    					character.object_x_location = character.object_x_location - 1;
//    		    				}
//    		    				if(character.object_y_location <= 730 && character.show_down == 1){
//    		    						//pix_y_char = pix_y_char + 1;
//    		    						character.object_y_location = character.object_y_location + 1;
//    		    				}
//    		    				//allows for moving left but also go down
//    		    				if(character.object_y_location <= 730  && character.object_y_location >= 23 && character.show_down == 1){
//    								//pix_y_char = pix_y_char + 1;
//    								character.object_y_location = character.object_y_location + 1;
//    							}
//    							if(character.object_y_location <= 730 && character.object_y_location > 310 && character.show_up== 1){
//    								//pix_y_char = pix_y_char - 1;
//    								character.object_y_location = character.object_y_location + 1;
//    							}
//
//    		    			}
//    		    			// go right
//    		    			else if(BTN == 0b1000 &&  character.show_right == 1){
//    							if(character.object_x_location <= 1534){
//    								//pix_x_char = pix_x_char + 1;
//    								character.object_x_location = character.object_x_location + 1;
//    							}
//    							if(character.object_y_location <= 730 && character.show_down == 1){
//    								//pix_y_char = pix_y_char + 1;
//    								character.object_y_location = character.object_y_location + 1;
//    							}
//    							//allows for moving right but also go down
//    							if(character.object_y_location <= 730 && character.object_y_location >= 23 && BTN == 0 && character.show_up == 1){
//    										//pix_y_char = pix_y_char + 1;
//    										character.object_y_location = character.object_y_location + 1;
//    							}
//    							if(character.object_y_location <= 730 && character.object_y_location >= 310 && character.show_down == 1){
//    								//pix_y_char = pix_y_char - 1;
//    								character.object_y_location = character.object_y_location + 1;
//    							}
//    						}
//    		    			else if(character.object_y_location == 310 && BTN == 0){
//    		    						//while(pix_y_char >= 310){
//    		    						//pix_y_char = pix_y_char;
//    		    						character.object_y_location = character.object_y_location;
//    		    						object_hit = 1;
//    		    			}
//    		    			else if(BTN == 0b0001||character.object_y_location <= 730 && character.object_y_location >= 23 && BTN == 0 && character.show_down == 1){
//    							//pix_y_char = pix_y_char + 1;
//    							character.object_y_location = character.object_y_location + 1;
//    							}
//    		    			else if(character.object_y_location >= 730){
//    		    				object_hit = 1;
//    		    			}
//
//    		    			//######################## platform moving down ##############################
//    		    			//reset plateform to start from above the screen
//    		    			if(platform1.object_y_location > 740 && platform1.show_down == 1){
//    		    				platform1.object_y_location = 25;
//    		    			}
//    		    			// constant down velocity
//    		    			else if(platform1.object_y_location <= 740 && platform1.show_down == 1){
//    		    				platform1.object_y_location = platform1.object_y_location + 1;
//    		    			}
//    		    			if(platform1.object_y_location == character.object_y_location + 16 && character.object_x_location >= platform1.object_x_location && character.object_x_location <= platform1.object_x_location + 40){
//    		    				//set character speed to platform down velocity
//    		    				character.object_down_velocity = platform1.object_down_velocity;
//    		    				object_hit = 1;
//    		    				//jump(&character, 100);
//    		    			} else
//    		    			{
//    		    				//character speed to default down velocity
//    		    				character.object_down_velocity = 10;
//    		    			}
//
//
//		//display char
//		//changeObjSpecs(PIX_X, PIX_Y, character, character);
//    	SQUID_PIX_X = character.object_x_location;
//    	SQUID_PIX_Y = character.object_y_location;
//		//display platform1
////    	PLAT_1_PIX = 0x012C0320;
////    	PLAT_2_PIX = 0x012C0330;
////    	PLAT_3_PIX = 0x013C0340;
////    	PLAT_4_PIX = 0x014C0350;
////    	PLAT_5_PIX = 0x015C0360;
////    	PLAT_6_PIX = 0x016C0370;
////    	PLAT_7_PIX = 0x017C0380;
////    	PLAT_8_PIX = 0x018C0390;
////    	PLAT_9_PIX = 0x019C0400;
////    	PLAT_10_PIX = 0x020C0410;
//
//
////    	LEVEL_PIX = 0x012C0320;
////    	PLAT_6_PIX = (platform1.object_y_location << 16) + platform1.object_x_location;
////    	PLAT_6_PIX = (character.object_y_location << 16) + character.object_x_location;
//
////    	PLAT_2_PIX =
//		//changeObjectSpecs(PIX_X1, PIX_Y1, &platform1, &platform1);
//    	// wait before displaying master refresh rate base clock for all objects
//    	usleep(100);
//    	object_velocity_counter++;
//    	if(object_velocity_counter == 5){
//    		object_velocity_counter = 0;
//    	}
//
//
//    }
//    return 0;
//}
//
///*##########################################################
// * void displayObjects(struct object *focus_obj)
// * inputs: struct object focus_obj
// * outputs: none
// * variables modified: struct object focus_obj
// * Register: none
// * functions: none
// * Description: changes the objects x and y values and logic to show object on screen
// * #########################################################*/
//void displayObjects(struct sprite *focus_obj){
//
//			//######################## user controller logic ##############################
//					// go down
//	    			if (BTN == 0b0010 && focus_obj->show_down == 1){
//	    				if(pix_y_char <= 730){
//	    					pix_y_char = pix_y_char + 1;
//	    					focus_obj->object_y_location = focus_obj->object_y_location + 1;
//	    				}
//	    			// go up
//	    			}
//
//	    			else if (BTN == 0b0001 && focus_obj->show_up == 1){
//	    				if(pix_y_char >= 24){
//	    					pix_y_char = pix_y_char - 1;
//	    				}
//	    			}
//	    			// go left
//	    			else if (BTN == 0b0100 && focus_obj->show_left == 1){
//	    				if(pix_x_char >= 330){
//	    					pix_x_char = pix_x_char - 1;
//	    				}
//	    				if(pix_y_char <= 730 && focus_obj->show_down == 1){
//	    						pix_y_char = pix_y_char + 1;
//	    				}
//	    				if(pix_y_char <= 730  && pix_y_char >= 23 && focus_obj->show_down == 1){
//							pix_y_char = pix_y_char + 1;
//						}
//						if(pix_y_char <= 730 && pix_y_char > 310 && focus_obj->show_up== 1){
//							pix_y_char = pix_y_char - 1;
//						}
//
//	    			}
//	    			// go right
//	    			else if(BTN == 0b1000 &&  focus_obj->show_right == 1){
//						if(pix_x_char <= 1534){
//							pix_x_char = pix_x_char + 1;
//						}
//						if(pix_y_char <= 730 && focus_obj->show_down == 1){
//							pix_y_char = pix_y_char + 1;
//						}
//						if(pix_y_char <= 730 && pix_y_char >= 23 && BTN == 0 && focus_obj->show_up == 1){
//									pix_y_char = pix_y_char + 1;
//						}
//						if(pix_y_char <= 730 && pix_y_char >= 310 && focus_obj->show_down == 1){
//							pix_y_char = pix_y_char - 1;
//						}
//					}
//	    			else if(pix_y_char == 310 && BTN == 0){
//	    						//while(pix_y_char >= 310){
//	    						pix_y_char = pix_y_char;
//	    			}
//	    			else if(pix_y_char <= 730 && pix_y_char >= 23 && BTN == 0 && focus_obj->show_down == 1){
//						pix_y_char = pix_y_char + 1;
//						}
//
//
//}
//

