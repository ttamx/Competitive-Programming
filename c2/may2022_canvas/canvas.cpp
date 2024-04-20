#include "canvas.h"
#include<bits/stdc++.h>
#define cerr if(0)cerr

using namespace std;

using ld = long double;

const ld eps=1E-8;

bool eq(ld x,ld y){
	return abs(x-y)<eps;
}

bool le(ld x,ld y){
	return y-x>=eps;
}

bool gr(ld x,ld y){
	return x-y>=eps;
}

bool operator==(const point &lhs,const point &rhs){
	return eq(lhs.x,rhs.x)&&eq(lhs.y,rhs.y);
}

ostream &operator<<(ostream &os,const point &p){
	return os << "(" << p.x << "," << p.y << ")";
}

point mirror(point p,point o,line l,circle c,int id=0){
	if(p==o)return p;
	point q=intersection(c,l,id);
	return p==q?intersection(c,l,id^1):q;
}

point mirror(point p,point o,line l,int id=0){
	if(p==o)return p;
	return mirror(p,o,l,compass(o,p),id);
}

point mirror(point p,point o,int id=0){
	if(p==o)return p;
	return mirror(p,o,straightedge(p,o),id);
}

point origin;
point *x_scale,*y_scale;
line x_axis,y_axis;
circle unit_circle;
circle c_scale[10];

line circles2line(circle c1,circle c2){
	return straightedge(intersection(c1,c2,0),intersection(c1,c2,1));
}

line midline(point p1,point p2){
	return circles2line(compass(p1,p2),compass(p2,p1));
}

line perpline(point p){
	if(p==origin)return y_axis;
	circle c=compass(p,origin);
	point q=intersection(c,x_axis,0);
	if(q==origin)q=intersection(c,x_axis,1);
	return midline(origin,q);
}

point midpoint(point p1,point p2,line l){
	if(p1==p2)return p1;
	return intersection(l,midline(p1,p2));
}

point midpoint(point p1,point p2){
	if(p1==p2)return p1;
	return midpoint(p1,p2,straightedge(p1,p2));
}

point construct(point x,point y){
	if(x==origin)return y;
	if(y==origin)return x;
	return mirror(origin,midpoint(x,y));
}

point x2y(point p){
	if(p==origin)return p;
	circle c=compass(origin,p);
	point q=intersection(c,y_axis,0);
	return eq(p.x,q.y)?q:intersection(c,y_axis,1);
}

point move(point p,point a,point b){
	return mirror(mirror(p,midpoint(a,b),x_axis),b,x_axis);
}

point addi(point a,point b){
	point p=move(a,origin,b);
	cerr << a <<  " + " << b << " = " << p << "\n";
	return p;
}

point nega(point p){
	return mirror(p,origin,x_axis);
}

point subt(point a,point b){
	point p=addi(a,nega(b));
	cerr << a << " - " << b << " = " << p << "\n";
	return p;
}

point mult(point a,point b){
	if(a==origin||b==origin)return origin;
	point h=x2y(addi(a,x_scale[-1]));
	point c=x2y(a);
	point d=construct(h,b);
	point p=intersection(straightedge(c,d),x_axis);
	cerr << a << " * " << b << " = " << p << "\n";
	return p;
}

point divi(point a,point b){
	if(a==origin)return origin;
	assert(!(b==origin));
	point c=x2y(subt(x_scale[1],b));
	point d=construct(a,c);
	point p=intersection(straightedge(y_scale[1],d),x_axis);
	cerr << a << " / " << b << " = " << p << "\n";
	return p;
}

point sqr(point a){
	if(a==origin||a==x_scale[1])return a;
	point b=addi(a,x_scale[1]);
	cerr << midpoint(origin,b) << "\n";
	point h=intersection(compass(midpoint(origin,b),b),perpline(a),0);
	cerr << "h : " << h << "\n";
	circle c=compass(a,h);
	point p=intersection(c,x_axis,0);
	if(p.x<a.x)p=intersection(c,x_axis,1);
	p=subt(p,a);
	cerr << "sqrt" << a << " = " << p << "\n";
	return p;
}

void init(){
	x_scale=(point*)malloc(sizeof(point)*25)+10;
	y_scale=(point*)malloc(sizeof(point)*25)+10;
	origin=x_scale[0]=y_scale[0]=p0,y_scale[1]=p1;
	unit_circle=c_scale[1]=compass(y_scale[0],y_scale[1]);
	y_axis=straightedge(y_scale[0],y_scale[1]);
	for(int i=2;i<10;i++)y_scale[i]=mirror(y_scale[i-2],y_scale[i-1],y_axis,1);
	for(int i=2;i<10;i++)c_scale[i]=compass(origin,y_scale[i]);
	for(int i=1;i<10;i++)y_scale[-i]=mirror(y_scale[i],origin,y_axis,c_scale[i]);
	x_axis=midline(y_scale[-1],y_scale[1]);
	for(int i=1;i<10;i++){
		for(int j=0;j<2;j++){
			point p=intersection(c_scale[i],x_axis,j);
			x_scale[le(p.x,0)?-i:i]=p;
		}
	}
}

point build(string s){
	auto [v,rt]=parse(s);
	function<point(int)> dfs=[&](int u){
		auto cur=v[u];
		if(cur.value!=-999)return x_scale[cur.value];
		point l=dfs(cur.left);
		if(cur.right!=-1){
			point r=dfs(cur.right);
			if(cur.ops=="ADD")return addi(l,r);
			if(cur.ops=="SUB")return subt(l,r);
			if(cur.ops=="MUL")return mult(l,r);
			if(cur.ops=="DIV")return divi(l,r);
			assert(false);
		}
		return sqr(l);
	};
	return dfs(rt);
}

point draw(string x,string y){
	init();
	return construct(build(x),x2y(build(y)));
}