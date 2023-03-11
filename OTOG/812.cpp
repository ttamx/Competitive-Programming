#include<bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")

using namespace std;

const int N=25;

int n;
long long a[N][N];
map<int,long long> pre,cur;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)cin >> a[i][j];
    pre[0]=0;
    for(int i=0;i<n;i++){
        cur.clear();
        for(int j=0;j<n;j++){
            for(auto [x,y]:pre){
                if(x&(1<<j))continue;
                auto it=cur.find(x|(1<<j));
                if(it==cur.end())cur[x|(1<<j)]=y+a[i][j];
                else it->second=min(it->second,y+a[i][j]);
            }
        }
        pre=cur;
    }
    cout << cur[(1<<n)-1];
}