#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int d;
    cin >> d;
    vector<string> w(d);
    int mx=0;
    for(auto &x:w){
        cin >> x;
        mx=max(mx,(int)x.size());
    }
    vector<vector<int>> cnt(26,vector<int>(mx+1));
    for(auto &x:w){
        if((int)x.size()>mx)return void(cout << "0\n");
        cnt[x[0]-'a'][(int)x.size()]++;
    }
    int ans=0;
    for(auto &x:w){
        int s=x.size();
        if(s!=n)continue;
        cnt[x[0]-'a'][s]--;
        auto cnt2=cnt;
        int res=1;
        for(int i=0;i<n;i++){
            int &v=cnt2[x[i]-'a'][a[i]];
            res=1LL*res*v%MOD;
            v--;
        }
        ans=(ans+res)%MOD;
        cnt[x[0]-'a'][s]++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}