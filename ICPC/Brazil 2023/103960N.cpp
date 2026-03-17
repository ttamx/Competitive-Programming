#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    ll base=0,ans=0;
    int m,k;
    cin >> m >> k;
    ll sum=0;
    multiset<int> msl,msr;
    auto insert=[&](int x){
        sum+=x;
        msl.emplace(x);
        if(msl.size()>k){
            int v=*msl.begin();
            msl.erase(msl.begin());
            msr.emplace(v);
            sum-=v;
        }
    };
    auto erase=[&](int x){
        auto it=msl.find(x);
        if(it!=msl.end()){
            sum-=x;
            msl.erase(it);
            if(!msr.empty()){
                int v=*msr.rbegin();
                msr.erase(prev(msr.end()));
                msl.emplace(v);
                sum+=v;
            }
        }else{
            msr.erase(msr.find(x));
        }
    };
    for(int i=0;i<m;i++){
        base+=a[i];
        insert(b[i]);
    }
    ans=max(ans,base+sum);
    for(int i=0;i<m;i++){
        base-=a[m-i-1];
        base+=a[n-i-1];
        erase(b[m-i-1]);
        insert(b[n-i-1]);
        ans=max(ans,base+sum);
    }
    cout << ans << "\n";
}