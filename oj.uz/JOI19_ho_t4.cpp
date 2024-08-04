#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n;
int cnt[N][2];
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<2*n;i++){
        int x,y;
        cin >> x >> y;
        if(x<1)ans+=1-x,x=1;
        if(x>n)ans+=x-n,x=n;
        if(y<1)ans+=1-y,y=1;
        if(y>2)ans+=y-2,y=2;
        cnt[x][y-1]++;
    }
    for(int i=1;i<=n;i++){
        cnt[i][0]+=cnt[i-1][0]-1;
        cnt[i][1]+=cnt[i-1][1]-1;
        while(cnt[i][0]<0&&cnt[i][1]>0)ans++,cnt[i][0]++,cnt[i][1]--;
        while(cnt[i][0]>0&&cnt[i][1]<0)ans++,cnt[i][0]--,cnt[i][1]++;
        ans+=abs(cnt[i][0])+abs(cnt[i][1]);
    }
    cout << ans;
}