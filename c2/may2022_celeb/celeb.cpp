#include "celeb.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct line{
	ll m,c;
	line(ll m,ll c):m(m),c(c){}
	ll get(ll x){
		return m*x+c;
	}
	ld insect(line l){
		return 1.0*(c-l.c)/(l.m-m);
	}
};

deque<line> dq;

vector<ll> max_revenue(int n,int k,vector<ll> x,vector<int> m)
{
	for(int i=0;i<n;i++){
		line l={-i,x[i]};
		while(dq.size()>1&&dq[1].insect(dq[0])<=dq[1].insect(l))dq.pop_front();
		dq.emplace_front(l);
	}
	vector<ll> rev;
	for(int i=0;i<k;i++){
		while(dq.size()>1&&dq[0].get(m[i])<=dq[1].get(m[i]))dq.pop_front();
		rev.emplace_back(dq[0].get(m[i]));
	}
	return rev;
}

