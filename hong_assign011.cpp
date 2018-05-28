#include <iostream>
#include <cmath>
#include <cstdlib>

#define _USE_MATH_DEFINES
using namespace std;

class shape {
protected:
	int type = 0;
public:
	int gettype() const {
		return type; // 0 : point, 1: circle, 2: rectangle, 3: triangle
	}
	enum class shapekind {
		point, circle, rectangle, triangle
	};
	virtual double area() = 0;
};

class shapeset {
	shape** shapes;
	int numshapes = 0;
	int maxshapes = 0;
public:
	shapeset(int n) : maxshapes(n) {
		shared_ptr<shape*> shapes(new shape*[n]);
		// shapes = new shape*[n]; <- not using smart pointer
	}
	shapeset(const shapeset& set) : shapes(set.shapes), numshapes(set.numshapes), maxshapes(set.maxshapes) {}

	// ~shapeset()  {<- if not using smart pointer destructor must be needed!
	// 	if (shapes != nullptr)
	// 		delete[] shapes;
	// }

	shapeset& operator= (const shapeset& set) {
		shapes = set.shapes;
		numshapes = set.numshapes;
		maxshapes = set.maxshapes;
		return *this;
	}

	shapeset operator+(shape& s) {
		shapes[numshapes++] = &s;
		return *this;
	}

	double totalarea() {
		double sum = 0.0;
		for (int i = 0; i < numshapes; ++i) {
			sum += shapes[i]->area();
		}
		return sum;
	}
};

class point : public shape {
	double x = 0.0, y = 0.0;
public:
	point(double a, double b) : x(a), y(b) {
		type = static_cast<int>(shape::shapekind::point);
	}
	point(const point& p) : x(p.x), y(p.y) {}
	point& operator= (const point& p) {
		x = p.x;
		y = p.y;
		return *this;
	}

	double area() {
		return 0.0;
	}
	double getx() const {
		return x;
	}
	double gety() const {
		return y;
	}
	friend ostream& operator<<(ostream& os, const point& p) {
		os << '(' << p.x << ", " << p.y << ')';
		return os;
	}
};

class rectangle: public shape {
	point rightupper, leftlower;
public:
	rectangle(const point& a, const point& b) : rightupper(a), leftlower(b) {
		type = static_cast<int>(shape::shapekind::rectangle);
	}
	rectangle(const rectangle& r) : rightupper(r.rightupper), leftlower(r.leftlower) {}
	rectangle& operator=(const rectangle & r) {
		rightupper = r.rightupper;
		leftlower = r.leftlower;
		return *this;
	}
	double area() {
		return (abs(rightupper.getx() - leftlower.getx()) * abs(rightupper.gety() - leftlower.gety()));
	}
	friend ostream& operator<<(ostream& os, const rectangle& r) {
		os << r.gettype() << ", 2 means rectangle! : " << r.rightupper << ", " << r.leftlower ;
		return os;
	}

};

class circle: public shape {
	point center;
	double radius = 0.0;
public:
	circle(const point& c, double r) : center(c), radius(r) {
		type = static_cast<int>(shape::shapekind::circle);
	}
	circle(const circle& c) : center(c.center), radius(c.radius) {}

	circle& operator=(const circle& c) {
		center = c.center;
		radius = c.radius;
		return *this;
	}

	double area() {
		return radius * radius * M_PI;
	}
	friend ostream& operator<<(ostream& os, const circle& c) {
		os << c.gettype() << ", 1 means circle! : the center of circle : " << c.center << ", radius == " << c.radius ;
		return os;
	}
};

class triangle: public shape {
	point p1, p2, p3;
public:
	triangle(const point& a, const class point& b, const class point& c): p1(a), p2(b), p3(c) {
		type = static_cast<int>(shape::shapekind::triangle);
	}
	triangle(const triangle& t) : p1(t.p1), p2(t.p2), p3(t.p3) {}

	triangle& operator=(const triangle& t) {
		p1 = t.p1;
		p2 = t.p2;
		p3 = t.p3;
		return *this;
	}

	bool isContaining(const point& a); // 얜 뭐하는 애지...?
	double area() {
		return 0.5 * abs((p1.getx() * p2.gety()) + (p2.getx() * p3.gety()) + (p3.getx() * p1.gety()) - (p1.getx() * p3.gety()) - (p3.getx() * p2.gety()) - (p2.getx() * p1.gety()));
	}
	friend ostream& operator<<(ostream& os, const triangle& t) {
		os << t.gettype() << ", 3 means triangle! : " << t.p1 << ", " << t.p2 << ", " << t.p3;
		return os;
	}
};

int main(int argc, char const *argv[])
{
	shapeset s(3);
	point p1(0, 1), p2(1, 2), p3(3, 2);
	point p4(0, 0);

	triangle t(p1, p2, p3);
	circle c(p4, 10);
	rectangle r(p1, p3);

	s = s + t;
	s = s + c;
	s = s + r;

	cout << t << endl;
	cout << c << endl;
	cout << r << endl;

	cout << t.area() << endl;
	cout << c.area() << endl;
	cout << r.area() << endl;
	cout << s.totalarea() << endl;

	return 0;
}
