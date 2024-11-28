#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int LG=17;

int n,k;
int l[N],r[N];
vector<int> ep;
set<int> st,ed;
vector<int> ans;

struct Doubling{
    int nxt[LG][N];
    void set(int u,int v){
        nxt[0][u]=v;
    }
    void build(){
        for(int i=1;i<LG;i++){
            for(int j=0;j<=n;j++){
                nxt[i][j]=nxt[i-1][nxt[i-1][j]];
            }
        }
    }
    template<class F>
    int query(int u,const F &f){
        if(!f(u))return 0;
        int res=0;
        for(int i=LG-1;i>=0;i--){
            int v=nxt[i][u];
            if(f(v)){
                u=v;
                res|=1<<i;
            }
        }
        return res+1;
    }
}pre;

int search(int x){
    int lo=0,hi=ep.size()-1;
    while(lo<hi){
        int m=(lo+hi+1)/2;
        if(x>=r[ep[m]])lo=m;
        else hi=m-1;
    }
    return ep[lo];
}

int query(int x){
    int cur=search(*st.lower_bound(x));
    int lb=*prev(ed.upper_bound(x));
    return pre.query(cur,[&](int u){return l[u]>=lb;});
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return r[i]<r[j]||(r[i]==r[j]&&l[i]>l[j]);
    });
    ep.emplace_back(0);
    int idx=0;
    for(auto i:ord){
        if(l[i]<=l[ep.back()]){
            continue;
        }
        while(idx+1<ep.size()&&r[ep[idx+1]]<=l[i]){
            idx++;
        }
        pre.set(i,ep[idx]);
        ep.emplace_back(i);
    }
    st.emplace(0);
    st.emplace(1e9);
    ed.emplace(1);
    ed.emplace(1e9+1);
    pre.build();
    int base=query(1);
    if(base<k){
        cout << -1;
        exit(0);
    }
    for(int i=1;i<=n;i++){
        int pos=*ed.upper_bound(l[i]);
        if(pos<=r[i]||pos<=*st.lower_bound(r[i])){
            continue;
        }
        int memo=base;
        base-=query(l[i])-1;
        st.emplace(l[i]);
        ed.emplace(r[i]);
        base+=query(l[i]);
        base+=query(r[i]);
        if(base<k){
            base=memo;
            st.erase(l[i]);
            ed.erase(r[i]);
        }else{
            ans.emplace_back(i);
            if(ans.size()==k){
                break;
            }
        }
    }
    assert(ans.size()==k);
    for(auto x:ans){
        cout << x << "\n";
    }
}