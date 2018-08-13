#include "defines.h"
#include "keys.h"

int KEYS::getPlayerDirection() {
	int v, h;
	v = h = 0;

	if(isPressed(KEY_MOVE_LEFT)) {
		--h;
	}

	if(isPressed(KEY_MOVE_RIGHT)) {
		++h;
	}

	if(isPressed(KEY_MOVE_UP)) {
		--v;
	}

	if(isPressed(KEY_MOVE_DOWN)) {
		++v;
	}

	if(!v && !h) {
		return PLAYER_DIRECTION_NO_MOVE;
	}

	if(!v && h<0) {
		return PLAYER_DIRECTION_W;
	} else if(!v && h>0) {
		return PLAYER_DIRECTION_E;
	} else if(!h && v<0) {
		return PLAYER_DIRECTION_N;
	} else if(!h && v>0) {
		return PLAYER_DIRECTION_S;
	} else if(h > 0 && v > 0) {
		return PLAYER_DIRECTION_SE;
	} else if(h > 0 && v < 0) {
		return PLAYER_DIRECTION_NE;
	} else if(h < 0 && v < 0) {
		return PLAYER_DIRECTION_NW;
	} else if(h < 0 && v > 0) {
		return PLAYER_DIRECTION_WS;
	}
}