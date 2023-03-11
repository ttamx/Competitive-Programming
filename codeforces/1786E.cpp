#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    b=a;
    sort(b.begin(),b.end());
    int pre=0;
    long long res=0;
    multiset<pair<int,int>> ms;
    vector<long long> ans;
    for(auto &x:b){
        res+=x-min(x,pre+1);
        pre=x=min(x,pre+1);
        ms.insert({x,x});
    }
    ms.insert({0,0});
    for(int i=n-1;i>=0;i--){
        ans.push_back(res);
        auto it=prev(ms.lower_bound({a[i]+1,0}));
        auto [l,r]=*it;
        ms.erase(it);
        if(a[i]<r){
            ms.insert({a[i]+1,r});
            if(a[i]>l)ms.insert({l,a[i]-1});
        }else{
            res-=a[i]-r;
            if(l<r)ms.insert({l,r-1});
        }
        it=ms.lower_bound({a[i],0});
        while(it!=ms.end()&&prev(it)->second+1<it->first){
            int sz=it->second-it->first+1;
            auto [l,r]=*prev(it);
            res+=sz;
            r+=sz;
            ms.erase(prev(it));
            it=ms.erase(it);
            ms.insert({l,r});
        }
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}