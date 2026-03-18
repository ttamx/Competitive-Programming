#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

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

template<class mint>
struct FormalPowerSeries:vector<mint>{
    using vector<mint>::vector;
    using FPS = FormalPowerSeries;

    FPS &operator+=(const FPS &rhs){
        if(rhs.size()>this->size())this->resize(rhs.size());
        for(int i=0;i<rhs.size();i++)(*this)[i]+=rhs[i];
        return *this;
    }
    FPS &operator+=(const mint &rhs){
        if(this->empty())this->resize(1);
        (*this)[0]+=rhs;
        return *this;
    }
    FPS &operator-=(const FPS &rhs){
        if(rhs.size()>this->size())this->resize(rhs.size());
        for(int i=0;i<rhs.size();i++)(*this)[i]-=rhs[i];
        return *this;
    }
    FPS &operator-=(const mint &rhs){
        if(this->empty())this->resize(1);
        (*this)[0]-=rhs;
        return *this;
    }
    FPS &operator*=(const FPS &rhs){
        auto res=NTT<mint>()(*this,rhs);
        return *this=FPS(res.begin(),res.end());
    }
    FPS &operator*=(const mint &rhs){
        for(auto &a:*this)a*=rhs;
        return *this;
    }
    friend FPS operator+(FPS lhs,const FPS &rhs){return lhs+=rhs;}
    friend FPS operator+(FPS lhs,const mint &rhs){return lhs+=rhs;}
    friend FPS operator+(const mint &lhs,FPS &rhs){return rhs+=lhs;}
    friend FPS operator-(FPS lhs,const FPS &rhs){return lhs-=rhs;}
    friend FPS operator-(FPS lhs,const mint &rhs){return lhs-=rhs;}
    friend FPS operator-(const mint &lhs,FPS rhs){return -(rhs-lhs);}
    friend FPS operator*(FPS lhs,const FPS &rhs){return lhs*=rhs;}
    friend FPS operator*(FPS lhs,const mint &rhs){return lhs*=rhs;}
    friend FPS operator*(const mint &lhs,FPS rhs){return rhs*=lhs;}
    
    FPS operator-(){return (*this)*-1;}

    FPS rev(){
        FPS res(*this);
        reverse(res.beign(),res.end());
        return res;
    }
    FPS pre(int sz){
        FPS res(this->begin(),this->begin()+min((int)this->size(),sz));
        if(res.size()<sz)res.resize(sz);
        return res;
    }
    FPS shrink(){
        FPS res(*this);
        while(!res.empty()&&res.back()==mint{})res.pop_back();
        return res;
    }
    FPS operator>>(int sz){
        if(this->size()<=sz)return {};
        FPS res(*this);
        res.erase(res.begin(),res.begin()+sz);
        return res;
    }
    FPS operator<<(int sz){
        FPS res(*this);
        res.insert(res.begin(),sz,mint{});
        return res;
    }
    FPS diff(){
        const int n=this->size();
        FPS res(max(0,n-1));
        for(int i=1;i<n;i++)res[i-1]=(*this)[i]*mint(i);
        return res;
    }
    FPS integral(){
        const int n=this->size();
        FPS res(n+1);
        res[0]=0;
        if(n>0)res[1]=1;
        ll mod=mint::get_mod();
        for(int i=2;i<=n;i++)res[i]=(-res[mod%i])*(mod/i);
        for(int i=0;i<n;i++)res[i+1]*=(*this)[i];
        return res;
    }
    mint eval(const mint &x){
        mint res=0,w=1;
        for(auto &a:*this)res+=a*w,w*=x;
        return res;
    }

    FPS inv(int deg=-1){
        assert(!this->empty()&&(*this)[0]!=mint(0));
        if(deg==-1)deg=this->size();
        FPS res{mint(1)/(*this)[0]};
        for(int i=2;i>>1<deg;i<<=1){
            res=(res*(mint(2)-res*pre(i))).pre(i);
        }
        return res.pre(deg);
    }
    FPS log(int deg=-1){
        assert(!this->empty()&&(*this)[0]==mint(1));
        if(deg==-1)deg=this->size();
        return (pre(deg).diff()*inv(deg)).pre(deg-1).integral();
    }
    FPS exp(int deg=-1){
        assert(this->empty()||(*this)[0]==mint(0));
        if(deg==-1)deg=this->size();
        FPS res{mint(1)};
        for(int i=2;i>>1<deg;i<<=1){
            res=(res*(pre(i)-res.log(i)+mint(1))).pre(i);
        }
        return res.pre(deg);
    }
    FPS pow(ll k,int deg=-1){
        const int n=this->size();
        if(deg==-1)deg=n;
        if(k==0){
            FPS res(deg);
            if(deg)res[0]=mint(1);
            return res;
        }
        for(int i=0;i<n;i++){
            if(__int128_t(i)*k>=deg)return FPS(deg,mint(0));
            if((*this)[i]==mint(0))continue;
            mint rev=mint(1)/(*this)[i];
            FPS res=(((*this*rev)>>i).log(deg)*k).exp(deg);
            res=((res*binpow((*this)[i],k))<<(i*k)).pre(deg);
            return res;
        }
        return FPS(deg,mint(0));
    }
};

using mint = mint998;
using FPS = FormalPowerSeries<mint>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> cnt(6);
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    FPS f(n+1);
    f[0]=1;
    for(int s=1;s<=5;s++){
        if(cnt[s]==0)continue;
        FPS g(n+1);
        vector<mint> dp(s+1);
        dp[s]=1;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=s;j++){
                dp[j-1]+=dp[j]*j;
                dp[j]*=m-j;
            }
            g[i]=dp[0];
            dp[0]=0;
        }
        f*=g.pow(cnt[s],n+1);
        f.resize(n+1);
    }
    for(int i=1;i<=n;i++){
        f[i]+=f[i-1]*m;
    }
    cout << f[n] << "\n";
}