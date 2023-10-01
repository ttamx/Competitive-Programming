#include "gondola.h"
#include<bits/stdc++.h>

using namespace std;

int valid(int n, int Seq[]){
	vector<int> s(n);
	map<int,bool> mp;
	for(int i=0;i<n;i++){
		if(mp[Seq[i]])return 0;
		mp[Seq[i]]=true;
		if(Seq[i]<=n)s[i]=Seq[i];
	}
	for(int t=0;t<2;t++){
		for(int i=0;i<n;i++){
			if(s[i]>0){
				auto &x=s[(i+1)%n];
				int val=s[i]%n+1;
				if(x==0)x=val;
				else if(x!=val)return 0;
			}
		}
	}
	return 1;
}

//----------------------

int replacement(int n, int Seq[], int Ans[]){
	vector<int> s(n);
	vector<pair<int,int>> vec;
	for(int i=0;i<n;i++){
		if(Seq[i]<=n)s[i]=Seq[i];
		else vec.emplace_back(Seq[i],i);
	}
	for(int t=0;t<2;t++)for(int i=0;i<n;i++)if(s[i]>0)s[(i+1)%n]=s[i]%n+1;
	if(s[0]==0)iota(s.begin(),s.end(),1);
	sort(vec.begin(),vec.end());
	int nxt=n+1;
	int sz=0;
	for(auto [num,pos]:vec){
		while(s[pos]!=num){
			Ans[sz++]=s[pos];
			s[pos]=nxt++;
		}
	}
	return sz;
}

//----------------------

typedef long long ll;

const ll mod=1e9+9;

ll binpow(ll a,ll b){
	ll res=1;
	while(b>0){
		if(b&1)res*=a,res%=mod;
		a*=a,a%=mod;
		b>>=1;
	}
	return res;
}

int countReplacement(int n, int Seq[]){
	if(!valid(n,Seq))return 0;
	vector<int> s(n);
	vector<int> vec;
	ll ans=n;
	for(int i=0;i<n;i++){
		if(Seq[i]<=n)s[i]=Seq[i],ans=1;
		else vec.emplace_back(Seq[i]);
	}
	sort(vec.rbegin(),vec.rend());
	vec.emplace_back(n);
	for(int i=1;i<vec.size();i++){
		ans*=binpow(i,vec[i-1]-vec[i]-1);
		ans%=mod;
	}
	return (int)ans;
}