#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    DSU dsu(n);
    vector<int> s;
    auto dp=a;
    for(int i=0;i<n;i++){
        if(s.empty()||a[i]>=a[s.back()]){
            s.emplace_back(i);
        }else{
            int t=s.back();
            while(!s.empty()&&a[s.back()]>a[i]){
                dp[i]=max(dp[i],dp[dsu.find(s.back())]);
                dsu.merge(i,s.back());
                s.pop_back();
            }
            s.emplace_back(t);
        }
    }
    for(int i=0;i<n;i++){
        cout << dp[dsu.find(i)] << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}