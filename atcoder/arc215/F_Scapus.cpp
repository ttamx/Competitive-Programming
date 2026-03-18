#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

template<class T=ll,int mod=0>
struct FFT{
	using vt = vector<T>;
	using cd = complex<db>;
	using vc = vector<cd> ;
	
	static const bool INT=true;

	static void fft(vc &a){
		int n=a.size(),L=31-__builtin_clz(n);
		vc rt(n);
		rt[1]=1;
		for(int k=2;k<n;k*=2){
			cd z=polar(db(1),PI/k);
			for(int i=k;i<2*k;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
		}
		vector<int> rev(n);
		for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
		for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
			cd z=rt[j+k]*a[i+j+k];
			a[i+j+k]=a[i+j]-z;
			a[i+j]+=z;
		}
	}
	template<class U>
	static db norm(const U &x){
		return INT?round(x):x;
	}
	static vt conv(const vt &a,const vt &b){
		if(a.empty()||b.empty())return {};
		vt res(a.size()+b.size()-1);
		int L=32-__builtin_clz(res.size()),n=1<<L;
		vc in(n),out(n);
		copy(a.begin(),a.end(),in.begin());
		for(int i=0;i<b.size();i++)in[i].imag(b[i]);
		fft(in);
		for(auto &x:in)x*=x;
		for(int i=0;i<n;i++)out[i]=in[-i&(n-1)]-conj(in[i]);
		fft(out);
		for(int i=0;i<res.size();i++)res[i]=norm(imag(out[i])/(4*n));
		return res;
	}
	static vl convMod(const vl &a,const vl &b){
		assert(mod>0);
		if(a.empty()||b.empty())return {};
		vl res(a.size()+b.size()-1);
		int L=32-__builtin_clz(res.size()),n=1<<L;
		ll cut=int(sqrt(mod));
		vc in1(n),in2(n),out1(n),out2(n);
		for(int i=0;i<a.size();i++)in1[i]=cd(ll(a[i])/cut,ll(a[i])%cut); // a1 + i * a2
		for(int i=0;i<b.size();i++)in2[i]=cd(ll(b[i])/cut,ll(b[i])%cut); // b1 + i * b2
		fft(in1),fft(in2);
		for(int i=0;i<n;i++){
			int j=-i&(n-1);
			out1[j]=(in1[i]+conj(in1[j]))*in2[i]/(2.l*n); // f1 * (g1 + i * g2) = f1 * g1 + i f1 * g2
			out2[j]=(in1[i]-conj(in1[j]))*in2[i]/cd(0.l,2.l*n); // f2 * (g1 + i * g2) = f2 * g1 + i f2 * g2
		}
		fft(out1),fft(out2);
		for(int i=0;i<res.size();i++){
			ll x=round(real(out1[i])),y=round(imag(out1[i]))+round(real(out2[i])),z=round(imag(out2[i]));
			res[i]=((x%mod*cut+y)%mod*cut+z)%mod; // a1 * b1 * cut^2 + (a1 * b2 + a2 * b1) * cut + a2 * b2
		}
		return res;
	}
	vt operator()(const vt &a,const vt &b){
		return mod>0?convMod(a,b):conv(a,b);
	}
};
template<>
struct FFT<db>{
	static const bool INT=false;
};

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int opt=n-1;
    vector<int> mx(n),mx2(n),dp(n),par(n,-1),sz(n);
    vector<bool> mark(n);
    vector<int> ed;
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            mx2[u]=max(mx2[u],mx[v]+1);
            if(mx2[u]>mx[u])swap(mx[u],mx2[u]);
        }
        dp[u]=mx[u];
        for(auto v:adj[u])if(v!=p){
            dp[u]=min(dp[u],max(dp[v],mx[v]+1==mx[u]?mx2[u]:mx[u]));
        }
    };
    function<void(int,int,int)> dfs2=[&](int u,int p,int d){
        array<int,3> f{d,d,d};
        for(auto v:adj[u])if(v!=p){
            auto nf=f;
            for(auto &x:nf)x=max(x,mx[v]+1);
            for(int i=0;i<2;i++){
                nf[i+1]=min(nf[i+1],max(f[i],dp[v]));
            }
            f=move(nf);
        }
        opt=min(opt,f[2]);
        for(auto v:adj[u])if(v!=p){
            dfs2(v,u,max(d,mx[v]+1==mx[u]?mx2[u]:mx[u])+1);
        }
    };
    function<void(int,int,int)> dfs3=[&](int u,int p,int d){
        int val=(d>mx[u]?mx[u]:max(d,mx2[u]))+1;
        if(val>opt){
            mark[u]=true;
        }
        for(auto v:adj[u])if(v!=p){
            dfs3(v,u,max(d,mx[v]+1==mx[u]?mx2[u]:mx[u])+1);
        }
    };
    function<void(int)> dfs4=[&](int u){
        sz[u]=1;
        bool ok=false;
        for(auto v:adj[u])if(v!=par[u]){
            par[v]=u;
            dfs4(v);
            if(mark[v]){
                mark[u]=true;
                ok=true;
            }else{
                sz[u]+=sz[v];
            }
        }
        if(mark[u]&&!ok){
            ed.emplace_back(u);
        }
    };
    function<void(int,int,int,vector<ll>&)> dfs5=[&](int u,int p,int d,vector<ll> &vec){
        if(vec.size()==d)vec.emplace_back(0);
        vec[d]++;
        for(auto v:adj[u])if(v!=par[u]&&!mark[v]){
            dfs5(v,u,d+1,vec);
        }
    };
    dfs(0,-1);
    dfs2(0,-1,0);
    dfs3(0,-1,0);
    int root=-1;
    for(int i=0;i<n;i++)if(mark[i]){
        root=i;
        break;
    }
    assert(root!=-1);
    dfs4(root);
    int len=count(mark.begin(),mark.end(),true);
    FFT fft;
    vector<ll> c(n);
    if(len==1){
        vector<vector<ll>> a(n);
        int buf=0;
        for(auto u:adj[root]){
            a[buf]={0};
            dfs5(u,root,1,a[buf]);
            buf++;
        }
        vector<int> ord(buf);
        iota(ord.begin(),ord.end(),0);
        sort(ord.begin(),ord.end(),[&](int i,int j){
            return a[i].size()<a[j].size();
        });
        vector<ll> b{1};
        c[0]=1;
        for(auto u:ord){
            auto cc=fft(b,a[u]);
            for(int i=0;i<cc.size();i++)c[i]+=cc[i];
            b.resize(a[u].size(),0LL);
            for(int i=0;i<a[u].size();i++)b[i]+=a[u][i];
        }
    }else{
        vector<ll> a,b;
        if(ed.size()==1)ed.emplace_back(root);
        assert(ed.size()==2);
        dfs5(ed[0],-1,0,a);
        dfs5(ed[1],-1,0,b);
        c=FFT()(a,b);
    }
    vector<ll> ans(n);
    for(int i=0;i<c.size()&&i+len<=n;i++)ans[i+len-1]=c[i];
    for(auto x:ans)cout << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}