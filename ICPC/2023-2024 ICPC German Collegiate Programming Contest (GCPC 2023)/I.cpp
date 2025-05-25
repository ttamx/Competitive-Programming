#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    multiset<pair<int,int>> s;
    auto insert=[&](int x){
        int l=x,r=x;
        auto it=s.lower_bound(make_pair(x,x));
        if(it->first==x+1){
            r=it->second;
            it=s.erase(it);
        }
        if(it!=s.begin()&&(--it)->second==x-1){
            l=it->first;
            s.erase(it);
        }
        s.emplace(l,r);
    };
    for(auto x:a){
        insert(x);
    }
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        x--;
        int pos=a[x];
        auto it=s.lower_bound(make_pair(pos+1,0));
        assert(it!=s.begin());
        it--;
        auto [l,r]=*it;
        s.erase(it);
        if(l<pos){
            s.emplace(l,pos-1);
        }
        if(pos<r){
            s.emplace(pos+1,r);
        }
        a[x]=r+1;
        insert(a[x]);
        cout << a[x] << "\n";
    }
}