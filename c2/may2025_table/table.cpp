#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include "table.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<ll,int,int,int>;

const int N=405;
const int M=N*N*4;
const ll INF=1e18;

int n,m;
ll a[N][N];
int t[N][N][4];
ll dp[N][N][2];
T heap[M];
int heap_sz;

inline void heap_push(const T &v){
    int p,q;
    for(heap[p=++heap_sz]=v;(q=p>>1)&&v<heap[q];p=q)swap(heap[p],heap[q]);
}

inline int get_ch(int i){
    return (i<<=1)>heap_sz?0:(i<heap_sz&&heap[i|1]<heap[i]?i|1:i);
}

inline T heap_pop(){
    T res=heap[1];
    swap(heap[1],heap[heap_sz--]);
    for(int i=1,j;(j=get_ch(i))&&heap[i]>heap[j];i=j)swap(heap[i],heap[j]);
    return res;
}

inline ll dijkstra(int si,int sj){
    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=m+1;j++){
            dp[i][j][0]=dp[i][j][1]=INF;
        }
    }
    heap_sz=0;
    heap_push({dp[si][sj][0]=0,si,sj,0});
    auto push=[&](int i,int j,int c,ll d){
        if(i<0||i>n+1||j<0||j>m+1)return;
        d+=a[i][j];
        if(d<dp[i][j][c])heap_push({dp[i][j][c]=d,i,j,c});
    };
    while(heap_sz){
        auto [d,i,j,c]=heap_pop();
        if(d>dp[i][j][c])continue;
        if(i==si&&j==sj&&c)return d;
        push(i-1,j,c^t[i][j][0],d);
        push(i,j-1,c^t[i][j][1],d);
        push(i,j+1,c^t[i][j][2],d);
        push(i+1,j,c^t[i][j][3],d);
    }
    return INF;
}

ll minimum_obstruction(int _n,int _m,vector<vector<int>> _a,int r1,int c1,int r2,int c2){
    n=_n,m=_m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if((i==r1&&j==c1)||(i==r2&&j==c2)){
                a[i+1][j+1]=INF;
            }else{
                a[i+1][j+1]=_a[i][j];
            }
        }
    }
    vector<pair<int,int>> st;
    r1++,c1++,r2++,c2++;
    for(int i=c1;i<c2;i++){
        t[r1][i][0]=1;
        t[r1-1][i][3]=1;
        st.emplace_back(r1,i);
    }
    for(int i=c1;i>c2;){
        i--;
        t[r1][i][0]=1;
        t[r1-1][i][3]=1;
        st.emplace_back(r1,i);
    }
    for(int i=r1;i<r2;i++){
        t[i][c2][1]=1;
        t[i][c2-1][2]=1;
        st.emplace_back(i,c2);
    }
    for(int i=r1;i>r2;){
        i--;
        t[i][c2][1]=1;
        t[i][c2-1][2]=1;
        st.emplace_back(i,c2);
    }
    ll ans=INF;
    for(auto [i,j]:st){
        ans=min(ans,dijkstra(i,j));
    }
    return ans;
}