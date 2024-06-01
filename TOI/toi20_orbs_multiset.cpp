#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q,l,r;
    cin >> n >> q >> l >> r;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    int sz[3]={l,r-l,n-r};
    multiset<int> ms[3];
    int p=0;
    for(auto x:a){
        if(ms[p].size()==sz[p])p++;
        ms[p].emplace(x);
    }
    auto compress=[&](){
        for(int i=2;i>0;i--){
            while(ms[i].size()>sz[i]){
                ms[i-1].emplace(*ms[i].begin());
                ms[i].erase(ms[i].begin());
            }
        }
    };
    while(q--){
        auto itl=prev(ms[0].end());
        auto itr=prev(ms[1].end());
        int x=*itl,y=*itr;
        ms[0].erase(itl);
        ms[1].erase(itr);
        ms[2].emplace(y-x);
        ms[2].emplace((x+y)/2);
        compress();
    }
    for(int i=0;i<3;i++)for(auto x:ms[i])cout << x << " ";
}