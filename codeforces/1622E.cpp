#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<string> s(n);
    for(auto &x:s)cin >> x;
    int best=-1;
    vector<int> ans(m,-1);
    for(int mask=0;mask<(1<<n);mask++){
        vector<pair<int,int>> b(m);
        int res=0;
        for(int i=0;i<n;i++){
            res+=(mask>>i&1)?-a[i]:a[i];
            for(int j=0;j<m;j++){
                if(s[i][j]=='1'){
                    b[j].first+=(mask>>i&1)?1:-1;
                }
            }
        }
        for(int i=0;i<m;i++)b[i].second=i;
        sort(b.begin(),b.end());
        for(int i=0;i<m;i++)res+=b[i].first*(i+1);
        if(res>best){
            best=res;
            for(int i=0;i<m;i++)ans[b[i].second]=i;
        }
    }
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}