#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

mint binpow(mint a,ll b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
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
		vi rev(n);
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
}ntt;

void runcase(){
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    int offset=count(s.begin(),s.end(),'1');
    vector<mint> a(n+1),b(2*n+1);
    for(int i=0;i<=n;i++){
        a[i]=comb.C(n,i);
    }
    for(int i=0;i<=2*n;i++){
        ll v=i-n;
        b[i]=mint(v/2)*(v-v/2);
    }
    auto c=ntt(a,b);
    while(q--){
        int x;
        cin >> x;
        x--;
        if(s[x]=='0'){
            s[x]='1';
            offset++;
        }else{
            s[x]='0';
            offset--;
        }
        cout << c[2*n-offset] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}