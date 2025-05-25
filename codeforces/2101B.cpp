#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a[2];
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x--;
        a[i&1].emplace_back(x);
    }
    ll cnt=0;
    for(auto &v:a){
        Fenwick<ll> f(n);
        for(int i=v.size()-1;i>=0;i--){
            cnt+=f.query(v[i]);
            f.update(v[i],+1);
        }
        sort(v.begin(),v.end());
    }
    auto gen=[&](){
        vector<int> res(n);
        for(int i=0;i<n;i++){
            res[i]=a[i&1][i/2];
        }
        return res;
    };
    vector<int> ans;
    if(cnt%2==0){
        ans=gen();
    }else{
        swap(a[0].end()[-2],a[0].back());
        ans=gen();
        swap(a[0].end()[-2],a[0].back());
        swap(a[1].end()[-2],a[1].back());
        ans=min(ans,gen());
    }
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}