#pragma once

class CAMERA {
private:
	float x, y;

public:
	CAMERA() {
		x = y =0.0;
	}

	//write access
	void setXY(float X, float Y) {x=X; y=Y;}

	//read access
	float getX(void) {return x;}
	float getY(void) {return y;}

	~CAMERA() {};
};
