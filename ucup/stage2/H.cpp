#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,d;
        cin >> n >> d;
        ll tot=0;
        vector<ll> a(n);
        for(auto &x:a){
            cin >> x;
            tot+=x;
        }
        int k=tot/n;
        auto check=[&](int mid){
            int g=mid*d;
            vector<vector<pair<int,int>>> events(n);
            for(int i=0;i<n;i++){
                if(a[i]>0){
                    events[max(0,i-g)].emplace_back(i+g,a[i]);
                }
            }
            queue<pair<int,int>> q;
            for(int i=0;i<n;i++){
                if(!q.empty()&&q.front().first<i){
                    return false;
                }
                for(auto [j,v]:events[i]){
                    q.emplace(j,v);
                }
                int cur=k;
                while(cur>0&&!q.empty()){
                    auto &[j,v]=q.front();
                    if(cur>=v){
                        cur-=v;
                        q.pop();
                    }else{
                        v-=cur;
                        cur=0;
                    }
                }
                if(cur>0){
                    return false;
                }
            }
            return true;
        };
        int l=0,r=n/d+1;
        while(l<r){
            int mid=(l+r)/2;
            if(check(mid))r=mid;
            else l=mid+1;
        }
        cout << l << "\n";
    }
}