#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=2e5+5;

struct line{
    ll m,c;
    line():m(0),c(0){}
    line(ll c):m(0),c(c){}
    line(ll m,ll c):m(m),c(c){}
    db insect(line l){
        return 1.0*(l.c-c)/(m-l.m);
    }
    ll get(ll x){
        return m*x+c;
    }
};

int n;
ll c;
ll h[N];
deque<line> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> c;
    for(int i=1;i<=n;i++)cin >> h[i];
    // (h[i]-h[j])^2 = h[i]^2 - 2h[i]h[j] + h[j]^2
    dq.emplace_front(-2*h[1],h[1]*h[1]);
    for(int i=2;i<=n;i++){
        while(dq.size()>1&&dq[0].insect(dq[1])<h[i])dq.pop_front();
        ll dp=dq[0].get(h[i])+c+h[i]*h[i];
        line l(-2*h[i],dp+h[i]*h[i]);
        while(dq.size()>1&&dq[dq.size()-2].insect(dq.back())>dq[dq.size()-2].insect(l))dq.pop_back();
        dq.emplace_back(l);
        if(i==n)cout << dp;
    }
}