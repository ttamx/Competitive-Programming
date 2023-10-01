#include "seats.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int h,w,n;
int r[N],c[N];
int mnr[N],mnc[N],mxr[N],mxc[N];
int ans=0;

void give_initial_chart(int H, int W, vector<int> R, vector<int> C){
	h=H,w=W;
	n=h*w;
	mnr[0]=h;
	mnc[0]=w;
	mxr[0]=-1;
	mxc[0]=-1;
	for(int i=1;i<=n;i++){
		r[i]=R[i-1];
		c[i]=C[i-1];
		mnr[i]=min(mnr[i-1],r[i]);
		mnc[i]=min(mnc[i-1],c[i]);
		mxr[i]=max(mxr[i-1],r[i]);
		mxc[i]=max(mxc[i-1],c[i]);
		if((mxr[i]-mnr[i]+1)*(mxc[i]-mnc[i]+1)==i)ans++;
	}
}

int swap_seats(int a, int b){
	if(a>b)swap(a,b);
	a++,b++;
	swap(r[a],r[b]);
	swap(c[a],c[b]);
	for(int i=a;i<=b;i++){
		if((mxr[i]-mnr[i]+1)*(mxc[i]-mnc[i]+1)==i)ans--;
		mnr[i]=min(mnr[i-1],r[i]);
		mnc[i]=min(mnc[i-1],c[i]);
		mxr[i]=max(mxr[i-1],r[i]);
		mxc[i]=max(mxc[i-1],c[i]);
		if((mxr[i]-mnr[i]+1)*(mxc[i]-mnc[i]+1)==i)ans++;
	}
	return ans;
}