#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<mint>> pre_ways(n,vector<mint>(n+1));
    vector<vector<mint>> pre_len(n,vector<mint>(n+1));
    {
        vector<mint> ways(n+1),len(n+1);
        ways[0]=1;
        for(int i=0;i<n;i++){
            if(s[i]=='('){
                for(int j=1;j<=n;j++){
                    pre_ways[i][j]=ways[j-1];
                    pre_len[i][j]=len[j-1]+ways[j-1];
                }
            }else{
                for(int j=0;j<n;j++){
                    pre_ways[i][j]=ways[j+1];
                    pre_len[i][j]=len[j+1]+ways[j+1];
                }
            }
            for(int j=0;j<=n;j++){
                ways[j]+=pre_ways[i][j];
                len[j]+=pre_len[i][j];
            }
        }
    }
    mint ans=0;
    vector<mint> ways(n+1),ways2(n+1),ways3(n+1);
    vector<mint> len(n+1),len2(n+1),len3(n+1);
    ways[0]=1;
    for(int i=n-1;i>=0;i--){
        if(s[i]==')'){
            for(int j=0;j<=n;j++){
                ans+=pre_len[i][j]*ways3[j];
                ans+=pre_ways[i][j]*len3[j];
                ans-=2*pre_ways[i][j]*ways3[j];
            }
            for(int j=n;j>=1;j--){
                ways[j]+=ways[j-1];
                len[j]+=len[j-1]+ways[j-1];
                ways2[j]+=ways2[j-1];
                len2[j]+=len2[j-1]+ways2[j-1];
            }
        }else{
            for(int j=0;j<n;j++){
                ways2[j]+=ways[j+1];
                len2[j]+=len[j+1]+ways[j+1];
                ways3[j]+=ways2[j+1];
                len3[j]+=len2[j+1]+ways2[j+1];
                ways3[j]+=ways3[j+1];
                len3[j]+=len3[j+1]+ways3[j+1];
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