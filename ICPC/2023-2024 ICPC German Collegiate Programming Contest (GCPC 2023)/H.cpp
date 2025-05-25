#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int F=30;
const int L=200;
const ll MOD=1e9+7;

mt19937 rng(MOD);

ll n;
ll f[F];
map<ll,int> dp,pre;

ll inv(ll a){
    ll res=1;
    for(int p=MOD-2;p>0;p>>=1){
        if(p&1)res=res*a%MOD;
        a=a*a%MOD;
    }
    return res;
}

int insert(ll val,int len,ll pval){
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    if(n==0){
        cout << ".##\n";
        cout << "##.\n";
        exit(0);
    }
    f[0]=1,f[1]=1;
    for(int i=2;i<F;i++){
        f[i]=(f[i-1]+f[i-2])%MOD;
    }
    while(true){
        int len=0;
        ll val=1;
        while(true){
            int i=rng()%(F-2)+2;
            val=val*f[i]%MOD;
            if(dp.count(val)&&dp[val]<=len){
                len=dp[val];
                continue;
            }
            if(len>0)len++;
            len+=i;
            if(len>L)break;
            dp[val]=len;
            pre[val]=i;
            if(val==n){
                vector<int> a;
                while(val!=1){
                    a.emplace_back(pre[val]);
                    val=val*inv(f[pre[val]])%MOD;
                }
                for(int t=0;t<2;t++){
                    for(int i=0;i<a.size();i++){
                        cout << string(a[i],'.') << "#\n"[i==a.size()-1];
                    }
                }
                exit(0);
            }
            ll val2=n*inv(val)%MOD;
            if(dp.count(val2)&&len+dp[val2]+1<=L){
                vector<int> a;
                while(val!=1){
                    a.emplace_back(pre[val]);
                    val=val*inv(f[pre[val]])%MOD;
                }
                while(val2!=1){
                    a.emplace_back(pre[val2]);
                    val2=val2*inv(f[pre[val2]])%MOD;
                }
                for(int t=0;t<2;t++){
                    for(int i=0;i<a.size();i++){
                        cout << string(a[i],'.') << "#\n"[i==a.size()-1];
                    }
                }
                exit(0);
            }
        }
    }
}