#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/fenwick-tree.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    set<int> has;
    set<int> cands;
    for(int i=0;i<=2*n+5;i++){
        cands.emplace(i);
    }
    vector<mint> ans;
    Fenwick<int> fw(n+1);
    int last=-1;
    int cnt=n+1;
    for(int i=n-1;i>=0;i--){
        int v=a[i];
        if(v<last)return void(cout << "0\n");
        for(auto it=cands.begin();it!=cands.end()&&*it<v;it=cands.erase(it)){
            if(*it>n)return void(cout << "0\n");
            has.emplace(*it);
            fw.update(*it,+1);
        }
        if(v==last){
            auto it=has.upper_bound(v);
            if(it==has.begin())return void(cout << "0\n");
            it--;
            ans.back()=fw.query(v);
            fw.update(*it,-1);
            has.erase(it);
            cnt--;
        }else{
            assert(cands.count(v));
            cands.erase(v);
            if(v<=n)cnt--;
        }
        if(has.size()>i+1)return void(cout << "0\n");
        ans.emplace_back(cnt);
        last=v;
    }
    if(!has.empty())ans.pop_back();
    mint val=1;
    for(auto x:ans)val*=x;
    cout << val << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}