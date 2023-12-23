#include "cheatsheet.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct bignum{
	ll D=501;
	ll B=350001;
	array<ll,501> d;
	bignum(ll x=0ll){
		for(int i=0;i<D;i++)d[i]=x%B,x/=B;
	}
	bignum& operator+=(const bignum &rhs){
		for(int i=0;i<D;i++){
			d[i]+=rhs.d[i];
			if(d[i]>=B)d[i]-=B,d[i+1]++;
		}
		return *this;
	}
	bignum& operator-=(const bignum &rhs){
		for(int i=0;i<D;i++){
			d[i]-=rhs.d[i];
			if(d[i]<0)d[i]+=B,d[i+1]--;
		}
		return *this;
	}
	bignum& operator*=(const ll &rhs){
		ll carry=0;
		for(int i=0;i<D;i++){
			d[i]*=rhs;
			d[i]+=carry;
			carry=d[i]/B;
			d[i]%=B;
		}
		return *this;
	}
	friend bignum operator+(const bignum &lhs,const bignum &rhs){return bignum(lhs)+=rhs;}
	friend bignum operator-(const bignum &lhs,const bignum &rhs){return bignum(lhs)-=rhs;}
	friend bignum operator*(const bignum &lhs,const ll &rhs){return bignum(lhs)*=rhs;}
	int cmp(const bignum &rhs){
		for(int i=D-1;i>=0;i--)if(d[i]!=rhs.d[i])return d[i]<rhs.d[i]?-1:1;
		return 0;
	}
	bool operator<(const bignum &rhs){return this->cmp(rhs)==-1;}
	bool operator>(const bignum &rhs){return this->cmp(rhs)==1;}
	bool operator==(const bignum &rhs){return this->cmp(rhs)==0;}
	bool operator<=(const bignum &rhs){return !(*this>rhs);}
	bool operator>=(const bignum &rhs){return !(*this<rhs);}
	bool operator!=(const bignum &rhs){return !(*this==rhs);}
	void print(){
		bool ok=false;
		for(int i=D-1;i>=0;i--){
			if(ok)cout << "," << d[i];
			else if(d[i])cout << d[i],ok=true;
		}
		if(!ok)cout << 0;
	}
};

vector<int> write_cheatsheet(int N, vector<int> A){
	const int M=1068;
	bignum cur;
	for(int i=0;i<N;i++)cur.d[i]=A[i];
	vector<bignum> fac(M+1);
	fac[0]=1;
	for(int i=1;i<=M;i++)fac[i]=fac[i-1]*i;
	vector<int> res;
	vector<bool> used(M);
	cur+=1;
	for(int i=M-1;i>=0;i--){
		int num=0;
		while(used[num])num++;
		for(int j=0;j<M;j++){
			if(used[j])continue;
			if(cur<=fac[i])break;
			num=j+1;
			while(used[num])num++;
			cur-=fac[i];
		}
		used[num]=true;
		res.emplace_back(num);
	}
	return res;
}

vector<int> recover_answer(int N, vector<int> R){
	const int M=1068;
	bignum cur;
	vector<bignum> fac(M+1);
	fac[0]=1;
	for(int i=1;i<=M;i++)fac[i]=fac[i-1]*i;
	vector<bool> used(M);
	for(int i=0;i<M;i++){
		int cnt=0;
		for(int j=0;j<R[i];j++)if(!used[j])cnt++;
		cur+=fac[M-i-1]*cnt;
		used[R[i]]=true;
	}
	vector<int> res;
	for(int i=0;i<N;i++)res.emplace_back(cur.d[i]);
	return res;
}