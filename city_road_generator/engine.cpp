#include "engine.h"

static e4_engine *e4;

e4_engine::e4_engine() {
	e4 = this;
	debug = true;
	fps = 0;
}

void e4_engine::InitDeviceContext(HWND hWnd) {
	hdc = GetDC(hWnd);
}

void e4_engine::UninitDeviceContext(HWND hWnd) {
	ReleaseDC(hWnd, hdc);
}

void e4_engine::MouseMove(float x, float y) {
	mouse.setPos(x, y);
}

void e4_engine::UpdateCameraCoordinates(void) {
	camera.moveCamera(mouse.getX(), mouse.getY());
	player.setAngle(AngleBetweenCoords(player.getX(), player.getY(), mouse.getX() - camera.getX(), mouse.getY()  - camera.getY()));
}

void e4_engine::LeftMouse(bool flag) {
	mouse.setLeft(flag);

	if(flag) {
	//DBG physics.addCrossway(e4_crossway(mouse.getX() - camera.getX(), mouse.getY() - camera.getY(), rand()%4+1));
		//DBG float angle = player.getAngle();
		//DBG physics.addMissile(e4_missile(player.getX() + player.getRadius() * cos(angle), player.getY() + player.getRadius() * sin(angle), angle, 4.0f, 800.0f));
	}
}

void e4_engine::RightMouse(bool flag) {
	mouse.setRight(flag);

	if(flag) {
		//if(rand()%2) {
			//DBG physics.addBlock(e4_block(mouse.getX() - camera.getX(), mouse.getY() - camera.getY(), rand()%(int)150.0f + 50.0f, rand()%(int)150.0f + 50.0f, BLOCK_TYPE_DEFAULT));
		
		

	//DBG physics.addBlock(e4_block(mouse.getX() - camera.getX(), mouse.getY() - camera.getY(), 200.0f, 200.0f, BLOCK_TYPE_DEFAULT));



		//} else {
		//	DBG physics.addRoad(e4_road(mouse.getX() - camera.getX(), mouse.getY() - camera.getY(), 200.0f, rand()%2));
		//}

		//DBG physics.addCrossways(mouse.getX() - camera.getX(), mouse.getY() - camera.getY());

		//DBG physics.addCrossway(e4_crossway(mouse.getX() - camera.getX(), mouse.getY() - camera.getY(), rand()%4+1));

	}
}

void e4_engine::ProcessPhysics(float deltaTime) {
	player.updateCooldown(deltaTime);
	if(mouse.isLeft() && player.canPlayerShoot()) {
		player.denyShooting();
		DBG float angle = player.getAngle();
		DBG physics.addMissile(e4_missile(player.getX() + player.getRadius() * cos(angle), player.getY() + player.getRadius() * sin(angle), angle, 2.0f, 1200.0f));
	}

	physics.processPhysics(deltaTime);
}

