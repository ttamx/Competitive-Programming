#include <bits/stdc++.h>
#include "rescuelib.h"

using namespace std;

int R,C;

int main()
{
    get_size(R,C);
    int d1 = drop_robot(1,1);
    int d2 = drop_robot(1,C);
    int d3 = drop_robot(R,C);
    int d4 = drop_robot(R,1);
    if(d1>=0&&d2>=0){
    	int y=(d1-d2+C+1)/2;
    	int x=d1-y+2;
    	answer(x,y);
    	return 0;
    }else if(d3>=0&&d2>=0){
    	int y=(R-1+2*C-d2-d3)/2;
    	int x=d2+y-C+1;
    	return 0;
    }else if(d3>=0&&d4>=0){
    	int y=(d4-d3+C+1)/2;
    	int x=R+y-1-d4;
    	answer(x,y);
    	return 0;
    }else if(d1>=0&&d4>=0){
    	int x=(R+d1-d4+1)/2;
    	int y=d1-x+2;
    	answer(x,y);
    	return 0;
    }
}
