#pragma GCC optimize("O3,unroll-loops")
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,m;
    cin >> n >> m;
    int k=(n+1)*(m+1);
    mint ans=0;
    vector<mint> pw(k+1);
    pw[0]=1;
    for(int i=1;i<=k;i++){
        pw[i]=pw[i-1]*mint(4);
    }
    vector<array<mint,16>> dp(m,array<mint,16>{});
    for(int x=0;x<4;x++){
        for(int y=0;y<4;y++){
            for(int z=0;z<4;z++){
                int mask=1<<x;
                if(y==0)mask|=1;
                if(z==0)mask|=2;
                dp[0][mask]+=4;
            }
        }
    }
    for(int j=1;j<m;j++){
        for(int mask=0;mask<16;mask++){
            if(!(mask&1)||(mask&2))continue;
            int mask2=0;
            if(mask&4)mask2|=1;
            for(int x=0;x<4;x++){
                for(int y=0;y<4;y++){
                    int mask3=mask2|(1<<x);
                    if(y==0)mask3|=2;
                    dp[j][mask3]+=dp[j-1][mask];
                }
            }
        }
    }
    for(int j=0;j<m;j++){
        for(int mask=0;mask<16;mask++){
            if((mask&3)==3){
                ans+=dp[j][mask]*pw[k-2*(j+2)];
            }
        }
    }
    for(int i=1;i<n;i++){
        vector<array<mint,16>> ndp(m,array<mint,16>{});
        for(int j=0;j<m;j++){
            for(int mask=0;mask<16;mask++){
                if(mask&1)continue;
                int mask2=0;
                if(mask&8)mask2|=2;
                for(int x=0;x<4;x++){
                    for(int y=0;y<4;y++){
                        int mask3=mask2|(1<<x);
                        if(y==0)mask3|=1;
                        ndp[j][mask3]+=dp[j][mask]*pw[j];
                    }
                }
            }
            if(j>0)for(int mask=0;mask<16;mask++){
                if(!(mask&1)||(mask&2))continue;
                int mask2=0;
                if(mask&4)mask2|=1;
                for(int x=0;x<4;x++){
                    for(int y=0;y<4;y++){
                        int mask3=mask2|(1<<x);
                        if(y==0)mask3|=2;
                        ndp[j][mask3]+=ndp[j-1][mask]*pw[i];
                    }
                }
            }

        }
        dp=move(ndp);
        for(int j=0;j<m;j++){
            for(int mask=0;mask<16;mask++){
                if((mask&3)==3){
                    ans+=dp[j][mask]*pw[k-(i+2)*(j+2)];
                }
            }
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