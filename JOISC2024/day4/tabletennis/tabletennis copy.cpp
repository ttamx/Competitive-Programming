#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;

int n,q;
ll m;
ll dp[N];
string ans[N];

bool solve(int n,ll m,int p){
    if(m==0)return true;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            for(int k=j;k<=n;k++){
                if(i+j+k>n)continue;
                ll mn=1LL*i*j*k;
                ll mx=mn+dp[i]+dp[j]+dp[k];
                if(mn>m||mx<m)continue;
                ll val=m-mn;
                ll tmp=min(val,dp[i]);
                if(!solve(i,tmp,p))return false;
                val-=tmp;
                tmp=min(val,dp[j]);
                if(!solve(j,tmp,p+i))return false;
                val-=tmp;
                tmp=min(val,dp[k]);
                if(!solve(k,tmp,p+i+j))return false;
                val-=tmp;
                for(int x=0;x<k;x++){
                    for(int y=0;y<i;y++){
                        ans[p+i+j+x][p+y-1]='1';
                    }
                }
                assert(val==0);
                return true;
            }
        }
    }
    return false;
}

int sz=3;

void calcdp(int s){
    if(s<=sz)return;
    for(int i=sz+1;i<=s;i++){
        for(int x=1;x<=i;x++){
            for(int y=x;y<=i;y++){
                int z=i-x-y;
                if(z<=0)break;
                dp[i]=max(dp[i],1LL*x*y*z+dp[x]+dp[y]+dp[z]);
            }
        }
    }
    sz=s;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[3]=1;
    cin >> q;
    while(q--){
        cin >> n >> m;
        calcdp(n);
        for(int i=2;i<=n;i++)ans[i]=string(i-1,'0');
        if(!solve(n,m,1)){
            cout << "No\n";
        }else{
            cout << "Yes\n";
            for(int i=2;i<=n;i++)cout << ans[i] << "\n";
        }
    }
}