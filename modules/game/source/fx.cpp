#include <windows.h>
#include "fx.h"

//void FX::draw(HDC bhdc) {
//	switch(visualType) {
//	case FX_VISUAL_TYPE_NONE:
//		break;
//	case FX_VISUAL_TYPE_ELLIPSE:
//		Ellipse(bhdc, x-size, y-size, x+size, y+size);
//		break;
//	case FX_VISUAL_TYPE_RECTANGLE:
//		Rectangle(bhdc, x-size, y-size, x+size, y+size);
//		break;
//	}
//}

void FX_FLASH::draw(HDC bhdc) {
	//HPEN pen = CreatePen(PS_SOLID, 1, RGB(rand()%50+250, rand()%50+250, 0));
	//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
	//SelectObject(bhdc, pen );
	//SelectObject(bhdc, brush );

	float newX = x+cameraOffsetX;
	float newY= y+cameraOffsetY;

	switch(visualType) {
	case FX_VISUAL_TYPE_NONE:
		break;
	case FX_VISUAL_TYPE_ELLIPSE:
		Ellipse(bhdc, newX-size, newY-size, newX+size, newY+size);
		break;
	case FX_VISUAL_TYPE_RECTANGLE:
		Rectangle(bhdc, newX-size, newY-size, newX+size, newY+size);
		break;
	}

	//DeleteObject(pen);
	//DeleteObject(brush);
	//SelectObject(bhdc, NULL);
}

void FX_BLOOD::draw(HDC bhdc) {
	//HPEN pen = CreatePen(PS_SOLID, 1, RGB(rand()%50+250, 0, 0));
	//HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	//SelectObject(bhdc, pen );
	//SelectObject(bhdc, brush );

	float newX = x+cameraOffsetX;
	float newY= y+cameraOffsetY;

	switch(visualType) {
	case FX_VISUAL_TYPE_NONE:
		break;
	case FX_VISUAL_TYPE_ELLIPSE:
		Ellipse(bhdc, newX-size, newY-size, newX+size, newY+size);
		break;
	case FX_VISUAL_TYPE_RECTANGLE:
		Rectangle(bhdc, newX-size, newY-size, newX+size, newY+size);
		break;
	}

	//DeleteObject(pen);
	//DeleteObject(brush);
	//SelectObject(bhdc, NULL);
}

//void FX_SEGMENTS::draw(HDC bhdc) {
//	HPEN pen = CreatePen(PS_SOLID, 1, RGB(rand()%255, rand()%255, rand()%255));
//	HBRUSH brush = CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255));
//	SelectObject(bhdc, pen );
//	SelectObject(bhdc, brush );
//
//	switch(visualType) {
//	case FX_VISUAL_TYPE_NONE:
//		break;
//	case FX_VISUAL_TYPE_ELLIPSE:
//		Ellipse(bhdc, x-size, y-size, x+size, y+size);
//		break;
//	case FX_VISUAL_TYPE_RECTANGLE:
//		Rectangle(bhdc, x-size, y-size, x+size, y+size);
//		break;
//	}
//
//	DeleteObject(pen);
//	DeleteObject(brush);
//	SelectObject(bhdc, NULL);
//}