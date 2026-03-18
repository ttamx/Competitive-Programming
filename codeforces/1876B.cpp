#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i].first;
        a[i].second=i+1;
    }
    sort(a.rbegin(),a.rend());
    vector<mint> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2;
    vector<vector<int>> divisor(n+1);
    vector<bool> used(n+1);
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j+=i){
            divisor[j].emplace_back(i);
        }
    }
    int all=n;
    mint ans=0;
    for(auto [v,i]:a){
        int cnt=0;
        for(auto j:divisor[i]){
            if(!used[j]){
                cnt++;
            }
        }
        ans+=v*(pw[cnt]-1)*pw[all-cnt];
        for(auto j:divisor[i]){
            if(!used[j]){
                used[j]=true;
                all--;
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}