/*
 * sprite.h
 *
 *  Created on: Dec 12, 2018
 *      Author: daniel.aucoin
 */

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

struct sprite{
	int object_x_location;
	int object_y_location;
	int object_up_velocity;
	int object_vel_up_prev_count;
	int show_up;
	int object_down_velocity;
	int object_vel_down_prev_count;
	int show_down;
	int object_right_velocity;
	int object_vel_right_prev_count;
	int show_right;
	int object_left_velocity;
	int object_vel_left_prev_count;
	int show_left;
};

//void changeObjSpecs(int REG_X, int REG_Y, struct sprite choose_obj_x, struct sprite choose_obj_y);
void objectVelocityCounterUp(struct sprite *focus_obj);
void objectVelocityCounterDown(struct sprite *focus_obj);
void objectVelocityCounterRight(struct sprite *focus_obj);
void objectVelocityCounterLeft(struct sprite *focus_obj);
void displayObjects(struct sprite *focus_obj);
void changeObjectVelocity(struct sprite *focus_obj);
void objectDetection(struct sprite * char_sprite, struct sprite *platform_sprite);
int jump(struct sprite *char_sprite, int jump_hieght, int on_object);
int encodeXY(struct sprite *focus_obj);
int objectDetect(struct sprite *char_sprite, int char_height, int char_width, struct sprite *platform, int platform_width);

//void setSpriteParameters(struct sprite *focus_obj, int object_x_location, int object_y_location, int object_up_velocity,
 //int object_vel_up_prev_count, int show_up, int object_down_velocity, int object_vel_down_prev_count, int show_down,
 //int object_right_velocity, int object_vel_right_prev_count, int show_right, int object_left_velocity, int object_vel_left_prev_count,
 //int show_left);

#endif /* SRC_SPRITE_H_ */