void e4_engine::KeyboardAction(char key, bool flag) {
	keyboard.setKey(key, flag);
	physics.updatePlayerDirection();

	if(flag && key == 'C') {
		DBG physics.removeBlocks();
		DBG physics.removeMissiles();
		DBG physics.removeCrossways();
		DBG physics.addCrossway(e4_crossway(player.getX() - camera.getX(), player.getY() - camera.getY(), 4));
	}

	if(flag && key == 'X') {
		debug = !debug;
		//if(debug) {
		//	camera.setCameraRate(25.0f);
		//} else {
		//	camera.setCameraRate(CAMERA_RATE);
		//}
	}
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
	case WM_CREATE:
		e4->InitDeviceContext(hWnd);
		break;

	case WM_KEYDOWN:
		e4->KeyboardAction(toupper(wParam), true);
		break;

	case WM_KEYUP:
		e4->KeyboardAction(toupper(wParam), false);
		break;

	case WM_MOUSEMOVE:
		e4->MouseMove(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONDOWN:
		e4->LeftMouse(true);
		break;

	case WM_LBUTTONUP:
		e4->LeftMouse(false);
		break;

	case WM_RBUTTONDOWN:
		e4->RightMouse(true);
		break;

	case WM_RBUTTONUP:
		e4->RightMouse(false);
		break;

	case WM_DESTROY:
		e4->UninitDeviceContext(hWnd);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

void e4_engine::drawScene(void) {
	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP memMap = CreateCompatibleBitmap(hdc, 640, 480);
	SelectObject(memDC, memMap);

	BitBlt(memDC, 0, 0, 640, 480, hdc, 0, 0, SRCCOPY);

	HBRUSH brush = CreateSolidBrush(0x0);
	RECT rc = {0, 0, 640, 480};

	//HBRUSH brush2 = CreateSolidBrush(0xffffff);
	SelectObject(memDC, brush);
	HPEN pen = CreatePen(PS_SOLID, 1, 0xffccff);
	SelectObject(memDC, pen);

	FillRect(memDC, &rc, brush);
	
	physics.drawBlocks(memDC);
	physics.drawCrossways(memDC);
	player.draw(memDC);
	mouse.draw(memDC);
	physics.drawMissiles(memDC);

	if(debug) {
		DBG memset(&rc, 0, sizeof(rc));
		DBG rc.right = 640;
		DBG rc.bottom = 100;

		DBG wchar_t buf[128];
		DBG swprintf(buf, L"camera xy: %d %d", (int)camera.getX(), (int)camera.getY());
		DBG DrawText(memDC, buf, lstrlen(buf), &rc, DT_CENTER);

		DBG rc.right = 100;

		DBG swprintf(buf, L"missiles: %d", physics.getMissilesCount());
		DBG DrawText(memDC, buf, lstrlen(buf), &rc, DT_CENTER);

		DBG rc.right = 300;

		DBG swprintf(buf, L"fps: %d", fps);
		DBG DrawText(memDC, buf, lstrlen(buf), &rc, DT_CENTER);
	
		//DBG rc.top = 25;
		//DBG rc.left = 0;
		//DBG rc.right = 100;
		//DBG rc.bottom = 150;

		//DBG swprintf(buf, L"render: %d", physics.getRenderedMissiles());
		//DBG DrawText(memDC, buf, lstrlen(buf), &rc, DT_CENTER);

		DBG rc.top = 50;
		DBG rc.left = 0;
		DBG rc.right = 100;
		DBG rc.bottom = 150;

		DBG swprintf(buf, L"blocks: %d", physics.getBlockCount());
		DBG DrawText(memDC, buf, lstrlen(buf), &rc, DT_CENTER);

		DBG rc.top = 75;
		DBG rc.left = 0;
		DBG rc.right = 100;
		DBG rc.bottom = 150;

		DBG swprintf(buf, L"cw/r: %d/%d", physics.getCrosswaysCount(), physics.getRoadsCount());
		DBG DrawText(memDC, buf, lstrlen(buf), &rc, DT_CENTER);
	}

	BitBlt(hdc, 0, 0, 640, 480, memDC, 0, 0, SRCCOPY);

	DeleteObject((HGDIOBJ)brush);
	DeleteObject((HPEN)pen);
	//DeleteObject((HGDIOBJ)brush2);
	DeleteObject((HGDIOBJ)memMap);
	DeleteDC(memDC);
}

BOOL e4_engine::InitWindow(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASS wc;
	memset(&wc, 0, sizeof(wc));

	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = L"Class";
	wc.style = CS_HREDRAW|CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	if(!RegisterClass(&wc)) {
		return FALSE;
	}

	RECT rect = {0, 0, 640, 480};
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindow(L"Class", NULL, WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2, (GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, NULL, NULL);
	
	if(!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);

	return TRUE;
}

BOOL e4_engine::InitGame(void) {
	timer.init();

	player.setXY(320.0f, 240.0f);
	player.setRadius(15.0f);
	player.setSpeed(300.0f);

	physics.init(&player, &keyboard/*, &camera*/);
	camera.init(&physics, &player);

	DBG physics.addCrossway(e4_crossway(player.getX(), player.getY(), 4));

	return TRUE;
}

void e4_engine::Launch(void) {
	srand((unsigned)time(NULL));

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	int fps = 0;
	float time = 0.0f;

	while(true) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if(GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				break;
			}
		} else {
			drawScene();
			fps++;
		}

		timer.update();

		ProcessPhysics((float)timer.getDelta());
		UpdateCameraCoordinates();

		time += (float)timer.getDelta();
		if(time >= 1.0f) {
			time = 0.0f;
			e4_engine::fps = fps;
			fps = 0;
		}
	}
}