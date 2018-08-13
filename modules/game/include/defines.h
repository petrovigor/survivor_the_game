#if NEW_GEN

#pragma once

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define WINDOW_CLASS	L"SurvivorWindowClass"
#define WINDOW_NAME		L"WindowName"

#endif //__DEFINES_H__

#else

#ifndef __DEFINES_H
#define __DEFINES_H

#define CLASS_NAME L"className"
#define FPS 80
#define SLEEP_MS 1000/FPS

#define RESOLUTION_X 1024//640
#define RESOLUTION_Y 768//480
#define CENTER_X RESOLUTION_X/2
#define CENTER_Y RESOLUTION_Y/2

#define DEBUGVAR_INTERSECTS_COUNT_MAX 40

#define CAMERA_DISTANCE_RATE 3.0
#define ATTACH_CAMERA_TO_CURSOR true
// true - attach to cursor
// false - attach to player

#define DEBUGVAR_INCLUDE_ENEMIES true
#define DEBUGVAR_SHOW_SHADOWS true//true //3d imitation
#define DEBUGVAR_INCLUDE_BLOCKS true
#define DEBUGVAR_INCLUDE_ROADS true//false
#define DEBUGVAR_INVULNERABLE_ENEMIES false
#define DEBUGVAR_INCLUDE_ENEMY_MULTIPLIER true //!
#define DEBUGVAR_ALLOW_INFINITE_MAP true
#define DEBUGVAR_ALLOW_ENEMIES_SEE_EACH_OTHER false//true
//#define DEBUGVAR_ALLOW_BOT_WAY_SEARCHING true
#define DEBUGVAR_INCLUDE_SHELLS false//true
#define DEBUGVAR_INCLUDE_ENEMIES_VISION false //motion coords
#define DEBUGVAR_ALLOW_SHOT_PRECISION true
#define DEBUGVAR_ALPHA_ROOFS false//true // my coding sucks
#define DEBUGVAR_AEZAKMI false
#define DEBUGVAR_SHOW_NOISES false
#define DEBUGVAR_INCLUDE_FXS true//true

#define MAXIMAL_ROADS_AT_MAP 0//100
#define MAXIMAL_BLOCKS_AT_MAP 15//18
#define MAXIMAL_ENEMIES_AT_MAP 40//10

// дистанци€ от кра€ карты, наруша€ которую, начинаетс€ смещение объектов
const double PLAYER_OUT_OF_MAP_SAFE_OFFSET = 200;//RESOLUTION_X;//200.00;
const double FAR_DISTANCE = 900.0; // дистанци€, на которой удал€ютс€ объекты, расположенные далеко

#define CURSOR_SIZE 6.0
#define ENEMY_SIZE 12.0
#define PLAYER_SIZE 15.0

#define PLAYER_NORMAL_SPEED 125.0   //125
#define ENEMY_NORMAL_SPEED 75.0     //75
#define ENEMY_FAST_SPEED 110//50.0      //110

#define WEAPON_BASE_WOUND_TIME 0.65 //1.25

#define PLAYER_DIRECTION_NO_MOVE 0
#define PLAYER_DIRECTION_N 1
#define PLAYER_DIRECTION_S 2
#define PLAYER_DIRECTION_W 3
#define PLAYER_DIRECTION_E 4
#define PLAYER_DIRECTION_NE 5
#define PLAYER_DIRECTION_SE 6
#define PLAYER_DIRECTION_WS 7
#define PLAYER_DIRECTION_NW 8

//#define DEGTORADc(degress) (degress*_PI/180.0)
#define DEGTORAD (_PI/180.0)
#define DEBUGVAR_UNLIMITED_AMMO -1

#endif

#endif