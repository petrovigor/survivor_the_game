#ifndef __CAMERA_H
#define __CAMERA_H

class CAMERA {
private:
	double x, y;

public:
	CAMERA() {
		x = y =0.0;
	}

	//write access
	void setXY(double X, double Y) {x=X; y=Y;}

	//read access
	double getX(void) {return x;}
	double getY(void) {return y;}

	~CAMERA() {};
};

#endif