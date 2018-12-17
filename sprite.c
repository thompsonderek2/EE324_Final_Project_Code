///*
// * sprite.c
// *
// *  Created on: Dec 12, 2018
// *      Author: jessi
// */
//
//
////#include "registers.h"
//#include "sprite.h"
//#include <stdio.h>
//#include <unistd.h>
//
//// variables
//struct sprite platform[12]; // [0] = character sprite and [1:12] = platforms
//struct sprite character;
//
//
///*##########################################################
// * int objectDetect(struct sprite *char_sprite, int char_width, struct sprite *platform, int platform_width);
// * struct sprite *char_sprite, int char_width, struct sprite *platform, int platform_width
// * outputs: none
// * variables modified: none
// * Register: none
// * functions: none
// * Description: send back on_object. A variable Object_hit will need to receive this value in game logic.
// * #########################################################*/
//int objectDetect(struct sprite *char_sprite, int char_height, int char_width, struct sprite *platform, int platform_width){
//	int on_object = 0;
//	if(platform->object_y_location == platform->object_y_location + char_height && char_sprite->object_x_location >= platform->object_x_location - char_width && char_sprite->object_x_location <= platform->object_x_location){
//		//set character speed to platform down velocity
//		char_sprite->object_down_velocity = platform->object_down_velocity;
//		 on_object = 1;
//		//jump(&character, 100);
//	} else
//	{
//		//character speed to default down velocity
//		char_sprite->object_down_velocity = 10;
//	}
//	return on_object;
//}
//
///*##########################################################
// * void encodeXY(int x_value,int y_value, struct sprite *focus_obj)
// * int x_value,int y_value, struct sprite *focus_obj
// * outputs: x and y encoded value: xy_encoded_value
// * variables modified: none
// * Register: none
// * functions: none
// * Description:  encodes the object x and y value to be sent off to its specific register for verilog
// * #########################################################*/
//int encodeXY(struct sprite *focus_obj){
//	int xy_encoded_value = 0;
//	xy_encoded_value = (focus_obj->object_y_location << 16); // y value shifted 16 places in 32 bit value uppper 16 bits
//	xy_encoded_value = xy_encoded_value + focus_obj->object_x_location; // adds on the lower 16 bits as x value
//	return xy_encoded_value;
//}
//
//
///*##########################################################
// * void jump(struct sprite *char_sprite, int jump_hieght)
// * inputs: struct sprite *char_sprite, int jump_hieght, nt on_object
// * outputs: returns 0
// * variables modified: none
// * Register: PIX_Y, PIX_X
// * functions: none
// * Description: makes character jump up certain amount. on_object is a flag that will need to be set in game logic with some variable (set when object is on an object).
// * The variable that is used to keep track of on_object will need to be set to the return value from this function.
// * #########################################################*/
//int jump(struct sprite *char_sprite, int jump_hieght, int on_object){
//	//character jump 40 pixals (put this into function);
//	if(on_object == 1){
//		for(int i = 0; i < jump_hieght; i++){
//			// jump certain amount
//				char_sprite->object_y_location--;
//			usleep(100);
//		}
//	}
//	return 0;
//}
//
///*##########################################################
// * void objectDetection(struct sprite * char_sprite, struct sprite *platform_sprite)
// * inputs: struct sprite * char_sprite, struct sprite *platform_sprite
// * outputs: none
// * variables modified: none
// * Register: PIX_Y, PIX_X, PIX_X1, PIX_Y1
// * functions: none
// * Description: determines object locations and when to show on screen also detects when objectes hit
// * #########################################################*/
//void objectDetection(struct sprite * char_sprite, struct sprite *platform_sprite){
//
//}
//
///*##########################################################
// * void changeObjSpecs(int choose_obj_x, int choose_obj_y)
// * inputs: int choose_obj_x, int choose_obj_y
// * outputs: none
// * variables modified: none
// * Register: PIX_Y, PIX_X
// * functions: none
// * Description: Changes Register values to current x and y location
// * #########################################################*/
///*
//void changeObjSpecs(int REG_X, int REG_Y,struct sprite choose_obj_x, struct sprite choose_obj_y)
//{
//	REG_Y = choose_obj_y.object_y_location;
//	REG_X = choose_obj_x.object_x_location;
//}
//*/
///*##########################################################
// * int objectVelocityCounter(int object_velocities, int object_velocity_count)
// * inputs: struct object focus_obj
// * outputs: int current_count: put into object_vel_prev_count
// * variables modified: none
// * Register: none
// * functions: none
// * Description: clk divides the count and adds onto previous count
// * #########################################################*/
//void objectVelocityCounterUp(struct sprite *focus_obj){
//	int obj_vel_up = focus_obj->object_up_velocity;
//	int obj_vel_count = focus_obj->object_vel_up_prev_count;
//	obj_vel_count++;
//	focus_obj->object_vel_up_prev_count = obj_vel_count;
//	if(obj_vel_count > obj_vel_up){
//		//reset count value
//		focus_obj->object_vel_up_prev_count = 0;
//		focus_obj->show_up = 1;
//	}else {
//		focus_obj->show_up = 0;
//	}
//
//}
//
///*##########################################################
// * int objectVelocityCounter(int object_velocities, int object_velocity_count)
// * inputs: struct object focus_obj
// * outputs: int current_count: put into object_vel_prev_count
// * variables modified: none
// * Register: none
// * functions: none
// * Description: clk divides the count and adds onto previous count
// * #########################################################*/
//void objectVelocityCounterDown(struct sprite *focus_obj){
//	int obj_vel_down = focus_obj->object_down_velocity;
//	int obj_vel_count = focus_obj->object_vel_down_prev_count;
//	obj_vel_count++;
//	focus_obj->object_vel_down_prev_count = obj_vel_count;
//	if(obj_vel_count > obj_vel_down){
//		//reset count value
//		focus_obj->object_vel_down_prev_count = 0;
//		focus_obj->show_down = 1;
//	}else {
//		focus_obj->show_down = 0;
//	}
//
//}
//
///*##########################################################
// * int objectVelocityCounter(int object_velocities, int object_velocity_count)
// * inputs: struct object focus_obj
// * outputs: int current_count: put into object_vel_prev_count
// * variables modified: none
// * Register: none
// * functions: none
// * Description: clk divides the count and adds onto previous count
// * #########################################################*/
//void objectVelocityCounterRight(struct sprite *focus_obj){
//	int obj_vel_right = focus_obj->object_right_velocity;
//	int obj_vel_count = focus_obj->object_vel_right_prev_count;
//	obj_vel_count++;
//	focus_obj->object_vel_right_prev_count = obj_vel_count;
//	if(obj_vel_count > obj_vel_right){
//		//reset count value
//		focus_obj->object_vel_right_prev_count = 0;
//		focus_obj->show_right = 1;
//	}else {
//		focus_obj->show_right = 0;
//	}
//
//}
//
///*##########################################################
// * int objectVelocityCounter(int object_velocities, int object_velocity_count)
// * inputs: struct object focus_obj
// * outputs: int current_count: put into object_vel_prev_count
// * variables modified: none
// * Register: none
// * functions: none
// * Description: clk divides the count and adds onto previous count
// * #########################################################*/
//void objectVelocityCounterLeft(struct sprite *focus_obj){
//	int obj_vel_left = focus_obj->object_left_velocity;
//	int obj_vel_count = focus_obj->object_vel_left_prev_count;
//	obj_vel_count++;
//	focus_obj->object_vel_left_prev_count = obj_vel_count;
//	if(obj_vel_count > obj_vel_left){
//		//reset count value
//		focus_obj->object_vel_left_prev_count = 0;
//		focus_obj->show_left = 1;
//	}else {
//		focus_obj->show_left = 0;
//	}
//
//}
