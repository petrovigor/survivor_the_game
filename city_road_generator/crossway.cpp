#include "crossway.h"

//created by unfold crossway constructor
e4_crossway::e4_crossway(float x, float y, int sourceDir, bool dummyVar = false) {
	
	unused = false;
	e4_crossway::sourceDirection = sourceDir;
	e4_crossway::unfolded = false;
	e4_crossway::opened = false;
	e4_crossway::render = false;
	e4_crossway::flag[0] = false;
	e4_crossway::flag[1] = false;
	e4_crossway::flag[2] = false;
	e4_crossway::flag[3] = false;
	e4_crossway::x = x;
	e4_crossway::y = y;
	e4_crossway::cx = 0.0f;
	e4_crossway::cy = 0.0f;
	e4_crossway::roadCount = 0;
	e4_crossway::roads.clear();
}

//right-mouse place constructor:
e4_crossway::e4_crossway(float x, float y, int roadCount) {
	
	unused = false;
	e4_crossway::sourceDirection = UNKNOWN;
	e4_crossway::unfolded = false;
	e4_crossway::opened = false;
	e4_crossway::render = false;
	e4_crossway::flag[0] = false;
	e4_crossway::flag[1] = false;
	e4_crossway::flag[2] = false;
	e4_crossway::flag[3] = false;
	e4_crossway::x = x;
	e4_crossway::y = y;
	e4_crossway::cx = 0.0f;
	e4_crossway::cy = 0.0f;
	e4_crossway::roadCount = roadCount;
	e4_crossway::roads.clear();

	init(x, y, roadCount);
}

void e4_crossway::toDelete(void) {
	unused = true;
}

bool e4_crossway::isToDelete(void) {
	return unused;
}

float e4_crossway::getX(void) {
	return x;
}

float e4_crossway::getY(void) {
	return y;
}

void e4_crossway::init(float x, float y, int roadCount = 0) {
	opened = true;

	if(roadCount < 1) {
		roadCount = 1;
	}

	if(roadCount > 4) {
		roadCount = 4;
	}
	
	e4_crossway::roadCount = roadCount;
	e4_crossway::x = x;
	e4_crossway::y = y;

	for(int i=0; i<roadCount; i++) {
		int n = rand()%4;
		float range = 600.0f;//(float)(rand()%600+300);

		if(roadCount == 1) {
			int j = sourceDirection;
			
			for(int k = 0; k < 2; k++) {
				j++;
				if(j > D) j = A;
			}

			if(n == sourceDirection || n == j) {
				--i;
				continue;
			}
		}

		if(flag[n] || (n == sourceDirection)) {
			--i;
			continue;
		}

		switch(n) {
		case A:
			roads.push_back(e4_road(x, y - range - ROAD_SIZE, range, A, false));
			break;
		case B:
			roads.push_back(e4_road(x + range + ROAD_SIZE, y, range, B, true));
			break;
		case C:
			roads.push_back(e4_road(x, y + range + ROAD_SIZE, range, C, false));
			break;
		case D:
			roads.push_back(e4_road(x - range - ROAD_SIZE, y, range, D, true));
			break;
		}
		
		flag[n] = true;
	}
}



//void e4_crossway::updatePlayerCoordinates(float px, float py) {
//	e4_crossway::px = px;
//	e4_crossway::py = py;
//}

void e4_crossway::deleteFarRoads() {
	for(std::vector<e4_road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		if( DistanceBetweenCoords(320.0f, 240.0f, it->getX(), it->getY()) >= 5000.0f ) {
			it->toDelete();
		}
	}

	std::vector<e4_road>::iterator r = roads.begin();
	while(r != roads.end()) {
		if(r->isToDelete()) {
			roads.erase(r);
			r = roads.begin();
		} else {
			++r;
		}
	}

	if( roads.size()<=0 && DistanceBetweenCoords(320.0f, 240.0f, x, y) >= 2500.0f ) {
		toDelete();
	}

	//update road flags here... flag[n] = false/true
}

bool e4_crossway::isUnfolded(void) {
	return unfolded;
}

bool e4_crossway::isOpened(void) {
	return opened;
}

const std::vector<e4_road> & e4_crossway::getRoadList() {
	return roads;
}

void e4_crossway::draw(HDC hdc) {
	DBG MoveToEx(hdc, 320.0f + cx, 240.0f + cy, NULL);
	DBG LineTo(hdc, x + cx, y + cy);

	RECT rc = {x + cx, y + cy, 640, 480};

	DBG wchar_t buf[128];
	DBG swprintf(buf, L"d=%d r=%d\nsrc=%d", (int)DistanceBetweenCoords(320.0f, 240.0f, x, y), roads.size(), sourceDirection);
	DBG DrawText(hdc, buf, lstrlen(buf), &rc, DT_LEFT);

	for(std::vector<e4_road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		it->draw(hdc);
	}

	if(render && opened) {
		const float sz = 5.0f;

		if(unused) {
			Ellipse(hdc, x + cx - sz, y + cy - sz, x + cx + sz, y + cy + sz);
		} else {
			Rectangle(hdc, x + cx - sz, y + cy - sz, x + cx + sz, y + cy + sz);
		}

		if(!(flag[A]) && sourceDirection!=A) {
			MoveToEx(hdc, x + cx - ROAD_SIZE, y + cy - ROAD_SIZE, NULL);
			LineTo(hdc, x + cx + ROAD_SIZE, y + cy - ROAD_SIZE);
		}
		if(!(flag[B]) && sourceDirection!=B) {
			MoveToEx(hdc, x + cx + ROAD_SIZE, y + cy - ROAD_SIZE, NULL);
			LineTo(hdc, x + cx + ROAD_SIZE, y + cy + ROAD_SIZE);
		}
		if(!(flag[C]) && sourceDirection!=C) {
			MoveToEx(hdc, x + cx - ROAD_SIZE, y + cy + ROAD_SIZE, NULL);
			LineTo(hdc, x + cx + ROAD_SIZE, y + cy + ROAD_SIZE);
		}
		if(!(flag[D]) && sourceDirection!=D) {
			MoveToEx(hdc, x + cx - ROAD_SIZE, y + cy - ROAD_SIZE, NULL);
			LineTo(hdc, x + cx - ROAD_SIZE, y + cy + ROAD_SIZE);
		}
	}
}

bool e4_crossway::presumeCollisionRectange(float x, float y, float hw, float hh) {
	for(std::vector<e4_road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		if(it->presumeCollisionRectangle(x, y, hw, hh)) {
			return true;
		}
	}

	//no collision was detected
	return false;
}

void e4_crossway::Open(void) {
	opened = true;
}

void e4_crossway::Unfold(void) {
	unfolded = true;
}

int e4_crossway::getRoadsCount(void) {
	return roads.size();
}

void e4_crossway::checkRender(void) {
	for(std::vector<e4_road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		it -> checkRender();
	}

	render = (x - ROAD_SIZE + cx < 640.0f && x + ROAD_SIZE + cx > 0.0f && y - ROAD_SIZE + cy < 480.0f && y + ROAD_SIZE + cy > 0.0f);
}

void e4_crossway::setCameraCoordinates(float cx, float cy) {
	e4_crossway::cx = cx;
	e4_crossway::cy = cy;

	for(std::vector<e4_road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		it -> setCameraCoordinates(cx, cy);
	}
}

void e4_crossway::offset(float dx, float dy) {
	x += dx;
	y += dy;

	for(std::vector<e4_road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		it -> offset(dx, dy);
	}
}

e4_crossway::~e4_crossway(void) {
	roads.clear();
}