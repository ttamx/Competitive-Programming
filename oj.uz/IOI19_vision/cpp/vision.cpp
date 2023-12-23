#include "vision.h"
#include<bits/stdc++.h>

using namespace std;

void construct_network(int H, int W, int K) {
	vector<int> h(H),w(W);
	for(int i=0;i<H;i++){
		vector<int> res;
		for(int j=0;j<W;j++)res.emplace_back(i*W+j);
		h[i]=add_or(res);
	}
	for(int i=0;i<W;i++){
		vector<int> res;
		for(int j=0;j<H;j++)res.emplace_back(j*W+i);
		w[i]=add_or(res);
	}
	int sameh=add_xor(h);
	int samew=add_xor(w);
	int ONE=add_or(h);
	int ZERO=add_not(ONE);
	int prevh=ZERO;
	vector<int> formerh(H),latterh(H);
	for(int i=0;i<H;i++){
		formerh[i]=add_and({h[i],add_not(prevh)});
		latterh[i]=add_and({h[i],add_or({prevh,sameh})});
		prevh=add_or({prevh,h[i]});
	}
	int prevw=ZERO;
	vector<int> formerw(W),latterw(W);
	for(int i=0;i<W;i++){
		formerw[i]=add_and({w[i],add_not(prevw)});
		latterw[i]=add_and({w[i],add_or({prevw,samew})});
		prevw=add_or({prevw,w[i]});
	}
	vector<int> num1h(8,ZERO),num2h(8,ZERO);
	for(int i=0;i<8;i++){
		vector<int> res1,res2;
		for(int j=0;j<H;j++){
			if(j>>i&1){
				res1.emplace_back(formerh[j]);
				res2.emplace_back(latterh[j]);
			}
		}
		if(res1.empty())continue;
		num1h[i]=add_or(res1);
		num2h[i]=add_or(res2);
	}
	vector<int> num1w(8,ZERO),num2w(8,ZERO);
	for(int i=0;i<8;i++){
		vector<int> res1,res2;
		for(int j=0;j<W;j++){
			if(j>>i&1){
				res1.emplace_back(formerw[j]);
				res2.emplace_back(latterw[j]);
			}
		}
		if(res1.empty())continue;
		num1w[i]=add_or(res1);
		num2w[i]=add_or(res2);
	}
	auto adder=[&](vector<int> a,vector<int> b){
		vector<int> res;
		int carry=ZERO;
		for(int i=0;i<8;i++){
			int axorb=add_xor({a[i],b[i]});
			int sum=add_xor({axorb,carry});
			carry=add_or({add_and({axorb,carry}),add_and({a[i],b[i]})});
			res.emplace_back(sum);
		}
		res.emplace_back(carry);
		return res;
	};
	auto sum1=adder(num1h,num1w);
	auto sum2=adder(num2h,num2w);
	auto compare=[&](vector<int> a,int k){
		vector<int> res[2];
		for(int i=0;i<9;i++)res[k>>i&1].emplace_back(a[i]);
		res[1].emplace_back(add_not(add_or(res[0])));
		return add_and(res[1]);
	};
	vector<int> res;
	for(int i=K;i<=H+W-2;i++){
		int j=i-K;
		res.emplace_back(add_and({compare(sum1,j),compare(sum2,i)}));
	}
	add_or(res);
}