#include<bits/stdc++.h>

using namespace std;

using ll = long long;

using T = tuple<int,int,int>;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    ll suml=0,sumr=0;
    vector<int> ver(n);
    priority_queue<T,vector<T>,greater<T>> pql,pqr;
    int mid=(n+1)/2;
    for(int i=0;i<n;i++){
        if(i<mid){
            suml+=a[i];
            pql.emplace(a[i],i,++ver[i]);
        }else{
            sumr+=a[i];
            pqr.emplace(a[i],i,++ver[i]);
        }
    }
    auto answer=[&](){
        while(true){
            auto [_,i,v]=pql.top();
            if(v==ver[i])break;
            pql.pop();
        }
        while(true){
            auto [_,i,v]=pqr.top();
            if(v==ver[i])break;
            pqr.pop();
        }
        ll x=get<0>(pql.top());
        ll y=get<0>(pqr.top());
        ll ansl=suml-x;
        ll ansr=sumr-y;
        if(x<y)swap(x,y);
        if(n%2==1)swap(x,y);
        cout << ansl+x << " " << ansr+y << "\n";
    };
    answer();
    while(q--){
        int i,x;
        cin >> i >> x;
        i--;
        if(i<mid){
            suml-=a[i];
            a[i]=x;
            suml+=a[i];
            pql.emplace(a[i],i,++ver[i]);
        }else{
            sumr-=a[i];
            a[i]=x;
            sumr+=a[i];
            pqr.emplace(a[i],i,++ver[i]);
        }
        answer();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}