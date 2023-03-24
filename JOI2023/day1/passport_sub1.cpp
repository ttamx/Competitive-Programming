#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,qr;
pair<int,int> a[N];
bool vis[N];
queue<pair<int,int>> q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        auto &[l,r]=a[i];
        cin >> l >> r;
    }
    cin >> qr;
    assert(qr==1);
    int st;
    cin >> st;
    assert(st==1);
    int ed=a[1].second;
    int ans=1;
    while(ed<n){
        if(st>ed){
            cout << -1;
            return 0;
        }
        ans++;
        int res=ed;
        while(st<=ed){
            res=max(res,a[st].second);
            st++;
        }
        ed=res;
    }
    cout << ans;
}