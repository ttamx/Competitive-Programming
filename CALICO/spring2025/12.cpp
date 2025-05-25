#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=1000000007;
const int LG=40;
const int M=550;

const int N=1000;

int term[N],len[N],to[N][2],link[N],buf;
int que[N],st,fi;
int val[N];

ll dp[LG][M][M];
ll ans[M][M],nans[M][M];

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

ll inv(ll x){
    return binpow(x,MOD-2);
}

void runcase(){
    ll n;
    int k;
    cin >> n >> k;
    ll x,y,w1,w2,l1,l2;
    cin >> x >> y >> w1 >> w2 >> l1 >> l2;
    ll w=w1*inv(w2)%MOD;
    ll l=l1*inv(l2)%MOD;
    buf=1;
    vector<string> s(k);
    for(auto &x:s){
        cin >> x;
        reverse(x.begin(),x.end());
    }
    sort(s.begin(),s.end());
    vector<pair<string,int>> ss;
    for(int i=0;i<k;i++){
        bool ok=true;
        for(auto &[str,v]:ss){
            if(str.size()>s.size())continue;
            bool match=true;
            for(int j=0;j<str.size();j++){
                if(s[i][j]!=str[j]){
                    match=false;
                    v^=1;
                    break;
                }
            }
            if(match){
                ok=false;
                break;
            }
        }
        if(ok)ss.emplace_back(s[i],1);
    }
    for(auto &[str,v]:ss){
        reverse(str.begin(),str.end());
        int cur=0;
        for(auto c:str){
            bool b=c=='W';
            if(!to[cur][b]){
                to[cur][b]=buf++;
                len[to[cur][b]]=len[cur]+1;
            }
            cur=to[cur][b];
        }
        term[cur]=cur;
        val[cur]=v;
    }
    st=0,fi=1;
    que[0]=0;
    while(st<fi){
        int V=que[st++];
        int U=link[V];
        if(!term[V])term[V]=term[U];
        for(int c=0;c<2;c++){
            if(to[V][c]){
                link[to[V][c]]=V?to[U][c]:0;
                que[fi++]=to[V][c];
            }else{
                to[V][c]=to[U][c];
            }
        }
    }
    for(int i=0;i<LG;i++){
        for(int j=0;j<=buf*2;j++){
            for(int k=0;k<=buf*2;k++){
                dp[i][j][k]=0;
            }
        }
    }
    dp[0][0][0]=1;
    for(int i=1;i<=buf;i++){
        for(int c=0;c<2;c++){
            ll wp=(c?w:l);
            ll lp=(MOD+1-wp)%MOD;
            int v1=to[i][0];
            dp[0][i*2-c][v1*2-(c^val[v1])]=lp;
            int v2=to[i][1];
            dp[0][i*2-c][v2*2-(c^val[v2])]=wp;
        }
    }
    for(int i=1;i<=buf*2;i++){
        for(int j=1;j<=buf*2;j++){
            dp[0][i][j]%=MOD;
        }
    }
    for(int b=1;b<LG;b++){
        for(int i=1;i<=buf*2;i++){
            for(int j=1;j<=buf*2;j++){
                for(int k=1;k<=buf*2;k++){
                    dp[b][i][j]=(dp[b][i][j]+dp[b-1][i][k]*dp[b-1][k][j])%MOD;
                }
            }
        }
    }
    for(int i=1;i<=buf*2;i++){
        for(int j=1;j<=buf*2;j++){
            ans[i][j]=(i==j);
        }
    }
    for(int b=LG-1;b>=0;b--){
        if(n>>b&1){
            for(int i=1;i<=buf*2;i++){
                for(int j=1;j<=buf*2;j++){
                    nans[i][j]=0;
                }
            }
            for(int i=1;i<=buf*2;i++){
                for(int j=1;j<=buf*2;j++){
                    for(int k=1;k<=buf*2;k++){
                        nans[i][j]=(nans[i][j]+ans[i][k]*dp[b][k][j])%MOD;
                    }
                }
            }
            for(int i=1;i<=buf*2;i++){
                for(int j=1;j<=buf*2;j++){
                    ans[i][j]=nans[i][j];
                }
            }
        }
    }
    ll sum=0;
    for(int i=1;i<=2*buf;i++)sum+=ans[1][i];
    cout << sum%MOD << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}