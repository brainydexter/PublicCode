Problem:
There is a monkey which can walk around on a planar grid. The monkey can move one space at a time left, right, up or down. That is, from (x, y) the monkey can go to (x+1, y), (x-1, y), (x, y+1), and (x, y-1). Points where the sum of the digits of the absolute value of the x coordinate plus the sum of the digits of the absolute value of the y coordinate are lesser than or equal to 19 are accessible to the monkey. For example, the point (59, 79) is inaccessible because 5 + 9 + 7 + 9 = 30, which is greater than 19. Another example: the point (-5, -7) is accessible because abs(-5) + abs(-7) = 5 + 7 = 12, which is less than 19. How many points can the monkey access if it starts at (0, 0), including (0, 0) itself?

Approach:

/*
legitPoints = {}; // all the allowed points that monkey can goto
list.push( Point(0,0) ); // start exploring from origin

while(!list.empty()){
 Point p = list.pop_front(); // remove point
  
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
- if Popped Point p from the list has been seen before; ignore p => continue; else mark it and proceed further
- if(x,y) is a valid point, then (y,x) will also be a valid point hence number of points considered are only in 1/8th
*/