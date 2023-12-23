#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;

typedef long long ll;
typedef pair<ll,int> p2;

int n,k;
ll a[N],qs[N];
ll dp[N];
int cnt[N];

ll cost(int l,int r){
    int m=(l+r)/2;
    return qs[r]-qs[m]-a[m]*(r-m)+a[m]*(m-l)-qs[m-1]+qs[l-1];
}

p2 calc(int i,int j){
    return p2(dp[i]+cost(i+1,j),cnt[i]+1);
}

p2 calc(ll lambda){
    struct range{
        int p,l,r;
        range(int p,int l,int r):p(p),l(l),r(r){}
    };
    deque<range> dq;
    dp[0]=cnt[0]=0;
    dq.emplace_back(0,1,n);
    for(int i=1;i<=n;i++){
        tie(dp[i],cnt[i])=calc(dq.front().p,i);
        dp[i]+=lambda;
        if(dq.front().r==i)dq.pop_front();
        else dq.front().l++;
        while(!dq.empty()&&calc(i,dq.back().l)<calc(dq.back().p,dq.back().l))dq.pop_back();
        if(dq.empty())dq.emplace_back(i,i+1,n);
        else{
            int l=dq.back().l,r=dq.back().r;
            while(l<r){
                int m=(l+r+1)/2;
                if(calc(dq.back().p,m)<=calc(i,m))l=m;
                else r=m-1;
            }
            dq.back().r=l;
            if(l<n)dq.emplace_back(i,l+1,n);
        }
    }
    return p2(dp[n],cnt[n]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    ll l=0,r=3e14;
    while(l<r){
        ll m=(l+r)/2;
        if(calc(m).second<=k)r=m;
        else l=m+1;
    }
    cout << calc(l).first-l*k;
}