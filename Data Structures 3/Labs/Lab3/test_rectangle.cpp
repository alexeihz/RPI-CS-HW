#include <vector>
#include "Point2D.h"
#include <iostream>
#include "Rectangle.h"

int main(){
	Point2D pt1;
	Point2D pt2(5.9,6.3);
	Point2D pt3;
	Point2D pt4(4.1,7.8);
	Point2D pt5;
	Point2D pt6(10,10);
	Rectangle rec1(pt2,pt4);
	Rectangle rec2(pt1,pt6);
	print_rectangle(rec1);
	print_rectangle(rec2);
	std::cout << rec1.is_point_within(pt4) << std::endl;
	std::vector<Point2D> temp = points_in_both(rec1,rec2);
	//float pt = temp[0].y;
}