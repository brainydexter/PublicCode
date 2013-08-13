#include "Data.h"

extern unsigned int N;

bool Data::insert(Point p){
	if(this->m_Points.count(p))
		return false;

    this->m_Points.insert(p);

	int mul = 1;
	if(p.getX() == 0 && p.getY() == 0)
		mul = 1;
	else if(p.getX() == 0 || p.getY() == 0)
		mul = 2;
	else
		mul = 4;

	m_count += mul;

	if(p.getX() >= rightBottom.getX())
		rightBottom.setX(p.getX());

	if(p.getY() >= rightBottom.getY())
		rightBottom.setY(p.getY());


    return true;
}

size_t Data::count(){
	return this->m_count;
}

bool Data::isLegitPoint(const Point& p){
    int x = abs(p.getX());
    int y = abs(p.getY());

    unsigned int xsum, ysum;
    xsum = ysum = 0;

    while(x != 0){
        xsum += (x % 10);

        x = x / 10;
    }

    while(y != 0){
        ysum += (y % 10);

        y = y / 10;
    }

    return xsum + ysum <= N;
}

#include <fstream>
void Data::print(){
	ofstream f;
	f.open("data.txt");

	for(auto i = m_Points.begin(); i != m_Points.end(); ++i){
		f << i->getX() << "," << i->getY() << "\n";
	}

	f.close();
}