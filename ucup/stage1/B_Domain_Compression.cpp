#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

template<class T>
constexpr T binpow(T a,ll b){
    T res=1;
    for(;b>0;b>>=1,a*=a)if(b&1)res*=a;
    return res;
}

struct NTT{
	using vm = vector<mint>;
	
	static constexpr mint root=mint::get_root();
    static_assert(root!=0);

	static void ntt(vm &a){
		int n=a.size(),L=31-__builtin_clz(n);
		vm rt(n);
		rt[1]=1;
		for(int k=2,s=2;k<n;k*=2,s++){
			mint z[]={1,binpow(root,MOD>>s)};
			for(int i=k;i<2*k;i++)rt[i]=rt[i/2]*z[i&1];
		}
		vector<int> rev(n);
		for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
		for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
			mint z=rt[j+k]*a[i+j+k];
			a[i+j+k]=a[i+j]-z;
			a[i+j]+=z;
		}
	}
	static vm conv(const vm &a,const vm &b){
		if(a.empty()||b.empty())return {};
		int s=a.size()+b.size()-1,n=1<<(32-__builtin_clz(s));
		mint inv=mint(n).inv();
		vm in1(a),in2(b),out(n);
		in1.resize(n),in2.resize(n);
		ntt(in1),ntt(in2);
		for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]*inv;
		ntt(out);
		return vm(out.begin(),out.begin()+s);
	}
	vm operator()(const vm &a,const vm &b){
		return conv(a,b);
	}
};

const int N=1e5+5;

int n;
vector<int> adj[N];
int sz[N],dep[N];
bool used[N];
vector<mint> cnt;
mint c[N];

int getsz(int u,int p=-1){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=getsz(v,u);
    return sz[u];
}

int getdep(int u,int p=-1){
    dep[u]=0;
    for(auto v:adj[u])if(v!=p&&!used[v])dep[u]=max(dep[u],getdep(v,u));
    return ++dep[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt/2)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,int d=1,int p=-1){
    cnt[d]++;
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,d+1,u);
}

void decom(int u){
    u=centroid(u,getsz(u));
    getdep(u);
    used[u]=true;
    sort(adj[u].begin(),adj[u].end(),[&](int i,int j){
        return dep[i]<dep[j];
    });
    vector<mint> cur(1,1);
    for(auto v:adj[u])if(!used[v]){
        cnt.assign(dep[v]+1,0);
        cur.resize(dep[v]+1);
        dfs(v);
        vector<mint> tmp=NTT::conv(cur,cnt);
        for(int i=1;i<tmp.size();i++)c[i]+=tmp[i];
        for(int i=0;i<cnt.size();i++)cur[i]+=cnt[i];
    }
    for(auto v:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    decom(1);
    vector<mint> f(n+1),g(n+1);
    for(int i=0;i<n-1;i++){
        f[i]=c[i+1]*comb.fac(n-i-2);
    }
    for(int i=0;i<=n;i++){
        g[i]=comb.ifac(i);
    }
    vector<mint> h=NTT::conv(f,g);
    for(int i=1;i<=n;i++){
        mint res=0;
        if(i<=n-2){
            res=h[i]*comb.ifac(n-i-2)*comb.fac(i);
        }
        cout << res << " \n"[i==n];
    }
}