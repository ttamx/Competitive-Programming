#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> h(n),l(n),r(n);
    for(auto &x:h)cin >> x;
    auto sol=[&](){
        vector<int> v;
        for(int i=0;i<n;i++){
            auto it=lower_bound(v.begin(),v.end(),h[i]);
            r[i]=it-v.begin();
            if(it==v.end())v.emplace_back(h[i]);
            else *it=h[i];
        }
    };
    sol();
    swap(l,r);
    reverse(h.begin(),h.end());
    sol();
    reverse(r.begin(),r.end());
    while(q--){
        int x;
        cin >> x;
        cout << min(l[x],r[x]) << '\n';
    }
}