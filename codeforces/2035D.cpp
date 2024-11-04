#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto calc=[&](ll x){
        int cnt=0;
        while(x%2==0){
            cnt++;
            x/=2;
        }
        return make_pair(x,cnt);
    };
    pair<ll,int> ans(0,0);
    vector<mint> pw(n*30+1);
    pw[0]=1;
    for(int i=1;i<=n*30;i++){
        pw[i]=pw[i-1]*2;
    }
    mint sum=0;
    stack<pair<ll,int>> s;
    for(auto x:a){
        auto [v,c]=calc(x);
        sum+=v;
        pair<ll,int> cur(v,c);
        while(!s.empty()){
            auto ans=s.top();
            int cnt=ans.second+cur.second;
            int dif=cnt-ans.second;
            if(dif>0){
                if(dif>=30||(v<<dif)>ans.first){
                    sum-=mint(ans.first)*(pw[ans.second]-1);
                    cur={v,cnt};
                    s.pop();
                }else{
                    break;
                }
            }else{
                dif=-dif;
                if(dif<30&&v>(ans.first<<dif)){
                    sum-=mint(ans.first)*(pw[ans.second]-1);
                    cur={v,cnt};
                    s.pop();
                }else{
                    break;
                }
            }
        }
        s.emplace(cur);
        sum+=mint(cur.first)*(pw[cur.second]-1);
        cout << sum << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}