#include<bits/stdc++.h>

using namespace std;

const int N=2005;
const int INF=1e9;

int n,m;
int a[N][N],lmx[N][N],rmx[N][N],lmn[N][N],rmn[N][N];
int mn=INF;

int bsearch(int i,int v){
    int l=1,r=m;
    while(l<r){
        int m=(l+r)/2;
        if(rmx[i][m]<=v)r=m;
        else l=m+1;
    }
    return l;
}

bool check1(int d){
    stack<pair<int,int>> s;
    for(int i=1;i<=n;i++){
        int p=upper_bound(lmx[i]+1,lmx[i]+m,mn+d)-lmx[i]-1;
        while(!s.empty()&&s.top().second>p)s.pop();
        s.emplace(i,p);
    }
    int lo=INF,hi=0,p;
    for(int i=n;i>=1;i--){
        if(!s.empty()&&s.top().first==i){
            p=s.top().second;
            s.pop();
        }
        lo=min(lo,rmn[i][p+1]);
        hi=max(hi,rmx[i][p+1]);
        if(hi-lo>d)return false;
    }
    return true;
}

bool check2(int d){
    stack<pair<int,int>> s;
    for(int i=1;i<=n;i++){
        int p=bsearch(i,mn+d);
        while(!s.empty()&&s.top().second<p)s.pop();
        s.emplace(i,p);
    }
    int lo=INF,hi=0,p;
    for(int i=n;i>=1;i--){
        if(!s.empty()&&s.top().first==i){
            p=s.top().second;
            s.pop();
        }
        lo=min(lo,lmn[i][p-1]);
        hi=max(hi,lmx[i][p-1]);
        if(hi-lo>d)return false;
    }
    return true;
}

bool check3(int d){
    stack<pair<int,int>> s;
    for(int i=n;i>=1;i--){
        int p=upper_bound(lmx[i]+1,lmx[i]+m,mn+d)-lmx[i]-1;
        while(!s.empty()&&s.top().second>p)s.pop();
        s.emplace(i,p);
    }
    int lo=INF,hi=0,p;
    for(int i=1;i<=n;i++){
        if(!s.empty()&&s.top().first==i){
            p=s.top().second;
            s.pop();
        }
        lo=min(lo,rmn[i][p+1]);
        hi=max(hi,rmx[i][p+1]);
        if(hi-lo>d)return false;
    }
    return true;
}

bool check4(int d){
    stack<pair<int,int>> s;
    for(int i=n;i>=1;i--){
        int p=bsearch(i,mn+d);
        while(!s.empty()&&s.top().second<p)s.pop();
        s.emplace(i,p);
    }
    int lo=INF,hi=0,p;
    for(int i=1;i<=n;i++){
        if(!s.empty()&&s.top().first==i){
            p=s.top().second;
            s.pop();
        }
        lo=min(lo,lmn[i][p-1]);
        hi=max(hi,lmx[i][p-1]);
        if(hi-lo>d)return false;
    }
    return true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> a[i][j],mn=min(mn,a[i][j]);
    for(int i=1;i<=n;i++){
        lmn[i][0]=rmn[i][m+1]=INF;
        for(int j=1;j<=m;j++){
            lmx[i][j]=max(a[i][j],lmx[i][j-1]);
            lmn[i][j]=min(a[i][j],lmn[i][j-1]);
        }
        for(int j=m;j>=1;j--){
            rmx[i][j]=max(a[i][j],rmx[i][j+1]);
            rmn[i][j]=min(a[i][j],rmn[i][j+1]);
        }
    }
    int l=0,r=INF;
    while(l<r){
        int m=(l+r)/2;
        if(check1(m)||check2(m)||check3(m)||check4(m))r=m;
        else l=m+1;
    }
    cout << l;
}