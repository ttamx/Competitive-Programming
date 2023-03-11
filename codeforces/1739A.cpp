#include<bits/stdc++.h>

using namespace std;

void runcase(){
	int n,m;
	cin >> n >> m;
	if(n==1||m==1)cout << 1 << ' ' << 1 << '\n';
	else cout << 2 << ' ' << 2 << '\n';
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int t(1);
	cin >> t;
	while(t--)runcase();
	return 0;
}