#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int B=20;
const int S=1<<B;
const ll MOD=1e9+7;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int n,b,s;
string s;
int a[N],cnt0[S],cnt1[S];
int mx=0;
bool done[S];
ll ans[S];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
        mx=max(mx,a[i]);
        cnt0[a[i]]++;
        cnt1[a[i]]++;
    }
    while((1<<b)<=mx)b++;
    s=1<<b;
    for(int j=0;j<b;j++){
        for(int i=0;i<s;i++){
            if(i>>j&1){
                cnt0[i^(1<<j)]+=cnt0[i];
                cnt1[i]+=cnt1[i^(1<<j)];
            }
        }
    }
    for(int i=0;i<n;i++){
        int cur=a[i];
        if(done[cur]){
            cout << ans[cur] << "\n";
            continue;
        }
        done[cur]=true;
        
    }
}