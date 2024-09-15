#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    map<string,int> id;
    vector<bool> b(n),c(n);
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        id[s]=i;
    }
    for(int i=0;i<m;i++){
        string s;
        cin >> s;
        b[id[s]]=true;
    }
    for(int i=0;i<k;i++){
        string s;
        cin >> s;
        c[id[s]]=true;
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(b[i]^c[i]){
            ans++;
        }
    }
    ans=min(ans,1+min(k,n-k));
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}