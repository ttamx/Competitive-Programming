#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using namespace std;

using mint = mint998;

using ll = long long;

vector<tuple<ll,ll,int>> input;
vector<mint> ans;
vector<thread> th;

void runcase(string l,string r,ll k,int testid){
    auto calc=[&](ll x){
        
    };
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    input.resize(t);
    ans.resize(t);
    for(int i=0;i<t;i++){
        string l,r;
        ll k;
        cin >> l >> r >> k;
        if(l.size()>k)l=string(k,'9');
        if(r.size()>k)r=string(k,'9');
        th.emplace_back(thread(runcase,l,r,k,i));
    }
    for(auto &e:th){
        e.join();
    }
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": " << ans[i-1] << "\n";
    }
}