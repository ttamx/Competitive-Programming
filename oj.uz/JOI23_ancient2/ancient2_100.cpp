#include "ancient2.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1000;
const int Q=102;

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

vector<int> solve_left(int n){
	vector<int> ans(n);
	int m=n+2;
	vector<int> a(m),b(m);
	a[n]=b[n]=n;
	a[n+1]=b[n+1]=n+1;
	for(int i=0;i<n;i++){
		a[i]=n;
		b[i]=n+1;
	}
	for(int i=0;i<n;i++){
		int res=Query(m,a,b);
		ans[i]=res-n;
		a[i]=b[i]=i+1;
	}
	return ans;
}

vector<int> solve_right(int n){
	vector<int> ans;
	for(int i=0;i<n;i++){
		ans.insert(ans.begin(),1);
		int m=i+2;
		vector<vector<int>> a(2,vector<int>(m));
		for(int j=0;j<m;j++){
			for(int c=0;c<2;c++){
				int sz=min(j+1,i+1);
				while(sz>0){
					vector<int> res(ans.begin()+j-sz+1,ans.begin()+j);
					res.emplace_back(c);
					vector<int> res2(ans.begin(),ans.begin()+sz);
					if(res==res2)break;
					sz--;
				}
				a[c][j]=sz;
			}
		}
		ans[0]=Query(m,a[0],a[1])==i+1;
	}
	return ans;
}

string Solve(int n) {
	Basis basis(n);
	VBS mat;
	vector<int> ans;
	auto vl=solve_left(min(n/2,Q-2));
	for(int i=0;i<vl.size();i++){
		BS res;
		res[i]=true;
		if(basis.insert(res)){
			mat.emplace_back(res);
			ans.emplace_back(vl[i]);
			if(basis.cnt==n)break;
		}
	}
	auto vr=solve_right(min((n+1)/2,Q-1));
	for(int i=0;i<vr.size();i++){
		BS res;
		res[n-vr.size()+i]=true;
		if(basis.insert(res)){
			mat.emplace_back(res);
			ans.emplace_back(vr[i]);
			if(basis.cnt==n)break;
		}
	}
	for(int m=2;m<=Q/2;m++){
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