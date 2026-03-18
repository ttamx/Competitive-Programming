#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n),l(k+1,n),r(k+1,-1);
    for(auto &x:a)cin >> x;
    for(int i=0;i<n;i++)if(a[i]){
        l[a[i]]=min(l[a[i]],i);
        r[a[i]]=max(r[a[i]],i);
    }
    vector<int> ans;
    auto check=[&](int mid){
        vector<int> vals;
        vector<vector<pair<int,int>>> event(n);
        for(int i=1;i<=k;i++){
            if(l[i]>r[i])vals.emplace_back(i);
            else{
                if(r[i]-l[i]>mid)return false;
                event[max(0,r[i]-mid)].emplace_back(l[i],i);
            }
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        int last=-1,val=-1;
        ans=a;
        for(int i=0;i<n;i++){
            for(auto [x,v]:event[i])pq.emplace(x,v);
            if(!a[i]){
                if(i>last){
                    if(!pq.empty()){
                        val=pq.top().second;
                        pq.pop();
                    }else{
                        if(vals.empty())return false;
                        val=vals.back();
                        vals.pop_back();
                    }
                    last=i+mid;
                }
                ans[i]=val;
            }
            while(!pq.empty()&&pq.top().first==i){
                last=i+mid;
                val=pq.top().second;
                pq.pop();
            }
        }
        return true;
    };
    int lo=0,hi=n;
    while(lo<hi){
        int mid=(lo+hi)/2;
        if(check(mid))hi=mid;
        else lo=mid+1;
    }
    check(lo);
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}