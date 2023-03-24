#include "ray.h"
#include <iostream>
#include "physicsManager.h"
#include <Windows.h>

void ray::draw(HDC bhdc, worldPoint playerPos)
{
	//constexpr float32 s = 0.0f;

	//const float32 ratio = 600.0f / 800.0f;
	//const float32 worldCenterOffsetWidth = 800.0f / 2.0f;
	//const float32 worldCenterOffsetHeight = 600.0f / 2.0f;
	//const float32 newX1 = worldCenterOffsetWidth - (s / 2.0f); //p.p.x + cameraOffsetX + worldCenterOffsetWidth*ratio;
	//const float32 newY1 = worldCenterOffsetHeight - (s / 2.0f); //p.p.y + cameraOffsetY + worldCenterOffsetHeight;
	//const float32 newX2 = worldCenterOffsetWidth - (s / 2.0f); //p.p.x + cameraOffsetX + worldCenterOffsetWidth*ratio;
	//const float32 newY2 = worldCenterOffsetHeight - (s / 2.0f); //p.p.y + cameraOffsetY + worldCenterOffsetHeight;


	//const float32 newX = (p.p.x - playerPosition.p.x + cameraOffsetX) - (s / 2.0f);
	//const float32 newY = (p.p.y - playerPosition.p.y + cameraOffsetY) - (s / 2.0f);


	auto &phys = PhysicsManager::instance();
	const auto screenFrom = phys.worldToScreen(from, playerPos);
	const auto screenTo = phys.worldToScreen(to, playerPos);

	const float32 newX1 = screenFrom.p.x;     //x1 + (400-  pp.p.x+ cox);//-  pp.p.x;// + cox);
	const float32 newY1 = screenFrom.p.y;     //y1 + (300-  pp.p.y+ coy);//-  pp.p.y;// + coy);
	const float32 newX2 = screenTo.p.x;       //x2 + (400-  pp.p.x+ cox);//newX1 + 100.0f; //x2;//-  pp.p.x;// + 400;//-  pp.p.x;// + cox);
	const float32 newY2 = screenTo.p.y;       //y2 + (300-  pp.p.y+ coy);//newY1 + 100.0f;//y2;//-  pp.p.y;// + 300;//-  pp.p.y;// + coy);
	//coy; cox;

	//std::cout << "playerXY: " << pp.p.x << " & " << pp.p.y << " from: " << newX1 << ", " << newY1 << " to " << newX2 << ", " << newY2 << std::endl;

	MoveToEx(bhdc, newX1, newY1, 0);
	LineTo(bhdc, newX2, newY2);
}

//void ray::depose(float32 dx, float32 dy) {
//	x1 += dx;
//	y1 += dy;
//	x2 += dx;
//	y2 += dy;
//}

//void ray::setCameraOffset(float32 x, float32 y)
//{
//	cox = x;
//	coy = y;
//}
