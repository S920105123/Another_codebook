#include <bits/stdc++.h>
using namespace std;
const double PI=acos(-1);

struct Point {
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
		double ang = atan2(cross(v),dot(v));
		return ang < 0 ? ang + PI * 2 : ang;
	}
	double getA()const{//angle to x-axis
		T A=atan2(y,x);//<0 when exceed PI
		if(A<=-PI/2)A+=PI*2;
		return A;
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

template<typename T>
struct polygon{
	polygon(){}
	vector<point<T> > p;//counterclockwise
	T area()const{
		T ans=0;
		for(int i=p.size()-1,j=0;j<(int)p.size();i=j++)
			ans+=p[i].cross(p[j]);
		return ans/2;
	}
	point<T> center_of_mass()const{
		T cx=0,cy=0,w=0;
		for(int i=p.size()-1,j=0;j<(int)p.size();i=j++){
			T a=p[i].cross(p[j]);
			cx+=(p[i].x+p[j].x)*a;
			cy+=(p[i].y+p[j].y)*a;
			w+=a;
		}
		return point<T>(cx/3/w,cy/3/w);
	}
	char ahas(const point<T>& t)const{//return 1 if in simple polygon, -1 if on, 0 if no.
		bool c=0;
		for(int i=0,j=p.size()-1;i<p.size();j=i++)
			if(line<T>(p[i],p[j]).point_on_segment(t))return -1;
			else if((p[i].y>t.y)!=(p[j].y>t.y)&&
			t.x<(p[j].x-p[i].x)*(t.y-p[i].y)/(p[j].y-p[i].y)+p[i].x)
				c=!c;
		return c;
	}
	char point_in_convex(const point<T>&x)const{
		int l=1,r=(int)p.size()-2;
		while(l<=r){//return 1 if in convex polygon, -1 if on, 0 if no.
			int mid=(l+r)/2;
			T a1=(p[mid]-p[0]).cross(x-p[0]);
			T a2=(p[mid+1]-p[0]).cross(x-p[0]);
			if(a1>=0&&a2<=0){
				T res=(p[mid+1]-p[mid]).cross(x-p[mid]);
				return res>0?1:(res>=0?-1:0);
			}else if(a1<0)r=mid-1;
			else l=mid+1;
		}
		return 0;
	}
	vector<T> getA()const{//angle of each edge to x-axis
		vector<T>res;//must be increasing
		for(size_t i=0;i<p.size();++i)
			res.push_back((p[(i+1)%p.size()]-p[i]).getA());
		return res;
	}
	bool line_intersect(const vector<T>&A,const line<T> &l)const{//O(logN)
		int f1=upper_bound(A.begin(),A.end(),(l.p1-l.p2).getA())-A.begin();
		int f2=upper_bound(A.begin(),A.end(),(l.p2-l.p1).getA())-A.begin();
		return l.cross_seg(line<T>(p[f1],p[f2]));
	}
	polygon cut(const line<T> &l)const{
		polygon ans;//convex polygon cut by a line, left side of the line is remained.
		for(int n=p.size(),i=n-1,j=0;j<n;i=j++){
			if(l.ori(p[i])>=0){
				ans.p.push_back(p[i]); 
				if(l.ori(p[j])<0)
					ans.p.push_back(l.line_intersection(line<T>(p[i],p[j])));
			}else if(l.ori(p[j])>0)
				ans.p.push_back(l.line_intersection(line<T>(p[i],p[j])));
		}
		return ans;
	}
	static bool graham_cmp(const point<T>& a,const point<T>& b){//CMP for finding hull
		return (a.x<b.x)||(a.x==b.x&&a.y<b.y);
	}
	void graham(vector<point<T> > &s){//convex hull
		sort(s.begin(),s.end(),graham_cmp);
		p.resize(s.size()+1);
		int m=0;
		for(size_t i=0;i<s.size();++i){
			while(m>=2&&(p[m-1]-p[m-2]).cross(s[i]-p[m-2])<=0)--m;
			p[m++]=s[i];
		}
		for(int i=s.size()-2,t=m+1;i>=0;--i){
			while(m>=t&&(p[m-1]-p[m-2]).cross(s[i]-p[m-2])<=0)--m;
			p[m++]=s[i];
		}
		if(s.size()>1)--m; 
		p.resize(m);
	}
	T diameter(){
		int n=p.size(),t=1;
		T ans=0;p.push_back(p[0]);
		for(int i=0;i<n;i++){
			point<T> now=p[i+1]-p[i];
			while(now.cross(p[t+1]-p[i])>now.cross(p[t]-p[i]))t=(t+1)%n;
			ans=max(ans,(p[i]-p[t]).abs2());
		}
		return p.pop_back(),ans;
	}
	T min_cover_rectangle(){// find convex hull before call this
		int n=p.size(),t=1,r=1,l;
		if(n<3)return 0;
		T ans=1e99;p.push_back(p[0]);
		for(int i=0;i<n;i++){
			point<T> now=p[i+1]-p[i];
			while(now.cross(p[t+1]-p[i])>now.cross(p[t]-p[i]))t=(t+1)%n;
			while(now.dot(p[r+1]-p[i])>now.dot(p[r]-p[i]))r=(r+1)%n;
			if(!i)l=r;
			while(now.dot(p[l+1]-p[i])<=now.dot(p[l]-p[i]))l=(l+1)%n;
			T d=now.abs2();
			T tmp=now.cross(p[t]-p[i])*(now.dot(p[r]-p[i])-now.dot(p[l]-p[i]))/d;
			ans=min(ans,tmp);
		}
		return p.pop_back(),ans;
	}
	T dis2(polygon &pl){//square of distance of two convex polygon
		vector<point<T> > &P=p,&Q=pl.p;
		int n=P.size(),m=Q.size(),l=0,r=0;
	for(int i=0;i<n;++i)if(P[i].y<P[l].y)l=i;
	for(int i=0;i<m;++i)if(Q[i].y<Q[r].y)r=i;
		P.push_back(P[0]),Q.push_back(Q[0]);
		T ans=1e99;
		for(int i=0;i<n;++i){
			while((P[l]-P[l+1]).cross(Q[r+1]-Q[r])<0)r=(r+1)%m;
			ans=min(ans,line<T>(P[l],P[l+1]).seg_dis2(line<T>(Q[r],Q[r+1])));
			l=(l+1)%n;
		}
		return P.pop_back(),Q.pop_back(),ans;
	}
	static char sign(const point<T>&t){
		return (t.y==0?t.x:t.y)<0;
	}
	static bool angle_cmp(const line<T>& A,const line<T>& B){
		point<T> a=A.p2-A.p1,b=B.p2-B.p1;
		return sign(a)<sign(b)||(sign(a)==sign(b)&&a.cross(b)>0);
	}
	int halfplane_intersection(vector<line<T> > &s){
		sort(s.begin(),s.end(),angle_cmp);//half plane is left side of the line
		int L,R,n=s.size();
		vector<point<T> > px(n);
		vector<line<T> > q(n);
		q[L=R=0]=s[0];
		for(int i=1;i<n;++i){
			while(L<R&&s[i].ori(px[R-1])<=0)--R;
			while(L<R&&s[i].ori(px[L])<=0)++L;
			q[++R]=s[i];
			if(q[R].parallel(q[R-1])){
				--R;
				if(q[R].ori(s[i].p1)>0)q[R]=s[i];
			}
			if(L<R)px[R-1]=q[R-1].line_intersection(q[R]);
		}
		while(L<R&&q[L].ori(px[R-1])<=0)--R;
		p.clear();
		if(R-L<=1)return 0;
		px[R]=q[R].line_intersection(q[L]);
		for(int i=L;i<=R;++i)p.push_back(px[i]);
		return R-L+1;
	}
};
template<typename T>
struct triangle{
	point<T> a,b,c;
	triangle(){}
	triangle(const point<T> &a,const point<T> &b,const point<T> &c):a(a),b(b),c(c){}
	T area()const{
		T t=(b-a).cross(c-a)/2;
		return t>0?t:-t;
	}
	point<T> barycenter()const{//center of mass
		return (a+b+c)/3;
	}
	point<T> circumcenter()const{//outer center
		static line<T> u,v;
		u.p1=(a+b)/2; 
		u.p2=point<T>(u.p1.x-a.y+b.y,u.p1.y+a.x-b.x);
		v.p1=(a+c)/2;
		v.p2=point<T>(v.p1.x-a.y+c.y,v.p1.y+a.x-c.x);
		return u.line_intersection(v);
	}
	point<T> incenter()const{//inner center
		T A=sqrt((b-c).abs2()),B=sqrt((a-c).abs2()),C=sqrt((a-b).abs2());
		return point<T>(A*a.x+B*b.x+C*c.x,A*a.y+B*b.y+C*c.y)/(A+B+C);
	}
	point<T> perpencenter()const{// perpendicular(?) center
		return barycenter()*3-circumcenter()*2;
	}
};
