#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int p;
    cin >> p;
    vector<int> f;
    for(int i=1;i<p;i++){
        if((p-1)%i==0){
            f.emplace_back(i);
        }
    }
    function<int(int,int)> modpow=[&](int a,int b){
        int res=1;
        while(b>0){
            if(b&1)res=1LL*res*a%p;
            a=1LL*a*a%p;
            b>>=1;
        }
        return res;
    };
    vector<int> cnt(p),val(p);
    for(int i=1;i<p;i++){
        for(auto x:f){
            if(modpow(i,x)==1){
                cnt[x]++;
                val[x]=i;
                break;
            }
        }
    }
    vector<long long> ans(p);
    for(int i=1;i<p;i++){
        if(!cnt[i])continue;
        int cur=1;
        for(int j=0;j<i;j++){
            ans[cur]+=1LL*cnt[i]*(p-1)/i;
            cur=1LL*cur*val[i]%p;
        }
    }
    for(int i=1;i<p;i++){
        cout << ans[i] << " ";
    }
}