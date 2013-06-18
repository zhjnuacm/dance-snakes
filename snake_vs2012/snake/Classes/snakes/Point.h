#ifndef POINT_H
#define POINT_H

class Point {

private:
	int x;
	int y;

public:

	Point(){}
	
	Point(int _x, int _y):x(_x), y(_y){}
	
	int getX();

	int getY();
};

#endif