#include<bits/stdc++.h>

using namespace std;

using ll = long long;

vector<ll> pre[10][10];
vector<ll> suf[10][10];

void solve1(int n,int v,int mx,ll val){
    pre[n][mx].emplace_back(val);
    if(n==8)return;
    for(int i=v;i<=mx;i++){
        solve1(n+1,i,mx,val*10+i);
    }
}

void solve2(int n,int v,int mx,ll val){
    suf[n][mx].emplace_back(val);
    if(n==8)return;
    for(int i=v;i>=1;i--){
        solve2(n+1,i,mx,val*10+i);
    }
}

void runcase(){
    ll a,b,m;
    cin >> a >> b >> m;
    a=max(a,1LL);
    auto work=[&](ll lim){
        ll res=0;
        for(int v=1;v<=9;v++){
            ll mul=1;
            for(int len=0;len<=8;len++,mul*=10){
                map<int,int> cnt;
                int idx=0;
                for(auto x:pre[len][v-1]){
                    ll cur=(x*10+v)*mul;
                    while(idx<suf[len][v-1].size()&&cur+suf[len][v-1][idx]<=lim){
                        ll val=suf[len][v-1][idx];
                        cnt[val%m]++;
                        idx++;
                    }
                    res+=cnt[(m-cur%m)%m];
                }
            }
        }
        return res;
    };
    cout << work(b)-work(a-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    for(int i=0;i<9;i++)solve1(0,1,i,0);
    for(int i=0;i<9;i++)solve2(0,i,i,0);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            sort(pre[i][j].rbegin(),pre[i][j].rend());
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            sort(suf[i][j].begin(),suf[i][j].end());
        }
    }
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}