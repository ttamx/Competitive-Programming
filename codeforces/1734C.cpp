#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    s=" "+s;
    long long ans=0;
    vector<bool> del(n+1);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            if(del[j])continue;
            if(s[j]=='1')break;
            del[j]=true;
            ans+=i;
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