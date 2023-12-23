#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=305;
const int inf=1e9;

int n,k;
int a[N],qs[N];
p2 dp[N][2];

struct convexhulltrick{
    struct line{
        int m,c,cnt;
        line(int m,int c,int cnt):m(m),c(c),cnt(cnt){}
        int get(int x){
            return m*x+c;
        }
    };
    deque<line> dq;
    bool bad(line l1,line l2,line l3){
        return (l2.c-l1.c)*(l1.m-l3.m)>=(l3.c-l1.c)*(l1.m-l2.m);
    }
    void clear(){
        dq.clear();
    }
    void insert(int m,int c,int cnt){
        line l(m,c,cnt);
        while(dq.size()>1&&bad(dq.end()[-2],dq.back(),l))dq.pop_back();
        dq.emplace_back(l);
    }
    p2 get(int x){
        if(dq.empty())return p2(inf,0);
        while(dq.size()>1&&dq[0].get(x)>dq[1].get(x))dq.pop_front();
        return p2(dq[0].get(x),dq[0].cnt);
    }
}cht[0];

p2 calc(int lambda){
    cht[0].clear();
    cht[1].clear();
    cht[0].insert(0,0,0);
    for(int i=1;i<=n;i++){
        dp[i][0]=cht[0].get(a[i]);
        dp[i][0].first+=i*a[i]-qs[i]+lambda;
        dp[i][0].second++;
        dp[i][1]=cht[1].get(i);
        dp[i][1].first+=qs[i];
        dp[i][1]=min(dp[i][1],dp[i][0]);
        cht[0].insert(-i,dp[i][1].first+qs[i],dp[i][1].second);
        cht[1].insert(-a[i],dp[i][0].first-qs[i]+i*a[i],dp[i][0].second);
    }
    return dp[n][1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    int l=0,r=3e6;
    while(l<r){
        int m=(l+r+1)/2;
        if(calc(m).second>=k)l=m;
        else r=m-1;
    }
    cout << calc(l).first-l*k;
}