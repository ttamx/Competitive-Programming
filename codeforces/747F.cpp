#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=200;

ll C[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll k,t;
    cin >> k >> t;
    for(int i=0;i<N;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=min(C[i-1][j-1]+C[i-1][j],k);
        }
    }
    vector<int> a(16,t);
    auto calc=[&](int len){
        vector<ll> dp(len+1);
        dp[0]=1;
        for(auto x:a){
            for(int i=len;i>=0;i--){
                for(int j=1;j<=x&&i+j<=len;j++){
                    dp[i+j]=min(dp[i+j]+dp[i]*C[i+j][j],k);
                }
            }
        }
        return dp[len];
    };
    vector<int> b;
    for(int len=1;;len++){
        ll v=0;
        for(int i=1;i<16;i++){
            if(a[i]==0)continue;
            a[i]--;
            v=min(v+calc(len-1),k);
            a[i]++;
        }
        if(v<k){
            k-=v;
            continue;
        }
        int st=1;
        for(int dig=1;dig<=len;dig++){
            bool ok=true;
            for(int i=st;i<16;i++){
                if(a[i]==0)continue;
                a[i]--;
                ll w=calc(len-dig);
                if(w<k){
                    k-=w;
                    a[i]++;
                }else{
                    ok=true;
                    b.emplace_back(i);
                    break;
                }
            }
            assert(ok);
            st=0;
        }
        break;
    }
    for(auto x:b){
        if(x<10)cout << x;
        else cout << char('a'+x-10);
    }
    cout << "\n";
}