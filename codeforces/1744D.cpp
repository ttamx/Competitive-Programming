#include<bits/stdc++.h>

using namespace std;

void runcase(){
	int n;
	cin >> n;
	int tmp=0;
	vector<int> a(n);
	for(int i=1;i<=n;++i){
		int x;
		cin >> x;
		tmp+=log2(x&-x);
		a[log2(i&-i)]++;
	}
	int idx=n-1;
	int ans=0;
	while(idx>0&&tmp<n){
		while(a[idx]&&tmp<n){
			ans++;
			tmp+=idx;
			a[idx]--;
		}
		idx--;
	}	if(tmp<n){
		cout << -1 << '\n';
	}else{
		cout << ans << '\n';
	}
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int t(1);
	cin >> t;
	while(t--)runcase();
}
