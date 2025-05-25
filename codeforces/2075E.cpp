#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

mint binpow(mint a,ll b){
    mint res=1;
    while(b>0){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

void runcase(){
    int n,m,a,b;
    cin >> n >> m >> a >> b;
    a++,b++;
    auto work=[&](int n,int a){
        int p=0;
        map<int,mint> mp;
        vector<pair<int,int>> c;
        for(int i=29;i>=0;i--){
            if(!(a>>i&1))continue;
            for(auto [q,j]:c){
                int val=((p^q)>>j)<<j;
                mp[val]+=2<<i;
                mp[val+(1<<j)]-=2<<i;
            }
            mp[0]+=1<<i;
            mp[1<<i]-=1<<i;
            c.emplace_back(p,i);
            p|=1<<i;
        }
        mint cur=0;
        vector<tuple<int,int,mint>> res;
        int last=-1;
        for(auto [pos,val]:mp){
            if(last!=-1){
                res.emplace_back(last,pos-1,cur);
            }
            last=pos;
            cur+=val;
        }
        return res;
    };
    auto aa=work(n,a);
    auto bb=work(m,b);
    mint ans=0;
    ans+=mint(a)*mint(b);
    ans+=(binpow(2,n-1)-1)*mint(a)*mint(a-1)*mint(b);
    ans+=(binpow(2,m-1)-1)*mint(b)*mint(b-1)*mint(a);
    mint base=(binpow(2,n-1)-1)*(binpow(2,m-1)-1);
    for(int i=0,j=0;i<aa.size()&&j<bb.size();){
        auto &[l1,r1,v1]=aa[i];
        auto &[l2,r2,v2]=bb[j];
        int l=max({l1,l2,1});
        l1=max(l1,l);
        l2=max(l2,l);
        if(l1>r1){
            i++;
            continue;
        }
        if(l2>r2){
            j++;
            continue;
        }
        int r=min(r1,r2);
        ans+=base*v1*v2*(r-l+1);
        if(r1>r){
            l1=r+1;
        }else{
            i++;
        }
        if(r2>r){
            l2=r+1;
        }else{
            j++;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}