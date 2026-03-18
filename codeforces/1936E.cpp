#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

template<class T>
constexpr T binpow(T a,ll b){
    T res{1};
    for(;b>0;b>>=1,a*=a)if(b&1)res*=a;
    return res;
}

template<class mint>
struct NTT{
	using vm = vector<mint>;
	
	static constexpr int mod=mint::get_mod();
	static constexpr mint root=mint::get_root();
    static_assert(root!=0);

	static void ntt(vm &a){
		int n=a.size(),L=31-__builtin_clz(n);
		vm rt(n);
		rt[1]=1;
		for(int k=2,s=2;k<n;k*=2,s++){
			mint z[]={1,binpow(root,mod>>s)};
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

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<int> p(n+1);
    for(int i=1;i<=n;i++){
        cin >> p[i];
        p[i]=max(p[i],p[i-1]);
    }
    vector<mint> dp(n+1),dp2(n+1);
    dp[0]=-1;
    function<void(int,int)> rec=[&](int l,int r){
        if(r-l<=1){
            if(l>0&&p[l]!=p[l-1]){
                dp[l]=dp[l]*l-dp2[l];
            }
            dp[l]*=-comb.ifac(p[l]-l);
            return;
        }
        int m=(l+r)/2;
        rec(l,m);
        mint val=0;
        for(int i=m-1;i>=l&&p[i]==p[m];i--){
            val+=dp[i]*comb.fac(p[m]-i-1);
        }
        for(int i=m;i<r&&p[i]==p[m];i++){
            dp[i]-=val;
        }
        int lo=p[m]-m,hi=p[r-1]-l;
        vector<mint> f(m-l),f2(m-l),g(hi-lo);
        for(int i=l;i<m;i++){
            f[i-l]=dp[i];
            f2[i-l]=dp[i]*i;
        }
        for(int i=lo;i<hi;i++){
            g[i-lo]=comb.fac(i);
        }
        f=NTT<mint>::conv(f,g);
        f2=NTT<mint>::conv(f2,g);
        for(int i=m;i<r;i++){
            dp[i]+=f[p[i]-l-lo-1];
            dp2[i]+=f2[p[i]-l-lo-1];
        }
        rec(m,r);
    };
    rec(0,n+1);
    mint ans=0;
    for(int i=0;i<n;i++){
        ans+=dp[i]*comb.fac(n-i);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}