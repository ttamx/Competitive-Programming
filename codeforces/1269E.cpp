#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick{
    int n;
    vector<int> t;
    void init(int _n){
        n=_n;
        t.assign(n+1,0);
    }
    void update(int i,int v){
        for(i++;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(i++;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        b[--a[i]]=i;
    }
    priority_queue<int> pql;
    priority_queue<int,vector<int>,greater<int>> pqr;
    ll opt=0;
    auto insert=[&](int x){
        if(!pql.empty()&&x<pql.top()){
            pql.emplace(x);
            pql.emplace(x);
            opt+=pql.top()-x;
            pqr.emplace(pql.top());
            pql.pop();
        }else if(!pqr.empty()&&x>pqr.top()){
            pqr.emplace(x);
            pqr.emplace(x);
            opt+=x-pqr.top();
            pql.emplace(pqr.top());
            pqr.pop();
        }else{
            pql.emplace(x);
            pqr.emplace(x);
        }
    };
    ll inv=0,sub=0;
    vector<ll> ans(n);
    f.init(n);
    for(int i=0;i<n;i++){
        sub+=(i+1)/2;
        inv+=i-f.query(b[i]);
        f.update(b[i],+1);
        insert(b[i]);
        ans[i]=inv+opt-sub;
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}