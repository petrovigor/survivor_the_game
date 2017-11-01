#ifndef __ENGINE_H
#define __ENGINE_H

#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <time.h>
#include "routine.h"
//#include "object.h"
#include "player.h"
#include "mouse.h"
#include "timer.h"
//#include "star.h"
#include "keyboard.h"
#include "physics.h"
#include "block.h"
#include "camera.h"

#define Deg2Rad(deg) (deg / 3.14f * 180.0f)

class e4_engine {
private:
	HWND hWnd;
	HDC hdc;

	e4_player player;
	e4_mouse mouse;
	e4_timer timer;
	e4_keyboard keyboard;
	e4_physics physics;
	e4_camera camera;

	DBG bool debug;
	DBG int fps;

	void drawScene(void);

public:
	e4_engine(void);

	BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);
	BOOL InitGame(void);
	void Launch(void);

	void InitDeviceContext(HWND hWnd);
	void UninitDeviceContext(HWND hWnd);
	void MouseMove(float x, float y);
	void LeftMouse(bool flag);
	void RightMouse(bool flag);
	void UpdateCameraCoordinates(void);
	void KeyboardAction(char key, bool flag);
	void ProcessPhysics(float deltaTime);

	FRIEND LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif