#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    auto b=a;
    for(int i=1;i<=n;i++){
        b[i]^=b[i-1];
    }
    vector<int> l(n+1),r(n+1);
    int root=0;
    stack<int> s;
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.top()]<a[i]){
            l[i]=s.top();
            s.pop();
        }
        (s.empty()?root:r[s.top()])=i;
        s.emplace(i);
    }
    vector<BinaryTrie<30>> dp(n+1);
    uint32_t ans=0;
    auto rec=[&](auto &&self,int st,int ed,int i){
        if(!i)return;
        self(self,st,i-1,l[i]);
        self(self,i+1,ed,r[i]);
        if(st==ed){
            dp[i].insert(b[i-1]);
            dp[i].insert(b[i]);
            return;
        }
        if(st==i){
            swap(dp[i],dp[r[i]]);
            ans=max(ans,dp[i].max(a[i]^b[i-1]));
            dp[i].insert(b[i-1]);
            return;
        }
        if(ed==i){
            swap(dp[i],dp[l[i]]);
            ans=max(ans,dp[i].max(a[i]^b[i]));
            dp[i].insert(b[i]);
            return;
        }
        if(dp[l[i]].size()<dp[r[i]].size()){
            swap(dp[i],dp[r[i]]);
            for(int j=st-1;j<i;j++){
                ans=max(ans,dp[i].max(a[i]^b[j]));
            }
            for(int j=st-1;j<i;j++){
                dp[i].insert(b[j]);
            }
        }else{
            swap(dp[i],dp[l[i]]);
            for(int j=i;j<=ed;j++){
                ans=max(ans,dp[i].max(a[i]^b[j]));
            }
            for(int j=i;j<=ed;j++){
                dp[i].insert(b[j]);
            }
        }
    };
    rec(rec,1,n,root);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}