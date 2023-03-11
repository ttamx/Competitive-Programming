#include<bits/stdc++.h>

using namespace std;

const int N=25e5;

typedef long long ll;

ll n,m,l,u,ans;
ll p[N],v[N],qs[N],rs[N];
deque<int> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> l >> u;
    for(int i=1;i<=m;++i){
        cin >> p[i] >> v[i];
        p[i]/=2;
        qs[i]=qs[i-1]+v[i];
    }
    p[m+1]=n/2;
    dq.emplace_back(0);
    for(int i=1;i<=m;++i){
        while(!dq.empty()&&p[dq.front()+1]+u<p[i])dq.pop_front();
        if(!dq.empty()&&p[dq.front()]+l<p[i+1])ans=max(ans,qs[i]-qs[dq.front()]);
        while(!dq.empty()&&qs[dq.back()]>=qs[i])dq.pop_back();
        dq.emplace_back(i);
    }
    for(int i=m;i>=0;--i){
        rs[i]=rs[i+1]+v[i];
    }
    while(!dq.empty())dq.pop_back();
    dq.emplace_back(m+1);
    for(int i=m;i>0;--i){
        while(!dq.empty()&&p[dq.back()-1]-u>p[i])dq.pop_back();
        if(!dq.empty()&&p[dq.back()]-l>p[i-1])ans=max(ans,rs[i]-rs[dq.back()]);
        while(!dq.empty()&&rs[dq.front()]>=rs[i])dq.pop_front();
        dq.emplace_front(i);
    }
    cout << ans;
}
/*
12 6 0 1
2 -1
4 3
6 -2
8 5
10 3
12 2

18 5 2 4
2 1
8 2
14 -2
16 -1
18 6
*/
