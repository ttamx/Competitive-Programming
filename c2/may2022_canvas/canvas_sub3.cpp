#include "canvas.h"
#include<bits/stdc++.h>

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

point midpoint(point p1,point p2,line l){
	if(p1==p2)return p1;
	return intersection(l,midline(p1,p2));
}

point midpoint(point p1,point p2){
	if(p1==p2)return p1;
	return midpoint(p1,p2,straightedge(p1,p2));
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

point answer(point x,point y){
	if(x==origin)return y;
	if(y==origin)return x;
	return mirror(origin,midpoint(x,y));
}

point draw(string x,string y){
	init();
	auto get=[&](string s){
		return s.substr(0,3)=="SUB"?'0'-s[6]:s[0]-'0';
	};
	return answer(x_scale[get(x)],y_scale[get(y)]);
}