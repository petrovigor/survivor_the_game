#include "player.h"

e4_player::e4_player(void) {
	direct = PLAYER_DIRECTION_IDLE;
	shootTime = 0.0f;
	canShoot = true;
}

void e4_player::setDirection(const int dir) {
	direct = dir;
}

int e4_player::getDirection(void) {
	return e4_player::direct;
}

void e4_player::move(float timeDelta) {
	float x = e4_player::x;
	float y = e4_player::y;

	float s = e4_player::s * timeDelta;
	float s_low = s / sqrt(2.0f);

	switch(direct) {
	case PLAYER_DIRECTION_N:
		y -= s;
		break;
	case PLAYER_DIRECTION_S:
		y += s;
		break;
	case PLAYER_DIRECTION_W:
		x -= s;
		break;
	case PLAYER_DIRECTION_E:
		x += s;
		break;
	case PLAYER_DIRECTION_NE:
		x += s_low;
		y -= s_low;
		break;
	case PLAYER_DIRECTION_SE:
		x += s_low;
		y += s_low;
		break;
	case PLAYER_DIRECTION_NW:
		x -= s_low;
		y -= s_low;
		break;
	case PLAYER_DIRECTION_SW:
		x -= s_low;
		y += s_low;
		break;

	default:
		break;
	}

	setXY(x, y);
}

bool e4_player::canPlayerShoot(void) {
	return canShoot;
}

void e4_player::denyShooting(void) {
	canShoot = false;
}

void e4_player::updateCooldown(float deltaTime) {
	if(!canShoot) {
		shootTime -= deltaTime;
		if(shootTime <= 0.0f) {
			canShoot = true;
			shootTime = 0.1f;
		}
	}
}

void e4_player::draw(HDC hdc) {
	Ellipse(hdc, e4_player::x - r + cx, e4_player::y - r + cy, e4_player::x + r + cx, e4_player::y + r + cy);
	
	//DBG RECT rc;
	//DBG memset(&rc, 0, sizeof(rc));

	//DBG rc.left = (int)x + cx;
	//DBG rc.top = (int)y + cy;
	//DBG rc.right = 640;
	//DBG rc.bottom = 480;

	//DBG wchar_t buf[128];
	//DBG swprintf(buf, L"%d/%d - %d/%d", (int)x, (int)y, (int)r, (int)r);
	//DBG DrawText(hdc, buf, lstrlen(buf), &rc, DT_LEFT);

	if(canShoot) {
		const float s = 4.0f;
		float x = e4_player::x + r * cos(a);
		float y = e4_player::y + r * sin(a);

		Ellipse(hdc, x - s + cx, y - s + cy, x + s + cx, y + s + cy);
	}
}