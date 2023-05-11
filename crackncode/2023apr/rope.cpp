#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;

int n,p;
ll x;
int y,z;
int a[N],b[N];
ll qs[N];
int cnt[N];
ll ans;
int idx=1;
deque<pair<int,int>> mxdq,mndq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    cin >> x >> y >> z;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)cin >> b[i];
    for(int i=1;i<=n;i++){
        qs[i]=qs[i-1]+a[i];
        cnt[b[i]]++;
        while(!mxdq.empty()&&mxdq.back().first<a[i])mxdq.pop_back();
        while(!mndq.empty()&&mndq.back().first>a[i])mndq.pop_back();
        mxdq.emplace_back(a[i],i);
        mndq.emplace_back(a[i],i);
        if(y!=-1){
            while(mxdq.front().first-mndq.front().first>y){
                cnt[b[idx]]--;
                idx++;
                while(mxdq.front().second<idx)mxdq.pop_front();
                while(mndq.front().second<idx)mndq.pop_front();
            }
        }
        if(z!=-1){
            while(cnt[b[i]]>z){
                cnt[b[idx]]--;
                idx++;
            }
        }
        while(qs[i]-qs[idx-1]>x){
            cnt[b[idx]]--;
            idx++;
        }
        while(mxdq.front().second<idx)mxdq.pop_front();
        while(mndq.front().second<idx)mndq.pop_front();
        ans+=i-idx+1;
    }
    cout << ans;
}