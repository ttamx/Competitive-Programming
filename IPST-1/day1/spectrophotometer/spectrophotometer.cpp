#include "spectrophotometer.h"
#include<bits/stdc++.h>

using namespace std;

const int K=3e5+5;

bool check1[K];
bool check2[K];

void sort_lasers(int N) {
	for(int i=0;i<N*3-1;i++){
		check1[i]=call_swap(i,i+1);
	}
	check1[N*3-1]=true;
	queue<int> q;
	int cnt1=0,cnt2=0,cnt3=0;
	for(int i=0;i<N;i++)if(check1[i])cnt1++;
	for(int i=N;i<N*2;i++)if(check1[i])cnt2++;
	for(int i=N*2;i<N*3;i++)if(check1[i])cnt3++;
	if(cnt1>=cnt2&&cnt1>=cnt3){
		for(int i=0;i<N;i++)if(!check1[i])q.push(i);
		for(int i=N;i<N*3;i++){
			if(check1[i]){
				call_swap(i,q.front());
				q.pop();
			}
		}
		for(int i=N;i<N*3-1;i++){
			check2[i]=call_swap(i,i+1);
		}
		check2[N*3-1]=true;
		cnt1=cnt2=0;
		for(int i=N;i<N*2;i++)if(check2[i])cnt1++;
		for(int i=N*2;i<N*3;i++)if(check2[i])cnt2++;
		if(cnt1>=cnt2){
			for(int i=N;i<2*N;i++)if(!check2[i])q.push(i);
			for(int i=2*N;i<N*3;i++){
				if(check2[i]){
					call_swap(i,q.front());
					q.pop();
				}
			}
		}else{
			for(int i=2*N;i<3*N;i++)if(!check2[i])q.push(i);
			for(int i=N;i<N*2;i++){
				if(check2[i]){
					call_swap(i,q.front());
					q.pop();
				}
			}
		}
	}else if(cnt2>=cnt1&&cnt2>=cnt3){
		for(int i=N;i<N*2;i++)if(!check1[i])q.push(i);
		for(int i=0;i<N;i++){
			if(check1[i]){
				call_swap(i,q.front());
				q.pop();
			}
		}
		for(int i=N*2;i<N*3;i++){
			if(check1[i]){
				call_swap(i,q.front());
				q.pop();
			}
		}
		for(int i=0;i<N-1;i++){
			check2[i]=call_swap(i,i+1);
		}
		check2[N-1]=call_swap(N-1,N*2);
		for(int i=N*2;i<N*3-1;i++){
			check2[i]=call_swap(i,i+1);
		}
		check2[N*3-1]=true;
		cnt1=cnt2=0;
		for(int i=0;i<N;i++)if(check2[i])cnt1++;
		for(int i=N*2;i<N*3;i++)if(check2[i])cnt2++;
		if(cnt1>=cnt2){
			for(int i=0;i<N;i++)if(!check2[i])q.push(i);
			for(int i=2*N;i<N*3;i++){
				if(check2[i]){
					call_swap(i,q.front());
					q.pop();
				}
			}
		}else{
			for(int i=2*N;i<3*N;i++)if(!check2[i])q.push(i);
			for(int i=0;i<N;i++){
				if(check2[i]){
					call_swap(i,q.front());
					q.pop();
				}
			}
		}
	}else{
		for(int i=N*2;i<N*3;i++)if(!check1[i])q.push(i);
		for(int i=0;i<N*2;i++){
			if(check1[i]){
				call_swap(i,q.front());
				q.pop();
			}
		}
		for(int i=0;i<N*2-1;i++){
			check2[i]=call_swap(i,i+1);
		}
		check2[N*2-1]=true;
		cnt1=cnt2=0;
		for(int i=0;i<N;i++)if(check2[i])cnt1++;
		for(int i=N;i<N*2;i++)if(check2[i])cnt2++;
		if(cnt1>=cnt2){
			for(int i=0;i<N;i++)if(!check2[i])q.push(i);
			for(int i=N;i<N*2;i++){
				if(check2[i]){
					call_swap(i,q.front());
					q.pop();
				}
			}
		}else{
			for(int i=N;i<2*N;i++)if(!check2[i])q.push(i);
			for(int i=0;i<N;i++){
				if(check2[i]){
					call_swap(i,q.front());
					q.pop();
				}
			}
		}
	}
}