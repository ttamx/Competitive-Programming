#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int MOD=998244353;

ll binpow(ll a,ll b,ll m){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%m;
        a=a*a%m;
        b>>=1;
    }
    return res;
}

int n,k,m,t,r;
vector<int> factor;
bool mark[N];
ll ex[N],lg[N];

const ll root=3;

void ntt(vector<ll> &a){
    int n=a.size(),L=31-__builtin_clz(n);
    vector<ll> rt(n);
    rt[1]=1;
    for(int k=2,s=2;k<n;k*=2,s++){
        ll z[]={1,binpow(root,MOD>>s,MOD)};
        for(int i=k;i<2*k;i++)rt[i]=rt[i/2]*z[i&1]%MOD;
    }
    vector<int> rev(n);
    for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
    for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
    for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
        ll z=rt[j+k]*a[i+j+k]%MOD;
        a[i+j+k]=(a[i+j]-z+MOD)%MOD;
        a[i+j]=(a[i+j]+z)%MOD;
    }
}

vector<ll> conv(const vector<ll> &a,const vector<ll> &b){
    if(a.empty()||b.empty())return {};
    int s=a.size()+b.size()-1,n=1<<(32-__builtin_clz(s));
    ll inv=binpow(n,MOD-2,MOD);
    vector<ll> in1(a),in2(b),out(n);
    in1.resize(n),in2.resize(n);
    ntt(in1),ntt(in2);
    for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]%MOD*inv%MOD;
    ntt(out);
    return vector<ll>(out.begin(),out.begin()+s);
}

vector<ll> conv2(const vector<ll> &a,const vector<ll> &b){
    vector<ll> fa(m-1),fb(m-1);
    for(int i=0;i<m-1;i++){
        fa[i]=a[ex[i]];
        fb[i]=b[ex[i]];
    }
    auto fc=conv(fa,fb);
    for(int i=m-1;i<fc.size();i++){
        fc[i-(m-1)]=(fc[i-(m-1)]+fc[i])%MOD;
    }
    vector<ll> c(m);
    for(int i=1;i<m;i++){
        c[i]=fc[lg[i]];
    }
    ll sa=accumulate(a.begin(),a.end(),0LL)%MOD;
    ll sb=accumulate(b.begin(),b.end(),0LL)%MOD;
    c[0]=(sa*b[0]%MOD+sb*a[0]%MOD-a[0]*b[0]%MOD+MOD)%MOD;
    return c;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> m >> t;
    vector<ll> a(m);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x]++;
    }
    for(int i=1;i<m;i++){
        if((m-1)%i==0){
            factor.emplace_back(i);
        }
    }
    r=-1;
    for(int i=1;i<m;i++){
        bool ok=true;
        vector<int> val;
        for(auto d:factor){
            int v=binpow(i,d,m);
            if(mark[v]){
                ok=false;
                break;
            }
            mark[v]=true;
            val.emplace_back(v);
        }
        if(ok){
            r=i;
            break;
        }
        for(auto v:val){
            mark[v]=false;
        }
    }
    assert(r!=-1);
    ex[0]=1;
    for(int i=0;i<m-2;i++){
        ex[i+1]=ex[i]*r%m;
    }
    for(int i=0;i<m-1;i++){
        lg[ex[i]]=i;
    }
    vector<ll> ans(m);
    ans[1]=1;
    while(t>0){
        if(t&1)ans=conv2(ans,a);
        a=conv2(a,a);
        t>>=1;
    }
    cout << ans[k] << "\n";
}