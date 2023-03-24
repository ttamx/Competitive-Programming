#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

typedef long long ll;

int n,m,q;
int s[N];
ll sum=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        cin >> s[i];
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
    }
    sum=m;
    int cnt=0;
    for(int i=1;i<n;i++){
        if(s[i]==2)cnt++;
    }
    if(cnt==0&&s[n]==2)cnt++;
    else if(cnt>0&&s[1]==1)cnt++;
    cout << sum+cnt;
}