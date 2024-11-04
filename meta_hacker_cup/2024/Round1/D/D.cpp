#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;
const int LIM=1e6+5;

void upd(int &x,ll v){
    x=min((ll)LIM,x+v);
}

void runcase(){
    string s;
    int k;
    cin >> s >> k;
    int n=s.size();
    string t=s;
    vector<int> dp(n);
    if(n>=2&&(s[n-2]=='?'&&s[n-1]=='?')){
        dp[n-2]=15;
        for(int i=n-3;i>=0;i--){
            if(s[i]=='?'){
                if(s[i+1]=='?'||s[i+1]<='6'){
                    dp[i]=min(dp[i+1]*2,LIM);
                }else{
                    dp[i]=dp[i+1];
                }
            }else{
                dp[i]=dp[i+1];
            }
        }
        for(int i=0;i<n-2;i++){
            if(s[i]=='?'){
                if(s[i+1]=='?'||s[i+1]<='6'){
                    if(k>dp[i+1]){
                        t[i]='1';
                        k-=dp[i+1];
                    }else{
                        t[i]='2';
                    }
                }else{
                    t[i]='1';
                }
            }
        }
        assert(k<=15);
        if(k<=6){
            t[n-2]='2';
            t[n-1]='6'-k+1;
        }else{
            k-=6;
            t[n-2]='1';
            t[n-1]='9'-k+1;
        }
    }else{
        dp[n-1]=1;
        if(s[n-1]=='?'){
            if(n>=2&&s[n-2]=='2'){
                dp[n-1]=6;
            }else{
                dp[n-1]=9;
            }
        }
        for(int i=n-2;i>=0;i--){
            if(s[i]=='?'){
                if(s[i+1]=='?'||s[i+1]<='6'){
                    dp[i]=min(dp[i+1]*2,LIM);
                }else{
                    dp[i]=dp[i+1];
                }
            }else{
                dp[i]=dp[i+1];
            }
        }
        for(int i=0;i<n;i++){
            if(i==n-1){
                if(s[i]=='?'){
                    if(n>=2&&s[n-2]=='2'){
                        assert(k<=6);
                        t[i]='6'-k+1;
                    }else{
                        assert(k<=9);
                        t[i]='9'-k+1;
                    }
                }
            }else if(s[i]=='?'){
                if(s[i+1]=='?'||s[i+1]<='6'){
                    if(k>dp[i+1]){
                        t[i]='1';
                        k-=dp[i+1];
                    }else{
                        t[i]='2';
                    }
                }else{
                    t[i]='1';
                }
            }
        }
    }
    vector<int> dp2(n+1);
    dp2[0]=1;
    for(int i=1;i<=n;i++){
        if(t[i-1]!='0'){
            dp2[i]=dp2[i-1];
        }
        if(i>=2&&(t[i-2]=='1'||(t[i-2]=='2'&&t[i-1]<='6'))){
            dp2[i]+=dp2[i-2];
            if(dp2[i]>MOD)dp2[i]-=MOD;
        }
    }
    cout << t << " " << dp2[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}