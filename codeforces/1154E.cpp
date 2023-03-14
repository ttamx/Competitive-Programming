#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    multiset<pair<int,int>> ms;
    multiset<pair<int,int>,greater<pair<int,int>>> pq;
    for(int i=0;i<n;i++){
        cin >> a[i];
        ms.emplace(i,a[i]);
        pq.emplace(a[i],i);
    }
    string ans(n,'1');
    bool ok=true;
    while(!pq.empty()){
        ok^=true;
        auto [x,y]=*pq.begin();
        pq.erase(pq.begin());
        auto it=ms.find({y,x});
        for(int j=0;j<k;j++){
            if(it==ms.begin())break;
            auto [xx,yy]=*prev(it);
            ms.erase(prev(it));
            pq.erase(pq.find({yy,xx}));
            if(ok)ans[xx]='2';
        }
        for(int j=0;j<k;j++){
            if(next(it)==ms.end())break;
            auto [xx,yy]=*next(it);
            ms.erase(next(it));
            pq.erase(pq.find({yy,xx}));
            if(ok)ans[xx]='2';
        }
        ms.erase(it);
        if(ok)ans[y]='2';
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}