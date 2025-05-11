#include "nicetry.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n;
vector<int> a[3];
vector<ll> c[3][3],d[3],e[3][3];

void init(int _n,int q,vector<int> _a,vector<int> _b,vector<int> _c){
	n=_n;
  	a[0]=move(_a),a[1]=move(_b),a[2]=move(_c);
	for(int i=0;i<3;i++)sort(a[i].begin(),a[i].end());
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			int p=0;
			for(int k=0;k<n;k++){
				while(p<n&&a[j][p]<a[i][k])p++;
				c[i][j].emplace_back(n-p);
			}
		}
		ll s=0;
		for(int j=0;j<n;j++){
			d[i].emplace_back(s);
			s+=c[i][(i+1)%3][j]*c[i][(i+2)%3][j];
		}
		for(int j=0;j<3;j++){
			s=0;
			for(int k=0;k<n;k++){
				e[i][j].emplace_back(s);
				s+=c[i][j][k];
			}
		}
	}
}

ll find_order(int aa,int bb,int cc){
	int v[3]={aa,bb,cc};
	int p[3]={0,1,2};
	sort(p,p+3,[&](int x,int y){return v[x]<v[y];});
	for(int i=0;i<3;i++)v[i]=lower_bound(a[i].begin(),a[i].end(),v[i])-a[i].begin();
	return d[p[0]][v[p[0]]]+e[p[1]][p[2]][v[p[1]]]+v[p[2]]+1;
}