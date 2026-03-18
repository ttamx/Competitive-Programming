#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int m,d;
    cin >> m >> d;
    auto calc=[&](string s){
        vector<array<array<mint,2>,2>> dp(m,array<array<mint,2>,2>{});
        for(int i=0;i<s.size();i++){
            int v=s[i]-'0';
            vector<array<array<mint,2>,2>> ndp(m,array<array<mint,2>,2>{});
            for(int j=0;j<m;j++){
                for(int dd=0;dd<10;dd++){
                    for(int b=0;b<2;b++){
                        for(int f=0;f<2;f++){
                            if(!((d==dd)^b))continue;
                            if(!f&&dd>v)continue;
                            ndp[(j*10+dd)%m][b^1][f|(dd<v)]+=dp[j][b][f];
                        }
                    }
                }
            }
            if(i==0&&v!=d){
                ndp[v%m][0][0]++;
            }
            for(int j=1;j<(i>0?10:v);j++){
                if(j!=d){
                    ndp[j%m][0][1]++;
                }
            }
            dp=move(ndp);
        }
        return dp[0][0][1]+dp[0][1][1];
    };
    string a,b;
    cin >> a >> b;
    reverse(b.begin(),b.end());
    int c=1;
    for(auto &x:b){
        x+=c;
        if(x>'9'){
            x-=10;
            c=1;
        }else{
            c=0;
            break;
        }
    }
    if(c)b.push_back('1');
    reverse(b.begin(),b.end());
    cout << calc(b)-calc(a) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}