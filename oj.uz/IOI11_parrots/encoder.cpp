#include "encoder.h"
#include "encoderlib.h"
#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")

using namespace std;

int base=321;

struct bignum{
	array<int,256> d;
	bignum(int x=0){
		for(int i=0;i<256;i++){
			d[i]=x%base;
			x/=base;
		}
	}
	bignum& operator+=(const bignum &rhs){
		for(int i=0;i<256;i++){
			d[i]+=rhs.d[i];
			if(d[i]>=base)d[i]-=base,d[i+1]++;
		}
		return *this;
	}
	bignum& operator-=(const bignum &rhs){
		for(int i=0;i<256;i++){
			d[i]-=rhs.d[i];
			if(d[i]<0)d[i]+=base,d[i+1]--;
		}
		return *this;
	}
	bignum& operator*=(const int &rhs){
		int carry=0;
		for(int i=0;i<256;i++){
			d[i]*=rhs;
			d[i]+=carry;
			carry=d[i]/base;
			d[i]%=base;
		}
		return *this;
	}
	friend bignum operator+(const bignum &lhs,const bignum &rhs){return bignum(lhs)+=rhs;}
	friend bignum operator-(const bignum &lhs,const bignum &rhs){return bignum(lhs)-=rhs;}
	friend bignum operator*(const bignum &lhs,const int &rhs){return bignum(lhs)*=rhs;}
	int cmp(const bignum &rhs){
		for(int i=255;i>=0;i--)if(d[i]!=rhs.d[i])return d[i]<rhs.d[i]?-1:1;
		return 0;
	}
	bool operator==(const bignum &rhs){return this->cmp(rhs)==0;}
	bool operator<(const bignum &rhs){return this->cmp(rhs)==-1;}
	bool operator>(const bignum &rhs){return this->cmp(rhs)==1;}
	bool operator<=(const bignum &rhs){return !(*this>rhs);}
	bool operator>=(const bignum &rhs){return !(*this<rhs);}
	friend ostream& operator<<(ostream &os,const bignum &o){
		bool ok=false;
		for(int i=255;i>=0;i--){
			if(ok)os << "," << o.d[i];
			else if(o.d[i])os << o.d[i],ok=true;
		}
		if(!ok)os << 0;
		return os;
	}
};

bool ok=false;
bignum dp[256][321];

void encode(int N, int M[]){
	int lim=5*N;
	base=lim+1;
	if(!ok){
		ok=true;
		dp[0][0]=1;
		for(int i=1;i<256;i++){
			bignum sum=0;
			for(int j=0;j<321;j++){
				sum+=dp[i-1][j];
				dp[i][j]+=sum;
			}
		}
		for(int i=0;i<256;i++)for(int j=1;j<321;j++)dp[i][j]+=dp[i][j-1];
	}
	vector<bignum> pw(N+1);
	pw[0]=1;
	for(int i=1;i<=N;i++)pw[i]+=pw[i-1]*256;
	bignum cur;
	for(int i=0;i<N;i++)cur+=pw[i]*M[i];
	int all=lim;
	for(int i=255;i>=0;i--){
		int num=0;
		for(int j=0;j<base;j++){
			if(all-j<0||cur<=dp[i][all-j])break;
			cur-=dp[i][all-j];
			num++;
		}
		all-=num;
		for(int j=0;j<num;j++)send(i);
	}
}