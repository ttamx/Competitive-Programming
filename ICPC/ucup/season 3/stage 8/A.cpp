#include<bits/stdc++.h>

using namespace std;

using i128 = __int128_t;

const i128 INF = 1e35;

void runcase(){
    string s;
    int m;
    cin >> s >> m;
    string ss=to_string(m);
    int dig=ss.size();
    reverse(s.begin(),s.end());
    for(int i=0;i<25;i++){
        s.push_back('0');
    }
    reverse(s.begin(),s.end());
    int n=s.size();
    vector<i128> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=min(pw[i-1]*10,INF);
    }
    vector<i128> suf(n+1);
    for(int i=n-1;i>=max(n-23,0);i--){
        suf[i]=suf[i+1]+(s[i]-'0')*pw[n-i-1];
    }
    i128 rem=0;
    for(auto x:s){
        rem=(rem*10LL+(x-'0'))%m;
    }
    i128 add=m-rem;
    {
        int last=n-1;
        while(s[last]=='9')last--;
        for(int i=0;i+dig<=last;i++){
            if(s.substr(i,dig)==ss){
                int exp=n-1-last;
                if(exp<=20){
                    add=min(add,pw[exp]-suf[last+1]);
                }
                if(i+dig==last){
                    add=1;
                }
            }
        }
    }
    {
        for(int i=max(0,n-21);i+dig<=n;i++){
            if(s.substr(i,dig)==ss){
                continue;
            }
            i128 val=0;
            if(s.substr(i,dig)>ss){
                val+=pw[dig];
            }
            for(int j=0;j<dig;j++){
                val+=(ss[j]-s[i+j])*pw[dig-j-1];
            }
            val*=pw[n-i-dig];
            val-=suf[i+dig];
            add=min(add,val);
        }
    }
    vector<i128> dp(n+1);
    dp[n]=1;
    for(int i=n-1;i>=0;i--){
        dp[i]=min(dp[i+1]+('9'-s[i])*pw[n-i-1],INF);
    }
    if(m>1){
        ss=to_string(m-1);
        dig=ss.size();
        for(int i=0;i+dig<=n;i++){
            if(s.substr(i,dig)==ss){
                add=min(add,dp[dig]);
            }
        }
    }
    string t=s;
    for(int i=n-1;i>=0;i--){
        int val=t[i]-'0'+add;
        t[i]='0'+(val%10);
        add=val/10;
    }
    reverse(t.begin(),t.end());
    while(t.back()=='0'){
        t.pop_back();
    }
    reverse(t.begin(),t.end());
    cout << t << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}