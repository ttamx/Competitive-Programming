#include "thief.h"
#include <bits/stdc++.h>

using namespace std;

void solve(int n,int m,vector<int> _u,vector<int> _v){
	vector<int> tmp(m);
	int a=-1,b=-1;
	if(query(tmp)){
		a=0;
		int l=0,r=n-2;
		while(l<r){
			int mid=(l+r)/2;
			for(int i=0;i<n-1;i++){
				tmp[i]=(i>mid);
			}
			if(query(tmp))r=mid;
			else l=mid+1;
		}
		b=l+1;
	}else if(query(vector<int>(m,1))){
		b=0;
		int l=0,r=n-2;
		while(l<r){
			int mid=(l+r)/2;
			for(int i=0;i<n-1;i++){
				tmp[i]=(i<=mid);
			}
			if(query(tmp))r=mid;
			else l=mid+1;
		}
		a=l+1;
	}else{
		int d=1;
		int c=-1;
		for(;d<n;d<<=1){
			for(int v=0;v<2;v++){
				for(int i=0;i<n-1;i++){
					tmp[i]=min(i&d,1)^v;
				}
				if(query(tmp)){
					c=v;
					break;
				}
			}
			if(c!=-1)break;
		}
		assert(c!=-1);
		{
			int l=0,r=n-2;
			while(l<r){
				int mid=(l+r)/2;
				for(int i=0;i<n-1;i++){
					tmp[i]=min(i&d,1)^c^(i>mid);
				}
				if(query(tmp))r=mid;
				else l=mid+1;
			}
			((min(l&d,1)^c)?a:b)=l+1;
		}
		{
			int l=0,r=n-2;
			while(l<r){
				int mid=(l+r+1)/2;
				for(int i=0;i<n-1;i++){
					tmp[i]=min(i&d,1)^c^(i<mid);
				}
				if(query(tmp))l=mid;
				else r=mid-1;
			}
			((min(l&d,1)^c)?a:b)=l+1;
		}
		assert(a!=-1&&b!=-1);
	}
	answer(a,b);
}
