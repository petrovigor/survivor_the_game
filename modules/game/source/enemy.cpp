//#include "enemy.h"
//
//bool ENEMY::checkForVisibility(void) {
//	vis = (x<RESOLUTION_X-size && y<RESOLUTION_Y-size && x>size && y>size);
//	return vis;
//}
//
//void ENEMY::draw(HDC bhdc) {
//	checkForVisibility();
//
//	if(vis) {
//		if(alive) {
//			float newX = x+cameraOffsetX;
//			float newY = y+cameraOffsetY;
//
//			Ellipse(bhdc, newX-size, newY-size, newX+size, newY+size);
//
//			if(DEBUGVAR_INCLUDE_ENEMIES_VISION) {
//				if(currentTarget==ENEMY_CURRENT_TARGET_SEARCH_PLAYER) {
//					MoveToEx(bhdc, newX, newY, 0);
//					LineTo(bhdc, px[0]+cameraOffsetX, py[0]+cameraOffsetY);
//					MoveToEx(bhdc, newX, newY, 0);
//					LineTo(bhdc, px[2]+cameraOffsetX, py[2]+cameraOffsetY);
//					MoveToEx(bhdc, newX, newY, 0);
//					LineTo(bhdc, px[1]+cameraOffsetX, py[1]+cameraOffsetY);
//					MoveToEx(bhdc, newX, newY, 0);
//					LineTo(bhdc, px[3]+cameraOffsetX, py[3]+cameraOffsetY);
//
//					MoveToEx(bhdc, newX, newY, 0);
//					LineTo(bhdc, PX+cameraOffsetX, PY+cameraOffsetY);
//				}
//			}
//
//			if(currentTarget==ENEMY_CURRENT_TARGET_PATROL || currentTarget==ENEMY_CURRENT_TARGET_SEARCH_PLAYER) {
//				if(DEBUGVAR_INCLUDE_ENEMIES_VISION) {
//					MoveToEx(bhdc, newX, newY, 0);
//					LineTo(bhdc, toX+cameraOffsetX, toY+cameraOffsetY);
//				}
//			}
//			
//			float X = x + size * cos(angle) +cameraOffsetX;
//			float Y = y + size * sin(angle) +cameraOffsetY;
//			float sz = size/3;
//
//			Ellipse(bhdc, X-sz, Y-sz, X+sz, Y+sz);
//		}
//	}
//}
//
//void ENEMY::correct(float deltaTime, float px, float py, float correctionAngle) {
//    float distance = speed * deltaTime;
//	faceTo(px, py);
//    angle += (DEGTORAD*correctionAngle);
//	x = oldX + distance * cos(angle);
//    y = oldY + distance * sin(angle);
//}
//
//void ENEMY::move(float deltaTime, float playerX, float playerY) {
//	//float _x = oldX;
//	//float _y = oldY;
//	
//	backupXY();
//
//	float dist = speed * deltaTime;
//
//	angle = abc(x, y, playerX, playerY);
//
//	x += dist * cos(angle);
//	y += dist * sin(angle);
//
//	//if(x==_x && y==_y && currentTarget==ENEMY_CURRENT_TARGET_PATROL) {
//	//	toX = x;
//	//	toY = y;
//	//}
//}