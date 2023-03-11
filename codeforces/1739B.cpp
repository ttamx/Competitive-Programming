#include<bits/stdc++.h>

using namespace std;

void runcase(){
	int n;
	cin >> n;
	int a[n];
	bool can=true;
	cin >> a[0];
	for(int i=1;i<n;++i){
		cin >> a[i];
		if(a[i]!=0 && a[i]<=a[i-1])can=false;
		a[i]+=a[i-1];
	}
	if(can)for(int i=0;i<n;++i)cout << a[i] << ' ';
	else cout << -1;
	cout << '\n';
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int t(1);
	cin >> t;
	while(t--)runcase();
	return 0;
}