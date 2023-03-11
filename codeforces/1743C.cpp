#include<bits/stdc++.h>

using namespace std;

void runcase(){
	int n;
	cin >> n;
	string s;
	cin >> s;
	int ans=0;
	vector<int> a(n);
	for(int i=0;i<n;++i){
		cin >> a[i];
	}
	int idx=0;
	while(idx<n&&s[idx]=='1'){
		ans+=a[idx];
		idx++;
	}
	while(idx<n){
		if(s[idx]=='1'&&s[idx-1]=='0'){
			int sum=a[idx-1];
			int mn=a[idx-1];
			while(s[idx]=='1'){
				mn=min(mn,a[idx]);
				sum+=a[idx];
				idx++;
			}
			ans+=sum-mn;
		}else{
			++idx;
			
		}
	}
	cout << ans << '\n';
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int t(1);
	cin >> t;
	while(t--)runcase();
}
