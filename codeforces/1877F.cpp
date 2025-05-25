#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/dsu.hpp"

using mint = mint998;

const int N=2e5+5;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> s(N),cnt(N);
    for(auto &x:a){
        cin >> x;
        cnt[x]++;
    }
    mint base=1;
    for(int i=0;i<N;i++){
        if(cnt[i]>0){
            base*=2;
        }
    }
    DSU dsu(N);
    deque<int> dq;
    mint ans=1;
    for(auto x:a){
        if(s[x]==-1){
            s[x]=0;
        }
        if(s[x]==0){
            if(!dq.empty()){
                dsu.merge(x,dq.back());
            }
            dq.emplace_back(x);
        }else{
            if(dq.empty()||dq.front()!=x){
                cout << base/2 << "\n";
                return;
            }
            dq.pop_front();
        }
        s[x]^=1;
    }
    if(!dq.empty()){
        cout << base/2 << "\n";
        return;
    }
    for(int i=0;i<N;i++){
        if(cnt[i]>0&&dsu.find(i)==i){
            ans*=2;
        }
    }
    cout << (base-ans)/2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}
