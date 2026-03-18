#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    int h=k/2;
    mint ans=0;
    // int cnt=0;
    // for(int mask=0;mask<(1<<n);mask++){
    //     int c[2]={};
    //     bool ok=true;
    //     for(int i=0;i<n;i++){
    //         c[mask>>i&1]++;
    //         if(i>=k)c[mask>>(i-k)&1]--;
    //         int v=mask>>(i-k+1)&1;
    //         if(i>=k-1&&c[v]<c[v^1]){
    //             ok=false;
    //             break;
    //         }
    //     }
    //     if(ok){
    //         cerr << bitset<9>(mask) << "\n";
    //         cnt++;
    //     }
    // }
    // cerr << cnt << "\n";
    // cerr << "\n";
    {
        int mask=0;
        for(int i=0;i+k-1<n;i++){
            if(s[i]=='0'){
                mask|=1;
            }else if(s[i]=='1'){
                mask|=2;
            }
        }
        int p=max(n-k+1,k);
        vector<mint> l0(k+1),l1(k+1),r0(k+1),r1(k+1);
        {
            int c0=0,c1=0,f=0;
            for(int i=n-k+1;i<p;i++){
                if(s[i]=='0'){
                    c0++;
                }else if(s[i]=='1'){
                    c1++;
                }else{
                    f++;
                }
            }
            for(int i=0;i<=f;i++){
                l0[c0+i]=comb.C(f,i);
            }
            for(int i=0;i<=f;i++){
                l1[c1+i]=comb.C(f,i);
            }
        }
        {
            int c0=0,c1=0,f=0;
            for(int i=p;i<n;i++){
                if(s[i]=='0'){
                    c0++;
                }else if(s[i]=='1'){
                    c1++;
                }else{
                    f++;
                }
            }
            for(int i=0;i<=f;i++){
                r0[c0+i]=comb.C(f,i);
            }
            for(int i=0;i<=f;i++){
                r1[c1+i]=comb.C(f,i);
            }
            for(int i=k-1;i>=0;i--){
                r0[i]+=r0[i+1];
                r1[i]+=r1[i+1];
            }
        }
        if(mask==0||mask==1){
            for(int i=max(0,h+2-(n-k+1));i<=k;i++){
                ans+=l0[i]*r0[max(0,h-i+1)];
            }
        }
        if(mask==0||mask==2){
            for(int i=max(0,h+2-(n-k+1));i<=k;i++){
                ans+=l1[i]*r1[max(0,h-i+1)];
            }
        }
    }
    vector<int> pre(n),mask(k-1);
    bool ok=true;
    int c0=0,c1=0,f=k-1;
    auto upd=[&](int i){
        if(mask[i%(k-1)]==0){
            f--;
        }else if(mask[i%(k-1)]==1){
            c0--;
        }else if(mask[i%(k-1)]==2){
            c1--;
        }
        if(s[i]=='0'){
            mask[i%(k-1)]|=1;
        }else if(s[i]=='1'){
            mask[i%(k-1)]|=2;
        }
        if(mask[i%(k-1)]==0){
            f++;
        }else if(mask[i%(k-1)]==1){
            c0++;
        }else if(mask[i%(k-1)]==2){
            c1++;
        }else{
            ok=false;
        }
    };
    int cur=0;
    for(int i=0;i<n;i++){
        if(s[i]=='0'){
            cur|=1;
        }else if(s[i]=='1'){
            cur|=2;
        }
        pre[i]=cur;
    }
    for(int i=n-k+1;i<n;i++){
        upd(i);
    }
    for(int i=n-k;i>=0;i--){
        if(pre[i]==0||pre[i]==1){
            if(mask[i%(k-1)]==0){
                f--;
                ans+=comb.C(f,h-c0);
                f++;
            }else if(mask[i%(k-1)]==2){
                ans+=comb.C(f,h-c0);
            }
        }
        if(pre[i]==0||pre[i]==2){
            if(mask[i%(k-1)]==0){
                f--;
                ans+=comb.C(f,h-c1);
                f++;
            }else if(mask[i%(k-1)]==1){
                ans+=comb.C(f,h-c1);
            }
        }
        upd(i);
        if(!ok)break;
    }
    if(ok){
        ans+=comb.C(f,h-c0);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}