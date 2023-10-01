#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    if(a.back()==1)return void(cout << "NO\n");
    cout << "YES\n";
    vector<int> ans;
    int l=0,r=n-1;
    int idx=n-1;
    int res=0;
    while(idx>=0){
        int cnt=0;
        while(idx>=0&&a[idx]==res){
            idx--;
            cnt++;
        }
        if(idx<0)break;
        res^=1;
        ans.emplace_back(idx+1);
    }
    reverse(ans.begin(),ans.end());
    for(int i=0;i<n-ans.size();i++)cout << 0 << " ";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}