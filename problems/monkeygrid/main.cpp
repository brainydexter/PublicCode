#include <iostream>
#include <list>
#include <unordered_set>
using namespace std;

#include "Point.h"
#include "Data.h"

/*
legitPoints = {}; // all the allowed points that monkey can goto
list.push( Point(0,0) ); // start exploring from origin

while(!list.empty()){
 Point p = list.pop_front(); // remove point
 
 // if p has been seen before; ignore p => continue;
 // else mark it and proceed further
 
 if(legit(p){
 // since we are only exploring points in one quadrant, 
 // we don't need to check for -x direction and -y direction
 // hence explore the following: this is like Breadth First Search
  list.push(Point(p.x+1, p.y)); // explore x+1, y
  list.push(Point(p.x, p.y+1)); // explore x, y+1

  legitPoints.insert(p); // during insertion, ignore duplicates 
						 // (although no duplicates should come through after above check)
						 // count properly using multipliers
						 // Origin => count once x = 0 && y == 0 => mul : 1
						 // X axis => count twice x = 0 && y != 0 => mul : 2
						 // Y axis => count twice x != 0 && y = 0 => mul : 2
						 // All others => mul : 4
 }

 return legitPoints.count();
}

optimized further:
- if(x,y) is a valid point, then (y,x) will also be a valid point hence number of points considered are only in 1/8th
*/
unsigned int N = 19;

int main(){

	Point origin(0,0);

	list<Point> points;
	Data legitPoints;

    unordered_set<Point> seenPoints;

	points.push_back(origin);

	while(!points.empty()){
		Point p = points.front(); // this is a seek operation
        points.pop_front(); // this actually deletes an element

		// continue if p has already been checked
        if(seenPoints.count(p))
            continue;
        else
		{
            seenPoints.insert(p);
			
			if(p.getX() != p.getY())
				seenPoints.insert(p.transpose());
		}

		if(Data::isLegitPoint(p)){
			points.push_back( Point(p.getX()+1, p.getY()) );
			points.push_back( Point(p.getX(),   p.getY()+1) );

			legitPoints.insert(p);
			
			if(p.getX() != p.getY())
				legitPoints.insert(p.transpose());
		}
	}

	cout << "Total number of points: " << legitPoints.count();
	//legitPoints.print();
	seenPoints.clear();
	return 0;
}

