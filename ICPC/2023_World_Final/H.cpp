#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<ll,ll>> a(n),ans;
    for(auto &[s,t]:a)cin >> s >> t;
    for(int l=n-1,r=n-1;;){
        ll s=a[l].first,t=a[r].second;
        ll x=s-(t-s+1)/2;
        if(x<0){
            cout << "impossible",exit(0);
        }
        if(l>0&&a[l-1].second>x){
            l--;
            continue;
        }
        if(l==0){
            ans.emplace_back(x,x+(t-s+1)/2);
            if(x>1){
                ans.emplace_back(0,x/2);  
            }
            break;
        }
        ll p=a[l-1].second;
        if(x>p+1){
            ans.emplace_back(p,(p+x)/2);
        }
        l=r=l-1;
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for(auto [s,t]:ans)cout << s << " " << t << "\n";
}