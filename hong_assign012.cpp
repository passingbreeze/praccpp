#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <set>
#include <iterator>
#include <string>

using namespace std;

class Shape {
protected:
	int type = 0;
public:
	int getType() const {
		return type; // 0 : Point, 1: Circle, 2: Rectangle, 3: Triangle
	}
	enum class shapeKind {
		Point, Circle, Rectangle, Triangle
	};
	virtual double Area() = 0;
};

class setShape {
	set<Shape*> shapes;
	size_t maxShapes = 0;
public:
	setShape(int n) : maxShapes(n) {}
	setShape(const setShape& set) : shapes(set.shapes), maxShapes(set.maxShapes) {}
	setShape& operator= (const setShape& set) {
		shapes = set.shapes;
		maxShapes = set.maxShapes;
		return *this;
	}

	setShape operator+(Shape& s) {
		setShape temp(*this);
		(temp.shapes).insert(&s);
		return temp;
	}

	size_t limitNum() const {
		return maxShapes;
	}

	size_t containNum() const {
		return shapes.size();
	}

	double totalArea() {
		double sum = 0.0;
		set<Shape*>::iterator s_iter;
		for (s_iter = shapes.begin(); s_iter != shapes.end(); ++s_iter) {
			sum += (*s_iter)->Area();
		}
		return sum;
	}
};

class Point : public Shape {
	double x = 0.0, y = 0.0;
public:
	Point(double a, double b) : x(a), y(b) {
		type = static_cast<int>(Shape::shapeKind::Point);
	}
	Point(const Point& p) : x(p.x), y(p.y) {}
	Point& operator= (const Point& p) {
		x = p.x;
		y = p.y;
		return *this;
	}

	double Area() {
		return 0.0;
	}
	double get_x() const {
		return x;
	}
	double get_y() const {
		return y;
	}
	friend ostream& operator<<(ostream& os, const Point& p) {
		os << '(' << p.x << ", " << p.y << ')';
		return os;
	}
};

class Rectangle : public Shape {
	Point rightUpper, leftLower;
public:
	Rectangle(const Point& a, const Point& b) : rightUpper(a), leftLower(b) {
		type = static_cast<int>(Shape::shapeKind::Rectangle);
	}
	Rectangle(const Rectangle& r) : rightUpper(r.rightUpper), leftLower(r.leftLower) {}
	Rectangle& operator=(const Rectangle & r) {
		rightUpper = r.rightUpper;
		leftLower = r.leftLower;
		return *this;
	}
	double Area() {
		return (abs(rightUpper.get_x() - leftLower.get_x()) * abs(rightUpper.get_y() - leftLower.get_y()));
	}
	friend ostream& operator<<(ostream& os, const Rectangle& r) {
		os << r.getType() << ", 2 means Rectangle! : " << r.rightUpper << ", " << r.leftLower;
		return os;
	}

};

class Circle : public Shape {
	Point Center;
	double Radius = 0.0;
public:
	Circle(const Point& c, double r) : Center(c), Radius(r) {
		type = static_cast<int>(Shape::shapeKind::Circle);
	}
	Circle(const Circle& c) : Center(c.Center), Radius(c.Radius) {}

	Circle& operator=(const Circle& c) {
		Center = c.Center;
		Radius = c.Radius;
		return *this;
	}

	double Area() {
		return Radius * Radius * M_PI; // M_PI means pi values defined in libraries.
	}
	friend ostream& operator<<(ostream& os, const Circle& c) {
		os << c.getType() << ", 1 means Circle! : the Center of Circle : " << c.Center << ", Radius == " << c.Radius;
		return os;
	}
};

class Triangle : public Shape {
	Point p1, p2, p3;
public:
	Triangle(const Point& a, const class Point& b, const class Point& c) : p1(a), p2(b), p3(c) {
		type = static_cast<int>(Shape::shapeKind::Triangle);
	}
	Triangle(const Triangle& t) : p1(t.p1), p2(t.p2), p3(t.p3) {}

	Triangle& operator=(const Triangle& t) {
		p1 = t.p1;
		p2 = t.p2;
		p3 = t.p3;
		return *this;
	}

	double Area() {
		return 0.5 * abs((p1.get_x() * p2.get_y()) + (p2.get_x() * p3.get_y()) + (p3.get_x() * p1.get_y()) - (p1.get_x() *
			p3.get_y()) - (p3.get_x() *
				p2.get_y()) - (p2.get_x() *
					p1.get_y()));
	}
	friend ostream& operator<<(ostream& os, const Triangle& t) {
		os << t.getType() << ", 3 means Triangle! : " << t.p1 << ", " << t.p2 << ", " << t.p3;
		return os;
	}
};

class errMsg {
	string msg;
public:
	errMsg() : msg("You cannot add more shapes!") {}
	string message() const {
		return msg;
	}
};

int main(int argc, char const *argv[])
{
	setShape s(3);
	Point p1(0, 1), p2(1, 2), p3(3, 2);
	Point p4(0, 0);

	Triangle t(p1, p2, p3);
	Circle c(p4, 10);
	Rectangle r(p1, p3);

	try {
		s = s + t;
		s = s + c;
		s = s + r;
		Rectangle r2(p2, p3);
		s = s + r2;
		if (s.containNum()>s.limitNum())
			throw errMsg();
		cout << t << endl;
		cout << c << endl;
		cout << r << endl;

		cout << t.Area() << endl;
		cout << c.Area() << endl;
		cout << r.Area() << endl;
		cout << s.totalArea() << endl;

	}
	catch (errMsg e) {
		cout << e.message() << endl;
	}
	return 0;
}
