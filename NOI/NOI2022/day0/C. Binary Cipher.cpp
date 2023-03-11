#include<bits/stdc++.h>

using namespace std;

int q,k;

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> q >> k;
	while(q--){
		int c;
		cin >> c;
		if((k&c)==k)cout << (c^k) << '\n';
		else cout << -1 << '\n';
	}
	return 0;
}
