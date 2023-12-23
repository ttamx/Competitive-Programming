#include "mushrooms.h"
#include<bits/stdc++.h>

using namespace std;

const int CUT=38;

int count_mushrooms(int n) {
	if(n==2)return 2-use_machine({0,1});
	vector<int> c(n);
	c[0]=0;
	vector<int> pos[2];
	for(int i=1;i<=2;i++)c[i]=use_machine({0,i});
	for(int i=0;i<=2;i++)pos[c[i]].emplace_back(i);
	int id=pos[1].size()>pos[0].size();
	int front=3;
	auto find2=[&](int idx){
		int tmp=use_machine({idx,pos[id][0],idx+1,pos[id][1]});
		c[idx]=tmp&1^id;
		c[idx+1]=tmp>>1^id;
	};
	if(front+1<n){
		find2(front);
		for(int j=0;j<2;j++)pos[c[front+j]].emplace_back(front+j);
		front+=2;
	}
	for(int i=0;i<CUT&&front+4<n;i++,front+=5){
		id=pos[1].size()>pos[0].size();
		int tmp=use_machine({front,pos[id][0],front+1,pos[id][1],front+2,pos[id][2]});
		c[front]=tmp&1^id;
		if((tmp>>1)!=1){
			c[front+1]=c[front+2]=tmp>>2^id;
			find2(front+3);
		}else{
			if(pos[id^1].size()>1){
				tmp=use_machine({front+3,pos[id][0],front+4,pos[id][1],front+1,pos[id][2],pos[id^1][0],front+2,pos[id^1][1]})-1;
				c[front+3]=tmp&1^id;
				c[front+4]=tmp>>1&1^id;
				c[front+1]=tmp>>2^id;
				c[front+2]=c[front+1]^1;
			}else{
				find2(front+1);
				find2(front+3);
			}
		}
		for(int j=0;j<5;j++)pos[c[front+j]].emplace_back(front+j);
	}
	int last=n;
	int sum=0;
	for(int i=front;i<last;i++){
		id=pos[1].size()>pos[0].size();
		vector<int> res;
		int cnt=0;
		for(int j=0;j<pos[id].size();j++){
			if(j==0){
				res.emplace_back(i);
			}else{
				res.emplace_back(--last);
				cnt++;
			}
			res.emplace_back(pos[id][j]);
			if(last==i+1)break;
		}
		int tmp=use_machine(res);
		c[i]=tmp&1^id;
		pos[c[i]].emplace_back(i);
		if(id){
			sum+=tmp>>1;
		}else{
			sum+=cnt-(tmp>>1);
		}
	}
	for(int i=0;i<last;i++)sum+=c[i]==0;
	return sum;
}