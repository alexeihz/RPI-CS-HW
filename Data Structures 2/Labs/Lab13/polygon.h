//polygon.h

#ifndef _polygon_h_
#define _polygon_h_

#include <vector>
#include <string>
#include <cstdlib>
#include "utilities.h"
using namespace std;



class Polygon{
	public:
		Polygon(const std::string &name1, const std::vector<Point> &points1){
			name = name1;
			points = points1;
		}
		
		virtual ~Polygon(){};
		
		string getName(){
			return name;
		}
		bool HasAllEqualSides(){
			if(points.size() >2){
				Vector* vec = new Vector(points[0],points[points.size()-1]);
				int len = vec->Length();
				for(unsigned int i =0; i < points.size();i++){
					Vector* vec2 = new Vector(points[i],points[i+1]);
					int len2 = vec2->Length();
					if(len != len2){
					return false;	
					}
				}
				return true;
			}
			return false;
		}
		
		
	protected:
		string name;
		vector<Point> points;
};
class Quadrilateral : public Polygon{
	public:
		Quadrilateral(const std::string &name, const std::vector<Point> &points) : Polygon(name, points){
			if(points.size() != 4){
				throw -1;
			}
			
		}
		
		
};

class Rectangle : public Quadrilateral{
	public:
		Rectangle(const std::string &name, const std::vector<Point> &points) : Quadrilateral(name, points){
			/*
			Vector* vec = new Vector(points[0],points[points.size()-1]);
			Vector* vec2 = new Vector(points[1],points[3]);
			bool para = Parallel(vec,vec2);
			bool ang1 = Angle(points[0],points[1],points[3]);
			bool ang2 = Angle(points[1],points[2],points[3]);
			if(!ang1 || !ang2 || !para){
				throw -1;
			}
			*/
		}
};
class Square : public Rectangle{
	public:
		Square(const std::string &name, const std::vector<Point> &points) : Rectangle(name, points){
			Vector* vec = new Vector(points[0],points[points.size()-1]);
			int len = vec->Length();
			for(unsigned int i =0; i < points.size();i++){
				Vector* vec2 = new Vector(points[i],points[i+1]);
				int len2 = vec2->Length();
				if(len != len2){
					throw -1;
				}
			}			
			
		}
};
class Triangle : public Polygon{
	public:
		Triangle(const std::string &name, const std::vector<Point> &points) : Polygon(name, points){
			
			if(points.size() != 3){
				throw -1;
			}
		}
		
		
};
class IsoscelesTriangle : public Triangle{
	public:
		IsoscelesTriangle(const std::string &name, const std::vector<Point> &points) : Triangle(name, points){
			Vector* vec = new Vector(points[0],points[points.size()-1]);
			int len = vec->Length();
			bool iso = false;
			for(unsigned int i =0; i < points.size();i++){
				Vector* vec2 = new Vector(points[i],points[i+1]);
				int len2 = vec2->Length();
				if(len == len2){
					iso = true;
					break;
				}
			}	
			if(iso==false){
				throw -1;
			}
		}
};
class EquilateralTriangle : public IsoscelesTriangle{
	public:
		EquilateralTriangle(const std::string &name, const std::vector<Point> &points) : IsoscelesTriangle(name, points){
			Vector* vec = new Vector(points[0],points[points.size()-1]);
			int len = vec->Length();
			for(unsigned int i =0; i < points.size();i++){
				Vector* vec2 = new Vector(points[i],points[i+1]);
				int len2 = vec2->Length();
				if(len != len2){
					throw -1;
				}
			}			
		}
		
};
#endif