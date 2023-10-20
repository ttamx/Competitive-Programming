#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

int n,s,ans;
multiset<p2> ms;
vector<p2> vec;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    for(int i=1;i<=n;i++){
        int x,t;
        cin >> x >> t;
        if(x-t>s||x+t<s)continue;
        vec.emplace_back(x-t,x+t);
    }
    sort(vec.begin(),vec.end(),[&](p2 x,p2 y){
        if(x.second==y.second)return x.first>y.first;
        return x.second<y.second;
    });
    ms.emplace(s,0);
    for(auto [l,r]:vec){
        auto it=ms.lower_bound(make_pair(l,0));
        int val=it->second+1;
        ans=max(ans,val);
        it=ms.emplace(make_pair(l,val));
        while(it!=ms.begin()&&(--it)->second<=val)it=ms.erase(it);
    }
    cout << ans;
}