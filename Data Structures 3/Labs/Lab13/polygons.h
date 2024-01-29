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
				double len = vec->Length();
				//std::cout << len << std::endl;
				for(unsigned int i =0; i < points.size()-1;i++){
					Vector* vec2 = new Vector(points[i],points[i+1]);
					double len2 = vec2->Length();
					//std::cout << points[i].x << " " << points[i << std::endl;
					if(fabs(len - len2) > DISTANCE_EPSILON){
						return false;	
					}
				}
				return true;
			}
			return false;
		}
		
		
		
		bool HasAllEqualAngles(){
			if(points.size() >2){
				double ang1 = Angle(points[2],points[0],points[1]);
				double ang2 = Angle(points[1],points[2],points[0]);
				if(!EqualAngles(ang1,ang2)){
					return false;	
				}
				for(unsigned int i =0; i < points.size()-2;i++){
					double ang3 = Angle(points[i],points[i+1], points[i+2]);
					if(!EqualAngles(ang1,ang3)){
						return false;	
					}
				}
				return true;
			}
			return false;
		}
		
		bool HasARightAngle(){
			if(points.size() >2){
				double ang1 = Angle(points[2],points[0],points[1]);
				double ang2 = Angle(points[1],points[2],points[0]);
				if(RightAngle(ang1) || RightAngle(ang2)){
					return true;	
				}
				for(unsigned int i =0; i < points.size()-2;i++){
					double ang3 = Angle(points[i],points[i+1], points[i+2]);
					if(RightAngle(ang3)){
						return true;	
					}
				}
				return false;
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


class Trapezoid : public virtual Quadrilateral{
	public:
		Trapezoid(const std::string &name, const std::vector<Point> &points) : Quadrilateral(name, points){
			
			Vector* vec = new Vector(points[3],points[0]);
			Vector* vec2 = new Vector(points[1],points[2]);
			Vector* vec3 = new Vector(points[0],points[1]);
			Vector* vec4 = new Vector(points[2],points[3]);
			bool para = Parallel(*vec,*vec2);
			bool para2 = Parallel(*vec3,*vec4);
			
			if(!para && !para2){
				throw -1;
			}
			
		}
};


class Parallelogram : public Trapezoid{
	public:
		Parallelogram(const std::string &name, const std::vector<Point> &points) : Trapezoid(name, points), Quadrilateral(name,points){
			
			Vector* vec = new Vector(points[3],points[0]);
			Vector* vec2 = new Vector(points[1],points[2]);
			Vector* vec3 = new Vector(points[0],points[1]);
			Vector* vec4 = new Vector(points[2],points[3]);
			bool para = Parallel(*vec,*vec2);
			bool para2 = Parallel(*vec3,*vec4);
			
			double ang1 = Angle(points[0],points[1],points[2]);
			double ang2 = Angle(points[2],points[3],points[0]);
			double ang3 = Angle(points[1],points[2],points[3]);
			double ang4 = Angle(points[3],points[0],points[1]);
			if(!EqualAngles(ang1,ang2) || !EqualAngles(ang4,ang3) || !para || !para2){
				throw -1;
			}
			
		}
};





class Rectangle : public virtual Parallelogram{
	public:
		Rectangle(const std::string &name, const std::vector<Point> &points) : Parallelogram(name, points), Quadrilateral(name,points){
			
			Vector* vec = new Vector(points[3],points[0]);
			Vector* vec2 = new Vector(points[1],points[2]);
			Vector* vec3 = new Vector(points[0],points[1]);
			Vector* vec4 = new Vector(points[2],points[3]);
			bool para = Parallel(*vec,*vec2);
			bool para2 = Parallel(*vec3,*vec4);
			
			bool ang1 = RightAngle(Angle(points[0],points[1],points[2]));
			bool ang2 = RightAngle(Angle(points[2],points[3],points[0]));
			bool ang3 = RightAngle(Angle(points[1],points[2],points[3]));
			bool ang4 = RightAngle(Angle(points[3],points[0],points[1]));
			if(!ang1 || !ang2 || !ang3 || !ang4 || !para || !para2){
				throw -1;
			}
			
		}
};






class Kite : public virtual Quadrilateral{
	public:
		Kite(const std::string &name, const std::vector<Point> &points) : Quadrilateral(name, points){
			
			Vector* vec = new Vector(points[3],points[0]);
			Vector* vec2 = new Vector(points[1],points[2]);
			Vector* vec3 = new Vector(points[0],points[1]);
			Vector* vec4 = new Vector(points[2],points[3]);
			
			double ang1 = Angle(points[0],points[1],points[2]);
			double ang2 = Angle(points[2],points[3],points[0]);
			double ang3 = Angle(points[1],points[2],points[3]);
			double ang4 = Angle(points[3],points[0],points[1]);
			
			if(!EqualSides(DistanceBetween(points[3],points[0]),DistanceBetween(points[0],points[1])) || !EqualSides(DistanceBetween(points[1],points[2]),DistanceBetween(points[2],points[3])) || !EqualAngles(ang1,ang2)){
				throw -1;				
			}
			
		}
};


class Rhombus : public virtual Parallelogram, public Kite{
	public:
		Rhombus(const std::string &name, const std::vector<Point> &points) : Parallelogram(name, points), Kite(name,points), Quadrilateral(name,points){
			
			double ang1 = Angle(points[0],points[1],points[2]);
			double ang2 = Angle(points[2],points[3],points[0]);
			double ang3 = Angle(points[1],points[2],points[3]);
			double ang4 = Angle(points[3],points[0],points[1]);
			
			if(HasAllEqualSides() == false || HasAllEqualAngles() == false){
				throw -1;				
			}
			
		}
};


class Square : public Rectangle, public Rhombus{
	public:
		Square(const std::string &name, const std::vector<Point> &points) : Rectangle(name, points), Rhombus(name,points), Parallelogram(name,points), Quadrilateral(name,points){
			
			bool ang1 = RightAngle(Angle(points[0],points[1],points[2]));
			bool ang2 = RightAngle(Angle(points[2],points[3],points[0]));
			bool ang3 = RightAngle(Angle(points[1],points[2],points[3]));
			bool ang4 = RightAngle(Angle(points[3],points[0],points[1]));
			
			if(HasAllEqualSides() == false || !ang1 || !ang2 || !ang3 || !ang4){
				throw -1;				
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




class RightTriangle : public virtual Triangle{
	public:
		RightTriangle(const std::string &name, const std::vector<Point> &points) : Triangle(name, points){
			bool ang1 = RightAngle(Angle(points[0],points[1],points[2]));
			bool ang2 = RightAngle(Angle(points[2],points[0],points[1]));
			bool ang3 = RightAngle(Angle(points[1],points[2],points[0]));
			
			
			if(!ang1 && !ang2 && !ang3){
				throw -1;
			}
		}
};

class IsoscelesTriangle : public virtual Triangle{
	public:
		IsoscelesTriangle(const std::string &name, const std::vector<Point> &points) : Triangle(name, points){
			Vector* vec = new Vector(points[0],points[points.size()-1]);
			double len = vec->Length();
			bool iso = false;
			for(unsigned int i =0; i < points.size()-1;i++){
				Vector* vec2 = new Vector(points[i],points[i+1]);
				double len2 = vec2->Length();
				if(fabs(len - len2) < DISTANCE_EPSILON){
					iso = true;
					break;
				}
			}	
			if(iso==false){
				throw -1;
			}
		}
};


class IsoscelesRightTriangle : public RightTriangle, public IsoscelesTriangle{
	public:
		IsoscelesRightTriangle(const std::string &name, const std::vector<Point> &points) : RightTriangle(name, points), IsoscelesTriangle(name,points), Triangle(name,points){
			Vector* vec = new Vector(points[0],points[points.size()-1]);
			double len = vec->Length();
			bool iso = false;
			bool angle = false;
			for(unsigned int i =0; i < points.size()-1;i++){
				Vector* vec2 = new Vector(points[i],points[i+1]);
				double len2 = vec2->Length();
				if(fabs(len - len2) < DISTANCE_EPSILON){
					iso = true;
					break;
				}
			}	
			bool ang1 = RightAngle(Angle(points[0],points[1],points[2]));
			bool ang2 = RightAngle(Angle(points[2],points[0],points[1]));
			bool ang3 = RightAngle(Angle(points[1],points[2],points[0]));
			
			
			if(iso==false && !ang1 && !ang2 && !ang3){
				throw -1;
			}
		}
};

class EquilateralTriangle : public IsoscelesTriangle{
	public:
		EquilateralTriangle(const std::string &name, const std::vector<Point> &points) : IsoscelesTriangle(name, points), Triangle(name,points){
			
			if(HasAllEqualSides() == false){
				throw -1;				
			}
			
		}
		
};
#endif