#include<bits/stdc++.h>

using namespace std;

void runcase(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	int idx=0;
	while(idx<n&&s[idx]=='0')idx++;
	if(idx==n){
		cout << 0 << '\n';
		return;
	}
	int sz=n-idx;
	string ans=s.substr(idx,sz);
	vector<int> need;
	for(int i=idx;i<n;++i)if(s[i]=='0')need.emplace_back(i);
	if(need.empty()){
		cout << ans << '\n';
		return;
	}
	int req=n-need[0];
	string ans2=ans;
	for(int i=idx;i<need[0];i++){
		string tmp=ans;
		string add=s.substr(i,req);		for(int j=0;j<req;j++){
			if(add[req-1-j]=='1')tmp[sz-j-1]='1';
		}		ans2=max(ans2,tmp);
	}
	cout << ans2;
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int t(1);
	while(t--)runcase();
}
