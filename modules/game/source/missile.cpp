#include "missile.h"

void MISSILE::draw(HDC bhdc) {
	//const float size = 5.0;
	//HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	//SelectObject(bhdc, pen );
	//SelectObject(bhdc, brush );

	//SelectObject(bhdc, *br);
	//SelectObject(bhdc, *pn);

	const float s = size * height;
	float newX = x+cameraOffsetX;
	float newY = y+cameraOffsetY;

	switch(visualType) {
	case MISSILE_VISUAL_TYPE_ELLIPSE:
		Ellipse(bhdc, newX-s, newY-s, newX+s, newY+s);
		break;

	case MISSILE_VISUAL_TYPE_SQUARE:
		Rectangle(bhdc, newX-s, newY-s, newX+s, newY+s);
		break;
	}

	//if(!flag) {
	//	Rectangle(bhdc, x-size*2, y-size*2, x+size*2, y+size*2);
	//}

	//DeleteObject(pen);
	//DeleteObject(brush);
	//SelectObject(bhdc, NULL);
}