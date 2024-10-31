#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    string s,t;
    cin >> s >> t;
    ll ans=LINF;
    ll cur=0;
    Fenwick<int> f(vector<int>(n,1));
    vector<queue<int>> pos(26);
    for(int i=0;i<n;i++){
        pos[s[i]-'a'].emplace(i);
    }
    for(int i=0;i<n;i++){
        int c=t[i]-'a';
        int p=n;
        for(int j=0;j<c;j++){
            if(!pos[j].empty()){
                p=min(p,f.query(pos[j].front())-1);
            }
        }
        if(p<n){
            ans=min(ans,cur+p-i);
        }
        if(pos[c].empty()){
            break;
        }
        p=pos[c].front();
        pos[c].pop();
        cur+=f.query(p)-i-1;
        f.update(p,-1);
        f.update(0,+1);
    }
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}