#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    int sa,sb;
    cin >> n >> sa >> sb;
    sa--,sb--;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    if(sa>sb){
        sa=n-sa-1;
        sb=n-sb-1;
        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());
    }
    b[sa]=a[sa];
    b[sb]=a[sb];
    for(int i=1;i<n;i++)b[i]+=b[i-1];
    auto get_sz=[&](int l,int r){
        return b[r]-(l?b[l-1]:0LL);
    };
    mint inv=mint(2).inv();
    vector<vector<mint>> suf(n+2,vector<mint>(n));
    for(int t=n;t>=1;t--){
        int lena=t/2,lenb=(t-1)/2;
        for(int i=lena;i+lenb+1<n;i++){
            ll sza=get_sz(i-lena,i);
            ll szb=get_sz(i+1,i+lenb+1);
            if(t&1){
                bool okl=(i>lena&&sza>=a[i-lena-1]);
                bool okr=(sza>=szb);
                if(okl&&okr){
                    suf[t][i]=(suf[t+1][i]+1)*inv;
                }else if(okl){
                    suf[t][i]=suf[t+1][i];
                }else if(okr){
                    suf[t][i]=1;
                }else{
                    suf[t][i]=0;
                }
            }else{
                bool okl=(szb>=sza);
                bool okr=(i+lenb+2<n&&szb>=a[i+lenb+2]);
                if(okl&&okr){
                    suf[t][i]=suf[t+1][i]*inv;
                }else if(okl){
                    suf[t][i]=0;
                }else if(okr){
                    suf[t][i]=suf[t+1][i];
                }else{
                    suf[t][i]=1;
                }
            }
        }
    }
    if(sb-sa==1){
        cout << suf[1][sa] << "\n";
        return;
    }
    mint ans=0;
    vector<mint> dpa(n),dpb(n);
    dpa[sa]=1,dpb[sb]=1;
    int lena=0,lenb=0;
    auto upd_ans=[&](int t,int i,mint p){
        ans+=suf[t+1][i]*p;
    };
    for(int t=1;t<n;t++){
        vector<mint> ndp(n);
        if(t&1){
            for(int l=0,r=lena;r<sb;l++,r++){
                ll sz=get_sz(l,r);
                bool okl=(l>0&&sz>=a[l-1]);
                bool okr=(r+1<n&&sz>=a[r+1]);
                if(okl&&okr){
                    ndp[r]+=dpa[r]*inv;
                    ndp[r+1]+=dpa[r]*inv;
                    if(r+1<sb)upd_ans(t,r+1,dpa[r]*dpb[r+2]*inv);
                }else if(okl){
                    ndp[r]+=dpa[r];
                }else if(okr){
                    ndp[r+1]+=dpa[r];
                    if(r+1<sb)upd_ans(t,r+1,dpa[r]*dpb[r+2]);
                }
            }
            dpa=move(ndp);
            lena++;
        }else{
            auto aux=dpa;
            for(int i=1;i<n;i++)aux[i]+=aux[i-1];
            for(int l=sa+1,r=sa+lenb+1;r<n;l++,r++){
                ll sz=get_sz(l,r);
                bool okl=(l>0&&sz>=a[l-1]);
                bool okr=(r+1<n&&sz>=a[r+1]);
                if(okl&&okr){
                    ndp[l-1]+=dpb[l]*inv;
                    ndp[l]+=dpb[l]*inv;
                    if(l-1>sa)upd_ans(t,l-2,dpa[l-2]*dpb[l]*inv);
                }else if(okl){
                    ndp[l-1]+=dpb[l];
                    if(l-1>sa)upd_ans(t,l-2,dpa[l-2]*dpb[l]);
                }else if(okr){
                    ndp[l]+=dpb[l];
                }else{
                    if(l-1>sa)ans+=dpb[l]*aux[l-2];
                }
            }
            dpb=move(ndp);
            lenb++;
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