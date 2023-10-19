#include "lingling.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef long long ll;

const int N=2e5+5;
const int M=1<<19;
const int K=145;
const int S=1415;

mt19937 rng(time(nullptr));

int n,k;
int a[N];
p2 b[N],c[N];
int block[N],l[K],r[K],pre[N],suf[N];
ll dp[K][K],cnt[K][N];
int hsh[N],qs1[N],qs2[N];

struct fenwick{
  int t[N];
  void add(int i,int v){	
    while(i<N)t[i]+=v,i+=i&-i;
  }
  int read(int i){
    int ret=0;
    while(i>0)ret+=t[i],i-=i&-i;
    return ret;
  }
}f;

ll calc(vector<int> &l,vector<int> &r){
	ll res=0;
	int i=0,j=0;
	while(i<l.size()&&j<r.size()){
		if(l[i]<r[j])i++;
		else res+=l.size()-i,j++;
	}
	return res;
}

void init_monkeys(vector<int> P, int Q){
	n=P.size();
	for(int i=1;i<=n;i++)hsh[i]=rng(),qs1[i]=qs1[i-1]^hsh[i];
	for(int i=1;i<=n;i++){
		a[i]=P[i-1]+1;
		b[i]=p2(a[i],i);
		qs2[i]=qs2[i-1]^hsh[a[i]];
	}
	k=(n-1)/S+1;
	for(int i=1;i<=k;i++)l[i]=r[i-1]+1,r[i]=i*S;
	r[k]=n;
	for(int i=1;i<=k;i++){
		sort(b+l[i],b+r[i]+1);
		for(int j=l[i];j<=r[i];j++)block[j]=i,c[j]=b[j];
		int res=0;
		for(int j=l[i];j<=r[i];j++){
			f.add(a[j],1);
			res+=f.read(n)-f.read(a[j]);
			pre[j]=res;
		}
		dp[i][i]=res;
		for(int j=l[i];j<=r[i];j++){
			suf[j]=res;
			f.add(a[j],-1);
			res-=f.read(a[j]-1);
		}
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=k;i++){
		for(int j=1,p=l[i];j<=n;j++){
			auto [val,id]=b[j];
			while(p<=r[i]&&val>c[p].first)p++;
			if(id<l[i])cnt[i][id]=p-l[i];
			if(id>r[i])cnt[i][id]=r[i]-p+1-(p<=r[i]&&val==c[p].first);
		}
		for(int j=1;j<=n;j++)cnt[i][j]+=cnt[i][j-1];
	}
	for(int sz=2;sz<=k;sz++){
		for(int i=1,j=sz;j<=k;i++,j++){
			dp[i][j]=dp[i+1][j]+dp[i][j-1]-dp[i+1][j-1]+cnt[j][r[i]]-cnt[j][l[i]-1];
		}
	}
}

long long minimum_branches(int L, int R){
	L++,R++;
	if((qs2[R]^qs2[L-1])!=(qs1[R]^qs1[L-1]))return -1;
	int bl=block[L],br=block[R];
	vector<int> x,y;
	if(bl==br){
		for(int i=l[bl];i<=r[bl];i++){
			auto [val,id]=c[i];
			if(id<L)x.emplace_back(val);
			if(L<=id&&id<=R)y.emplace_back(val);
		}
		return pre[R]-(L==l[bl]?0:pre[L-1])-calc(x,y);
	}
	ll ans=suf[L]+dp[bl+1][br-1]+pre[R];
	for(int i=bl+1;i<br;i++)ans+=cnt[i][r[bl]]-cnt[i][L-1]+cnt[i][R]-cnt[i][l[br]-1];
	for(int i=l[bl];i<=r[bl];i++){
		auto [val,id]=c[i];
		if(L<=id)x.emplace_back(val);
	}
	for(int i=l[br];i<=r[br];i++){
		auto [val,id]=c[i];
		if(id<=R)y.emplace_back(val);
	}
	return ans+calc(x,y);
}