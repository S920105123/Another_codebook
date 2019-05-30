#include <bits/stdc++.h>
using namespace std;
const double PI=acos(-1);

struct Point {
	// Also a vector
	double x,y;
	double cross(const Point &v) const {
		return x*v.y-y*v.x;
	}
	double dot(const Point &v) const {
		return x*v.x+y*v.y;
	}
	Point normal() { // Normal vector to the left
		return {-y,x};
	}
	double angle(const Point &v) const {
		// Angle from *this to v in [-pi,pi].
		return atan2(cross(v),dot(v));
	}
	Point rotate_about(double theta, const Point &p) const {
		// Rotate this point conterclockwise by theta about p
		double nx=x-p.x,ny=y-p.y;
		return {nx*cos(theta)-ny*sin(theta)+p.x,nx*sin(theta)+ny*cos(theta)+p.y};
	}
};

struct Line {
	// IMPORTANT, remember to transform between two-point form
	// and normal form by yourself, some methods may need them.
	Point p1,p2;
	double a,b,c; // ax+by+c=0
	Line(){} 
    void pton() {
        a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-a*p1.x-b*p1.y;
    }
	int relation(const Point &p) {
		// For line, 0 if point on line
		// -1 if left, 1 if right
		Point dir=p2-p1;
		double crs=dir.cross(p-p1);
		return crs==0?0:crs<0?-1:1;
	}
	Point normal() { // normal vector to the left.
		Point dir=p2-p1;
		return {-dir.y,dir.x};
	}
	bool on_segment(const Point &p) {
		// Point on segment
		return relation(p)==0&&(p2-p).dot(p1-p)<=0;
	}
	bool parallel(const Line &l) {
		// Two line parallel
		return (p2-p1).cross(l.p2-l.p1)==0;
	}
	bool equal(const Line &l) {
		// Two line equal
		return relation(l.p1)==0&&relation(l.p2)==0;
	}
	bool cross_seg(const Line &seg) {
		// Line intersect segment
		Point dir=p2-p1;
		return dir.cross(seg.p1-p1)*dir.cross(seg.p2-p1)<=0;
	}
	int seg_intersect(const Line &s) const{
		// Two segment intersect
		// 0 -> no, 1 -> one point, -1 -> infinity
		Point dir=p2-p1, dir2=s.p2-s.p1;
		double c1=dir.cross(s.p2-p1);
		double c2=dir.cross(s.p1-p1);
		double c3=dir2.cross(p2-s.p1);
		double c4=dir2.cross(p1-s.p1);
		if (c1==0&&c2==0) {
			if((s.p2-p1).dot(s.p1-p1)>0&&(s.p2-p2).dot(s.p1-p2)>0&&
			   (p1-s.p1).dot(p2-s.p1)>0&&(p1-s.p2).dot(p2-s.p2)>0)return 0;
			if(p1==s.p1&&(p2-p1).dot(s.p2-p1)<=0)return 1;
			if(p1==s.p2&&(p2-p1).dot(s.p1-p1)<=0)return 1;
			if(p2==s.p1&&(p1-p2).dot(s.p2-p2)<=0)return 1;
			if(p2==s.p2&&(p1-p2).dot(s.p1-p2)<=0)return 1;
			return -1;
		}else if(c1*c2<=0&&c3*c4<=0)return 1;
		return 0;
	}
	Point line_intersection(const Line &l) const{
		// Intersection of lines
		// pton(); l.pton();
		double deno=a*l.b-l.a*b;
		if (deno!=0) {
			return { (l.c*b-c*l.b)/deno, (l.a*c-a*l.c)/deno};
		}
		// Reaches here means no intersection. (parallel)
        return {1234,4321};
	}
	Point seg_intersection(Line &s) const {
		Point dir=p2-p1, dir2=s.p2-s.p1;
		// pton(); l.pton();
		double c1=dir.cross(s.p2-p1);
		double c2=dir.cross(s.p1-p1);
		double c3=dir2.cross(p2-s.p1);
		double c4=dir2.cross(p1-s.p1);
		if (c1==0&&c2==0) {
			if(p1==s.p1&&(p2-p1).dot(s.p2-p1)<=0)return p1;
			if(p1==s.p2&&(p2-p1).dot(s.p1-p1)<=0)return p1;
			if(p2==s.p1&&(p1-p2).dot(s.p2-p2)<=0)return p2;
			if(p2==s.p2&&(p1-p2).dot(s.p1-p2)<=0)return p2;
		}else if(c1*c2<=0&&c3*c4<=0)return line_intersection(s);
		// Reaches here means either INF or NOT ANY
		// Use seg_intersect to check OuO
        return {1234,4321};
	}
	double dist(const Point &p, bool is_segment) const {
		// Point to Line/segment
		Point dir=p2-p1,v=p-p1;
		if (is_segment) {
			if (dir.dot(v)<0) return v.len();
			if ((p1-p2).dot(p-p2)<0) return (p-p2).len();
		}
		double d=abs(dir.cross(v))/dir.len();
		return d;
	}
};

struct Polygon {
	vector<Point> V; // Counterclockwise
	double area() const {
		double res=0;
		for (int i=1;i+1<V.size();i++) {
			res+=(V[i]-V[0]).cross(V[i+1]-V[0]);
		}
		return abs(res/2.0);
	}
	bool contain(const Point &p) {
		// Point can't on side
		int i, j, k = 0;
	    for(i = 0, j = V.size()-1; i < V.size(); j = i++) {
	        if(V[i].y > p.y != V[j].y > p.y &&
	           p.x < (V[j].x-V[i].x)*(p.y-V[i].y)/(V[j].y-V[i].y)+V[i].x)
	           k++;
	    }
	    return k&1;
	}
};
