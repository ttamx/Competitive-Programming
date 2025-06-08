#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int K=1505;

using BS = bitset<K>;

struct Gauss{
    BS basis[K];
    BS mask[K];
    int id[K];
    pair<bool,BS> insert(BS x,int k){
        BS cur;
        for(int i=K-1;i>=0;i--){
            if(x[i]){
                if(basis[i][i]){
                    x^=basis[i];
                    cur^=mask[i];
                }else{
                    cur.set(i);
                    basis[i]=x;
                    mask[i]=cur;
                    id[i]=k;
                    return {true,cur};
                }
            }
        }
        return {false,cur};
    }
}ds;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<BS> a(n);
    for(auto &x:a){
        string s;
        cin >> s;
        s.push_back('1');
        x=BS(s);
    }
    for(int i=0;i<n;i++){
        auto [ok,mask]=ds.insert(a[i],i);
        if(!ok){
            string ans(n,'0');
            vector<int> cands{i};
            for(int i=0;i<K;i++){
                if(mask[i]){
                    cands.emplace_back(ds.id[i]);
                }
            }
            assert(cands.size()%2==0);
            for(int i=0;i<cands.size();i++){
                ans[cands[i]]=char('1'+i%2);
            }
            cout << ans << "\n";
            exit(0);
        }
    }
    cout << "*\n";
}