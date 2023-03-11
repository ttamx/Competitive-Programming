#include<bits/stdc++.h>

using namespace std;

void runcase(){
	int n;
	cin >> n;
	for(int i=0;i<n;++i){
		int x;
		cin >> x;
	}
	cout << (10-n)*(9-n)*3 << '\n';
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int t(1);
	cin >> t;
	while(t--)runcase();
}
