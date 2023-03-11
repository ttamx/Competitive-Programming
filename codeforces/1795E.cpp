#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const bool DBG=false;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),l(n),r(n);
    for(auto &x:a)cin >> x;
    ll res=0;
    stack<pair<ll,ll>> st;
    for(int i=0;i<n;i++){
        ll x=a[i];
        while(!st.empty()&&x>0){
            auto [ll,rr]=st.top();
            if(rr+1<=x)break;
            st.pop();
            res-=(rr+ll)*(rr-ll+1)/2;
            x-=rr-ll+1;
        }
        if(x<=0){
            x=0;
            while(!st.empty()){
                auto [ll,rr]=st.top();
                st.pop();
                res-=(rr+ll)*(rr-ll+1)/2;
            }
        }
        st.emplace(x,a[i]);
        res+=(a[i]+x)*(a[i]-x+1)/2;
        l[i]=res-a[i];
    }
    res=0;
    while(!st.empty())st.pop();
    for(int i=n-1;i>=0;i--){
        ll x=a[i];
        while(!st.empty()&&x>0){
            auto [ll,rr]=st.top();
            if(rr+1<=x)break;
            st.pop();
            res-=(rr+ll)*(rr-ll+1)/2;
            x-=rr-ll+1;
        }
        if(x<=0){
            x=0;
            while(!st.empty()){
                auto [ll,rr]=st.top();
                st.pop();
                res-=(rr+ll)*(rr-ll+1)/2;
            }
        }
        st.emplace(x,a[i]);
        res+=(a[i]+x)*(a[i]-x+1)/2;
        r[i]=res-a[i];
    }
    if(DBG)for(int i=0;i<n;i++)cerr << "(" << l[i] << "," << r[i] << ") ";
    if(DBG)cerr << '\n';
    ll sum=0,ans=0;
    for(auto x:a)sum+=x;
    for(int i=0;i<n;i++)ans=max(ans,l[i]+r[i]);
    cout << sum-ans << '\n';
    if(DBG)cerr << "==================\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}