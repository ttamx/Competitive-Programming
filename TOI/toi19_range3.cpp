#include<bits/stdc++.h>

using namespace std;

struct Range{
    int l,r,i;
    Range(int _l,int _r,int _i){
        l=_l,r=_r,i=_i;
    }
    bool operator<(const Range &o)const{
        return r<o.r||(r==o.r&&l>o.l);
    }
};

struct SuffixMax{
    map<int,int> a;
    int query(int i){
        auto it=a.lower_bound(i);
        return it==a.end()?0:it->second;
    }
    void update(int i,int v){
        auto it=a.lower_bound(i);
        if(it!=a.end()&&it->second>=v)return;
        it=a.insert(it,make_pair(i,v));
        cerr << i << " : ";
        cerr << v << " -> " << it->second << "\n";
        it->second=v;
        while(it!=a.begin()&&(--it)->second<=v){
            it=a.erase(it);
        }
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<Range> a;
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        a.push_back(Range(l,r,i));
    }
    sort(a.begin(),a.end());
    SuffixMax ds;
    vector<int> dp(n);
    for(auto x:a){
        dp[x.i]=ds.query(x.l)+1;
        ds.update(x.l,dp[x.i]);
    }
    cout << *max_element(dp.begin(),dp.end()) << "\n";
    for(auto x:dp){
        cout << x << " ";
    }
}