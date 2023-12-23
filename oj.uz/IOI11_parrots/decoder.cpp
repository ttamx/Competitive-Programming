#include "decoder.h"
#include "decoderlib.h"
#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")

using namespace std;


int Base=321;

struct Bignum{
	array<int,256> d;
	Bignum(int x=0){
		for(int i=0;i<256;i++){
			d[i]=x%Base;
			x/=Base;
		}
	}
	Bignum& operator+=(const Bignum &rhs){
		for(int i=0;i<256;i++){
			d[i]+=rhs.d[i];
			if(d[i]>=Base)d[i]-=Base,d[i+1]++;
		}
		return *this;
	}
	Bignum& operator-=(const Bignum &rhs){
		for(int i=0;i<256;i++){
			d[i]-=rhs.d[i];
			if(d[i]<0)d[i]+=Base,d[i+1]--;
		}
		return *this;
	}
	Bignum& operator*=(const int &rhs){
		int carry=0;
		for(int i=0;i<256;i++){
			d[i]*=rhs;
			d[i]+=carry;
			carry=d[i]/Base;
			d[i]%=Base;
		}
		return *this;
	}
	friend Bignum operator+(const Bignum &lhs,const Bignum &rhs){return Bignum(lhs)+=rhs;}
	friend Bignum operator-(const Bignum &lhs,const Bignum &rhs){return Bignum(lhs)-=rhs;}
	friend Bignum operator*(const Bignum &lhs,const int &rhs){return Bignum(lhs)*=rhs;}
	int cmp(const Bignum &rhs){
		for(int i=255;i>=0;i--)if(d[i]!=rhs.d[i])return d[i]<rhs.d[i]?-1:1;
		return 0;
	}
	bool operator==(const Bignum &rhs){return this->cmp(rhs)==0;}
	bool operator<(const Bignum &rhs){return this->cmp(rhs)==-1;}
	bool operator>(const Bignum &rhs){return this->cmp(rhs)==1;}
	bool operator<=(const Bignum &rhs){return !(*this>rhs);}
	bool operator>=(const Bignum &rhs){return !(*this<rhs);}
	bool operator!=(const Bignum &rhs){return !(*this==rhs);}
	friend ostream& operator<<(ostream &os,const Bignum &o){
		bool ok=false;
		for(int i=255;i>=0;i--){
			if(ok)os << "," << o.d[i];
			else if(o.d[i])os << o.d[i],ok=true;
		}
		if(!ok)os << 0;
		return os;
	}
};

bool Ok=false;
Bignum Dp[256][321];

void decode(int N, int L, int X[]){
	int lim=5*N;
	Base=lim+1;
	Dp[0][0]=1;
	if(!Ok){
		Ok=true;
		Dp[0][0]=1;
		for(int i=1;i<256;i++){
			Bignum sum=0;
			for(int j=0;j<321;j++){
				sum+=Dp[i-1][j];
				Dp[i][j]+=sum;
			}
		}
		for(int i=0;i<256;i++)for(int j=1;j<321;j++)Dp[i][j]+=Dp[i][j-1];
	}
	vector<Bignum> pw(N+1);
	pw[0]=1;
	for(int i=1;i<=N;i++)pw[i]+=pw[i-1]*256;
	Bignum cur,res;
	for(int i=0;i<L;i++)cur.d[X[i]]++;
	int all=lim;
	if(cur!=0)res=1;
	for(int i=255;i>=0;i--){
		for(int j=0;j<cur.d[i];j++){
			res+=Dp[i][all-j];
		}
		all-=cur.d[i];
	}
	vector<int> ans(N);
	for(int i=N-1;i>=0;i--){
		int num=0;
		for(int j=0;j<256;j++){
			if(res<pw[i])break;
			res-=pw[i];
			num++;
		}
		ans[i]=num;
	}
	for(auto x:ans)output(x);
}