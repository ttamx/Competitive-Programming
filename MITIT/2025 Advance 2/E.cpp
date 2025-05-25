#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
	cin >> n;
	int mx=1;
	vector<int> have;
    vector<int> a(n);
	for(int i=0;i<n;i++){
        cin >> a[i];
        have.emplace_back(a[i]);
    }
	sort(have.begin(),have.end());
	have.erase(unique(have.begin(),have.end()),have.end());
    int col=-1;
    int last=n;
	for(auto i:have){
        int cur=0;
		for(int j=0;j<n;j++){
			if(a[j]==i)cur++;
            else cur=max(cur-1,0);
			mx=max(mx,cur);
            if(cur>mx||(cur==mx&&i<last)){
                col=i;
                last=i;
            }
		}
	}
    cout << mx << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}