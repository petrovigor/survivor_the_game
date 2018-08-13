#include "block.h"

e4_block::e4_block(void) {
	unused = false;
	type = BLOCK_TYPE_DEFAULT;
	x = y = hwidth = hheight = 0.0f;
	ax = ay = bx = by = cx = cy = dx = dy = 0.0f;
	camX = camY = 0.0f;
	render = false;
	heightRate = 1.0f;
}

e4_block::e4_block(float x, float y, float hw, float hh, int type) {
	unused = false;
	heightRate = 1.0f;
	init(x, y, hw, hh, type);
	render = false;
}

void e4_block::offset(float dx, float dy) {
	e4_block::x += dx;
	e4_block::y += dy;

	e4_block::ax = e4_block::dx = e4_block::x - e4_block::hwidth;
	e4_block::bx = e4_block::cx = e4_block::x + e4_block::hwidth;

	e4_block::ay = e4_block::by = e4_block::y - e4_block::hheight;
	e4_block::dy = e4_block::cy = e4_block::y + e4_block::hheight;
}

void e4_block::init(float x, float y, float hw, float hh, int type = BLOCK_TYPE_HOUSE) {
	if(type == BLOCK_TYPE_TREE) {
		hw = hh = 6.0f;
	}

	e4_block::x = x;
	e4_block::y = y;

	e4_block::hwidth = hw;
	e4_block::hheight = hh;

	e4_block::ax = e4_block::dx = x - hw;
	e4_block::bx = e4_block::cx = x + hw;

	e4_block::ay = e4_block::by = y - hh;
	e4_block::dy = e4_block::cy = y + hh;

	//heightRate = (float)(rand()%(85+15)) / 100.0f;
	camX = camY = 0.0f;

	e4_block::type = type;
}

float e4_block::getHalfWidth(void) {
	return hwidth;
}

float e4_block::getHalfHeight(void) {
	return hheight;
}

bool e4_block::isCoordInBlock(float x, float y, float hw, float hh) {
	return x + hw > ax && x - hw < bx && y + hh > ay && y - hh < cy;
}

void e4_block::setCameraCoordinates(float cx, float cy) {
	camX = cx;
	camY = cy;
}

void e4_block::checkRender(void) {
	render = (ax + camX < 640.0f) && (bx + camX < 640.0f) && (cx + camX < 640.0f) && (dx + camX < 640.0f) ||
		(ay + camY < 480.0f) && (by + camY < 480.0f) && (cy + camY < 480.0f) && (dy + camY < 480.0f) ||
		(ax + camX > 0.0f) && (bx + camX > 0.0f) && (cx + camX > 0.0f) && (dx + camX > 0.0f) ||
		(ay + camY > 0.0f) && (by + camY > 0.0f) && (cy + camY > 0.0f) && (dy + camY > 0.0f);
}

void e4_block::draw(HDC hdc, float px, float py) {
	if(render) {
		MoveToEx(hdc, (int)(ax + camX), (int)(ay + camY), NULL);

		LineTo(hdc, (int)(bx + camX), (int)(by + camY));
		LineTo(hdc, (int)(cx + camX), (int)(cy + camY));
		LineTo(hdc, (int)(dx + camX), (int)(dy + camY));
		LineTo(hdc, (int)(ax + camX), (int)(ay + camY));

		float aa = AngleBetweenCoords(px, py, ax, ay);
		float ba = AngleBetweenCoords(px, py, bx, by);
		float ca = AngleBetweenCoords(px, py, cx, cy);
		float da = AngleBetweenCoords(px, py, dx, dy);

		float ad = DistanceBetweenCoords(px, py, ax, ay) * heightRate;
		float bd = DistanceBetweenCoords(px, py, bx, by) * heightRate;
		float cd = DistanceBetweenCoords(px, py, cx, cy) * heightRate;
		float dd = DistanceBetweenCoords(px, py, dx, dy) * heightRate;

		float ax2 = ax + ad * cos(aa);
		float ay2 = ay + ad * sin(aa);
		float bx2 = bx + bd * cos(ba);
		float by2 = by + bd * sin(ba);
		float cx2 = cx + cd * cos(ca);
		float cy2 = cy + cd * sin(ca);
		float dx2 = dx + dd * cos(da);
		float dy2 = dy + dd * sin(da);

		MoveToEx(hdc, (int)(ax2 + camX), (int)(ay2 + camY), NULL);

		LineTo(hdc, (int)(bx2 + camX), (int)(by2 + camY));
		LineTo(hdc, (int)(cx2 + camX), (int)(cy2 + camY));
		LineTo(hdc, (int)(dx2 + camX), (int)(dy2 + camY));
		LineTo(hdc, (int)(ax2 + camX), (int)(ay2 + camY));

		MoveToEx(hdc, (int)(ax2 + camX), (int)(ay2 + camY), NULL);
		LineTo(hdc, (int)(ax + camX), (int)(ay + camY));

		MoveToEx(hdc, (int)(bx2 + camX), (int)(by2 + camY), NULL);
		LineTo(hdc, (int)(bx + camX), (int)(by + camY));
		MoveToEx(hdc, (int)(cx2 + camX), (int)(cy2 + camY), NULL);
		LineTo(hdc, (int)(cx + camX), (int)(cy + camY));
		MoveToEx(hdc, (int)(dx2 + camX), (int)(dy2 + camY), NULL);
		LineTo(hdc, (int)(dx + camX), (int)(dy + camY));

		//DBG RECT rc;
		//DBG memset(&rc, 0, sizeof(rc));

		//DBG rc.top = (int)y + camY;
		//DBG rc.left = (int)x + camX;
		//DBG rc.right = 640;
		//DBG rc.bottom = 480;

		//DBG wchar_t buf[128];
		//DBG swprintf(buf, L"%d/%d - %d/%d", (int)x, (int)y, (int)hwidth, (int)hheight);
		//DBG DrawText(hdc, buf, lstrlen(buf), &rc, DT_LEFT);
	}
}

float e4_block::getX(void) {
	return x;
}

float e4_block::getY(void) {
	return y;
}

void e4_block::toDelete(void) {
	unused = true;
}

bool e4_block::isToDelete(void) {
	return unused;
}