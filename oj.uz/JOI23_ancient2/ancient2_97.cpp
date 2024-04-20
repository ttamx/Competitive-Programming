#include "ancient2.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1000;
const int Q=1000;

using BS = bitset<N>;
using VBS = vector<BS>;

struct Basis{
	VBS basis;
	int n,cnt;
	Basis(){}
	Basis(int _n){
		init(_n);
	}
	void init(int _n){
		n=_n;
		cnt=0;
		basis.assign(_n,BS{});
	}
	bool insert(BS v){
		for(int i=0;i<n;i++){
			if(v[i]){
				if(basis[i][i]){
					v^=basis[i];
				}else{
					basis[i]=v;
					cnt++;
					return true;
				}
			}
		}
		return false;
	}
};

void gaussian_elimation(int n,VBS &a,vector<int> &b){
	for(int i=0;i<n;i++){
		int id=i;
		while(!a[id][i])id++;
		swap(a[i],a[id]);
		swap(b[i],b[id]);
		for(int j=0;j<n;j++)if(i!=j&&a[j][i]){
			a[j]^=a[i];
			b[j]^=b[i];
		}
	}
}

bool ask(int n,int m,int r){
	vector<int> a(m*2),b(m*2);
	for(int i=0;i<m;i++){
		int p=(i+1)%m;
		a[i]=b[i]=p;
		a[i+m]=b[i+m]=p+m;
	}
	int p=(r+1)%m;
	b[r]=m+p;
	b[r+m]=p;
	return Query(2*m,a,b)>=m;
}

string Solve(int n) {
	Basis basis(n);
	VBS mat;
	vector<int> ans;
	for(int m=2;m<Q/2;m++){
		for(int r=0;r<m;r++){
			BS res;
			for(int i=r;i<n;i+=m)res[i]=true;
			if(basis.insert(res)){
				mat.emplace_back(res);
				ans.emplace_back(ask(n,m,r));
				if(basis.cnt==n)break;
 			}
		}
		if(basis.cnt==n)break;
	}
	gaussian_elimation(n,mat,ans);
	string res="";
	for(auto x:ans)res.push_back('0'+x);
	return res;
}