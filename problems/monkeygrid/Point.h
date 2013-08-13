#ifndef POINT_H
#define POINT_H

#include <functional>

class Point{
private:
	int x, y;
public:
	Point(int a_x, int a_y)
		: x(a_x), y(a_y)
	{}
	~Point(){}

	int getX()const { return x; }
	int getY()const { return y; }

	void setX(int ax) { x = ax; }
	void setY(int ay) { y = ay; }

	bool operator == (const Point& rhs) const{
		return x == rhs.x && y == rhs.y;
	}

	bool operator != (const Point& rhs) const{
		return !(*this == rhs);
	}

	Point transpose() { return Point(y,x); }
};

namespace std
{
    // specializing hash function for Point
    template <>
    struct hash<Point>
    {
        size_t operator()(Point const & x) const /*noexcept*/ // since VS 2012 compiler doesnt support this yet
        {
            return (
                (101 + std::hash<int>()(x.getX())) *
                101 + std::hash<int>()(x.getY())
            );
        }
    };
}

#endif