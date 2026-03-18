#include "template.hpp"
#include "data-structure/dsu.hpp"

int mp[300];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    int q;
    cin >> q;
    vector<int> t(n);
    vector<pair<int,int>> qr(q);
    mp['C']=1,mp['O']=2,mp['W']=3;
    for(auto &[i,c]:qr){
        char ch;
        cin >> i >> ch;
        i--;
        c=t[i];
        t[i]=mp[ch];
    }
    reverse(qr.begin(),qr.end());
    DSU dsu(n);
    array<int,4> cnt{};
    for(int i=0;i<n;i++){
        if(!t[i]){
            dsu.merge(a[i],i);
        }
    }
    for(int i=0;i<n;i++){
        if(dsu.find(i)==i){
            cnt[t[i]]+=dsu.size(i);
        }
    }
    vector<array<int,4>> ans;
    for(auto [i,c]:qr){
        ans.emplace_back(cnt);
        cnt[t[i]]-=dsu.size(i);
        t[i]=c;
        if(!t[i]){
            int p=dsu.find(a[i]);
            cnt[t[p]]-=dsu.size(p);
            dsu.merge(p,i);
            cnt[t[p]]+=dsu.size(i);
        }else{
            cnt[t[i]]+=dsu.size(i);
        }
    }
    reverse(ans.begin(),ans.end());
    for(auto [_,x,y,z]:ans){
        cout << x << " " << y << " " << z << "\n";
    }
}