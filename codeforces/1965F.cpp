#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
vector<pair<int,int>> a;
int add[N],ans[N];

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for(auto &[l,r]:a){
        cin >> l >> r;
    }
    for(int t=0;t<2;t++){
        sort(a.rbegin(),a.rend());
        priority_queue<int,vector<int>,greater<int>> pq;
        vector<pair<int,int>> b;
        for(int l=0;l<N;l++){
            while(!a.empty()&&a.back().first<=l){
                pq.emplace(a.back().second);
                a.pop_back();
            }
            while(!pq.empty()&&pq.top()<l){
                pq.pop();
            }
            if(!pq.empty()){
                b.emplace_back(N-pq.top(),N-l);
                pq.pop();
            }
        }
        a=move(b);
    }
    for(auto [l,r]:a){
        add[r]=l;
    }
    for(int l=N-1,r=N-1;l>=1;l--){
        if(add[l]){
            f.update(add[l],1);
        }
        while(l<=r&&f.query(r)<r-l+1){
            r--;
        }
        ans[r-l+1]++;
    }
    for(int i=n;i>=1;i--){
        ans[i-1]+=ans[i];
    }
    for(int i=1;i<=n;i++){
        cout << ans[i] << "\n";
    }
}