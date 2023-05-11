#include "cheatsheet.h"
#include <bits/stdc++.h>
#define base 350001
#define M 1067

using namespace std;

typedef long long ll;

struct A{
	array<int,500> a;
	A(){}
	A(vector<int> v){
		for(int i=0;i<v.size();i++)a[i]=v[i];
	}
	bool operator>(A x){
		for(int i=0;i<500;i++)if(a[i]!=x.a[i])return a[i]>x.a[i];
		return false;
	}
	A operator+(A x){
		ll carry=0;
		for(int i=0;i<500;i--){
			ll val=a[i]+x.a[i]+carry;
			carry=val/base;
			x.a[i]=val%base;
		}
		return x;
	}
	A operator-(A x){
		ll carry=0;
		for(int i=0;i<500;i--){
			ll val=a[i]-x.a[i]-carry;
			if(val<0)val+=base,carry=1;
			else carry=0;
			x.a[i]=val;
		}
		return x;
	}
	A operator*(int x){
		A res=*this;
		ll carry=0;
		for(int i=0;i<500;i++){
			ll val=res.a[i]*x+carry;
			carry=val/base;
			res.a[i]=val%base;
		}
		return res;
	}
	int operator/(A x){
		int l=0,r=M;
		while(l<r){
			int m=(l+r+1)/2;
			if((x*m)>*this)r=m-1;
			else l=m;
		}
		return l;
	}
	void print(){
		for(int i=0;i<5;i++)cout << a[i] << ' ';
		cout << '\n';
	}
};

vector<int> write_cheatsheet(int n, vector<int> a){
	vector<A> fac(M+1);
	fac[0]=A({1});
	for(int i=1;i<=M;i++)fac[i]=fac[i-1]*i;
	A num(a);
	vector<int> r;
	return r;
}

vector<int> recover_answer(int n, vector<int> r){
	vector<int> ans(n);
	return ans;
}
