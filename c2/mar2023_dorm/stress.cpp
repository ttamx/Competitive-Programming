#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct SUB3{

static const int N=305;

ll n;
ll a[N];
ll sum=0;
ll dp[N][N];
ll ans[N];

SUB3(){
    n=0,sum=0;
    for(int i=0;i<N;i++)a[i]=ans[i]=0;
    for(int i=0;i<N;i++)for(int j=0;j<N;j++)dp[i][j]=0;
}

ll calc(ll val,ll p){
    p++;
    if(p>=val)return val;
    ll num=val/p;
    ll rem=val-num*p;
    return rem*((num+1)*(num+1))+(p-rem)*num*num;
}

void init(int N,vector<vector<int> > Req){
    n=N;
    for(auto v:Req){
        int l=v[0],r=v[1];
        l++,r++;
        a[l]++;
        a[r+1]--;
        sum+=r-l+1;
    }
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    for(int i=1;i<=n;i++){
        for(int j=0;j<305;j++){
            dp[i][j]=1e18;
            for(int k=0;k<=j;k++){
                dp[i][j]=min(dp[i][j],dp[i-1][j-k]+calc(a[i],k));
            }
        }
    }
}

ll least_crowded(int P){
    return dp[n][P];
}

};

struct SOL{

static const int N=3005;
static const int M=1e5+5;

int n;
int a[N];
ll base;
vector<tuple<ll,ll,ll>> sub;

SOL(){
    n=0,base=0;
    for(int i=0;i<N;i++)a[i]=0;
    sub.clear();
}

ll pw2(ll x){
    return x*x;
}

int cdiv(int a,int b){
    return (a-1)/b+1;
}

ll calc(int i,int x){
    x++;
    ll sz=a[i]/x;
    ll cnt=x-a[i]%x;
    return pw2(sz)*cnt+pw2(sz+1)*(x-cnt);
}

void add(ll dif,ll sz){
    sub.emplace_back(dif,dif*sz,sz);
}

void init(int N,vector<vector<int>> Req){
    n=N;
    for(auto x:Req)a[x[0]+1]++,a[x[1]+2]--;
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    for(int i=1;i<=n;i++)if(a[i]){
        base+=pw2(a[i]);
        int val=a[i];
        int cnt=0;
        vector<pair<int,int>> vec;
        vec.emplace_back(val,0);
        while(val>1){
            int l=cnt+1,r=a[i]-1;
            while(l<r){
                int m=(l+r)/2;
                if(cdiv(a[i],m+1)<val)r=m;
                else l=m+1;
            }
            val=cdiv(a[i],l+1);
            cnt=l;
            vec.emplace_back(val,cnt);
        }
        for(int j=0;j<vec.size()-1;j++){
            auto [val,cnt]=vec[j];
            int freq=(a[i]-1)%(cnt+1)+1;
            int ok=vec[j+1].second-1-cnt;
            add(calc(i,vec[j+1].second-1)-calc(i,vec[j+1].second),1);
            if(ok)add(pw2(val)*(val-1)-pw2(val-1)*val,ok);
        }
    }
    sort(sub.rbegin(),sub.rend());
    for(int i=1;i<sub.size();i++){
        get<1>(sub[i])+=get<1>(sub[i-1]);
        get<2>(sub[i])+=get<2>(sub[i-1]);
    }
}

long long least_crowded(int P){
    int l=0,r=sub.size();
    while(l<r){
        int m=(l+r)/2;
        if(get<2>(sub[m])>P)r=m;
        else l=m+1;
    }
    ll res=base;
    if(l){
        res-=get<1>(sub[l-1]);
        P-=get<2>(sub[l-1]);
    }
    if(l==sub.size())return res;
    res-=get<0>(sub[l])*P;
    return res;
}

};

mt19937 rng(0);

int rnd(){
    return rng();
}

int rnd(int x){
    int res=rnd()%x;
    return res<0?res+x:res;
}

int rnd(int l,int r){
    return l+rnd(r-l+1);
}

void runcase(){
    SUB3 sub3;
    SOL sol;
	int N,M,Q;
    N=rnd(1,20);
    M=rnd(1,20);
    Q=rnd(1,20);
    vector<vector<int> > Req(M,vector<int> (2,0));
    for(int i = 0;i < M;i++){
        int l=rnd(N),r=rnd(N);;
        if(l>r)swap(l,r);
        Req[i][0]=l;
        Req[i][1]=r;
    }
    int P[Q];
    for(int i = 0;i < Q;i++){
        P[i]=rnd(1,300);
    }
    sub3.init(N,Req);
    sol.init(N,Req);
    for(int i = 0;i < Q;i++){
        ll ans=sub3.least_crowded(P[i]);
        ll out=sol.least_crowded(P[i]);
        if(ans!=out){
            cout << N << " " << M << " " << Q << "\n";
            for(auto x:Req)cout << x[0] << " " << x[1] << "\n";
            for(auto x:P)cout << x << "\n";
            cerr << i << "th query: expected " << ans << " found " << out << ".\n";
            exit(0);
        }
    }
}

int main(){
    int T=1000;
    while(T--)runcase();
    cout << "passed";
}
