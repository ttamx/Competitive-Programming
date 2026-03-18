#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "string/z-algorithm.hpp"

using mint = mint107;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    string s,t;
    cin >> s >> t;
    vector<mint> pw(n+1),ipw(n+1);
    mint inv2=mint(1)/mint(2);
    pw[0]=ipw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2;
        ipw[i]=ipw[i-1]*inv2;
    }
    vector<vector<mint>> f(26,vector<mint>(n+1));
    for(int c=0;c<26;c++){
        for(int i=0;i<n;i++){
            f[c][i+1]=f[c][i];
            if(t[i]=='a'+c){
                f[c][i+1]+=ipw[i+1];
            }
        }
    }
    while(q--){
        int k;
        string w;
        cin >> k >> w;
        int len=w.size();
        string ss=s;
        int cur=0;
        for(;ss.size()<len&&cur<k;cur++){
            ss+=t.substr(cur,1)+ss;
        }
        int m=ss.size();
        if(m<len){
            cout << "0\n";
            continue;
        }
        mint ans=0;
        {
            auto z=z_algorithm(w+ss);
            for(int i=0;i<m;i++){
                if(z[len+i]>=len){
                    ans+=ipw[cur];
                }
            }
        }
        vector<int> pre(m),suf(m);
        for(int tt=0;tt<2;tt++){
            auto z=z_algorithm(w+ss);
            for(int i=0;i<m;i++){
                if(min(z[len+i],len)>=m-i){
                    pre[i]=1;
                }
            }
            reverse(w.begin(),w.end());
            reverse(ss.begin(),ss.end());
            swap(pre,suf);
        }
        reverse(suf.begin(),suf.end());
        for(int i=0;i<len;i++){
            if(i>0&&!pre[m-i])continue;
            if(i<len-1&&!suf[len-i-2])continue;
            ans+=f[w[i]-'a'][k]-f[w[i]-'a'][cur];
        }
        cout << ans*pw[k] << "\n";
    }
}