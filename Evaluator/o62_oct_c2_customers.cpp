#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,q,k=4895;
int a[N],s[N],c[N],l[N];
vector<int> S[N],C[N];

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m >> q;
	for(int i=1;i<=m;++i){
		cin >> l[i];
		for(int j=0;j<l[i];++j){
			int x;
			cin >> x;
			S[i].push_back(x);
			if(l[i]>k)C[x].push_back(i);
		}
	}
	while(q--){
		int o;
		cin >> o;
		if(o==1){
			int x,y;
			cin >> x >> y;
			int add=y-a[x];
			a[x]=y;
			if(l[x]>k){
				s[x]+=add;
			}else{
				for(auto i:S[x]){
					c[i]+=add;
				}
			}
		}else{
			int x;
			cin >> x;
			int ans=c[x];
			for(auto i:C[x])ans+=s[i];
			cout << ans << '\n';
		}
	}
}