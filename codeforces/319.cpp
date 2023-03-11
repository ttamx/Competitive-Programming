#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

struct line{
    ll m,c;
    double cross(line l){
        return 1.0*(c-l.c)/(l.m-m);
    }
    ll calc(ll x){
        return m*x+c;
    }
};

int n;
ll a[N],b[N],dp[N];
deque<line> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++){
        while(dq.size()>=2 && dq.back().cross(dq[dq.size()-2])<a[i])dq.pop_back();
        if(dq.size())dp[i]=dq.back().calc(a[i]);
        while(dq.size()>=2 && dq[1].cross(dq[0])>dq[1].cross({b[i],dp[i]}))dq.pop_front();
        dq.push_front({b[i],dp[i]});
    }
    cout << dp[n];
}