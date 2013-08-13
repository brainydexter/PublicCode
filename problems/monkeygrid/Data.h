#ifndef DATA_H
#define DATA_H

#include <unordered_set>
using namespace std;

#include "Point.h"

class Data{
public:
	Data()
	 : m_count(0), rightBottom(0,0)
	{}

	~Data(){ m_Points.clear(); }

	// returns true if point was successfully inserted into this
	bool insert(Point p);
	size_t count();

	static bool isLegitPoint(const Point& p);

	void print();
private:
	unordered_set<Point> m_Points;
	size_t m_count;

	Point rightBottom;
};

#endif
