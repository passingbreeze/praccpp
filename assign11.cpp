#include <iostream>

using namespace std;

class Shape;

class ShapeSet {
	Shape** shapes;
	int    numShapes;
	int    maxShapes; // maximum number of shape objects
public:
	ShapeSet(int n)
		:shapes(new Shape*[n]),numShapes(0),maxShapes(n) {}
	ShapeSet& operator+(Shape& s) {
		shapes[numShapes++]=&s;
		return *this;
	}
	double totalArea(void);
};
 

class Shape {
protected:
  int  type; // POINT, CIRCLE, RECTANGLE, or TRIANGLE
public:
	Shape(int _type)
		:type(_type) {}
	int getType() const {
		return type;
	}
	enum {POINT, CIRCLE, RECTANGLE, TRIANGLE};
	virtual double area()=0;
};

double ShapeSet::totalArea(void) 
{
	double sum = 0.0;
	for(int i=0;i<numShapes;++i)
		sum+=shapes[i]->area();
	return sum;	
}

class Point : public Shape {
	double x, y;
public:
	Point(double _x, double _y) 
		:Shape(POINT),x(_x), y(_y) {}
	Point(const Point& p) 
		:Shape(p.type),x(p.x),y(p.y) {}
	double readX(void) const {
		return x;
	}		
	double readY(void) const {
		return y;
	}
	double area() { return 0.0;}
};

 

class Rectangle : public Shape {
	Point rightUpper, leftLower;
public:
	Rectangle(const Point& rP, const Point& lp) 
		:Shape(RECTANGLE),rightUpper(rP), leftLower(lp) {}
	double area(void) {
		double row = rightUpper.readX()-leftLower.readX();
		double col = rightUpper.readY()-leftLower.readY();
		return row*col;
	}
};
 

class Circle : public Shape {
	Point Center;
	double radius;
public:
	Circle(const Point& p, double r)
		:Shape(CIRCLE),Center(p),radius(r) {}
	double area(void) {
		return 3.14*radius*radius;
	}
};

double abs(double v) {
	return v>0?v:-v;
} 

class Triangle : public Shape {
	Point p1, p2, p3;
	static double abs(double tmp) {
		return tmp>0 ? tmp : -tmp;
	}
public:
	Triangle(const Point& _p1, const Point& _p2, const Point& _p3) 
		:Shape(TRIANGLE),p1(_p1), p2(_p2), p3(_p3) {}
	double area(void) {
		double tmp = 
			(p1.readX()-p2.readX())*p3.readY() +
			(p2.readX()-p3.readX())*p1.readY() +
			(p3.readX()-p1.readX())*p2.readY();
		return abs(tmp)/2.0;	 
	}
};

int main(void)
{
	ShapeSet s1(4);
	Circle c1(Point(1,2),3);
	Circle c2(Point(2,3),4);
	
	s1+c1+c2;
	cout << s1.totalArea() << endl;
	return 0;
}
