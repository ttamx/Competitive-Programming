#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n;
int q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    while(q--){
        ll x;
        cin >> x;
        if(x>n*(n+1)/2){
            cout << 0 << '\n';
            continue;
        }
        ll ans=0;
        set<pair<int,int>> s;
        if(x%(n+1)==0){
            ans+=max(0ll,(n/2)-(x/(n+1))+1);
        }else{
            int cnt=x/(n+1);
            int left=x%(n+1);
            if(left<=(n+1)/2){
                int r=(left*2)-1;
                int l=r-(2*cnt);
                if(l>0)s.insert({l,r});
            }else{
                int l=(n-left+1)*2;
                int r=l+(2*cnt);
                if(r<=n)s.insert({l,r});
            }
        }
        if(x%(n+2)==0){
            ans+=max(0ll,((n-1)/2)-(x/(n+2))+1);
        }else{
            int cnt=x/(n+2);
            int left=x%(n+2);
            if(left<=(n+1)/2){
                int l=(left*2)-1;
                int r=l+(2*cnt);
                if(r<=n)s.insert({l,r});
            }else{
                int r=(n-left+1)*2;
                int l=r-(2*cnt);
                if(l>0)s.insert({l,r});
            }
        }
        ans+=s.size();
        cout << ans << '\n';
    }
}
