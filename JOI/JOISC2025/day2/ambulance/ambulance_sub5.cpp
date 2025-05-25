#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=165;
const int T=10005;

int n,l,t;
pair<int,int> a[N];
int dpl[T],dpr[T];
bool okl[N],okr[N];

void solve(){
    {
        okl[0]=true;
        for(int i=0;i<=t;i++){
            dpl[i]=0;
        }
        for(int i=1;i<=n;i++){
            okl[i]=false;
            int cost1=a[i].first+a[i].second-2;
            int cost2=a[i].first-a[i].second-1+l;
            for(int j=t;j>=0;j--){
                dpl[j]+=cost1;
                if(j>=cost2){
                    dpl[j]=min(dpl[j],dpl[j-cost2]);
                }
                if(dpl[j]<=t){
                    okl[i]=true;
                }
            }
        }
    }
    {
        okr[n+1]=true;
        for(int i=0;i<=t;i++){
            dpr[i]=0;
        }
        for(int i=n;i>=1;i--){
            okr[i]=false;
            int cost1=l*2-a[i].first-a[i].second;
            int cost2=l-a[i].first+a[i].second-1;
            for(int j=t;j>=0;j--){
                dpr[j]+=cost1;
                if(j>=cost2){
                    dpr[j]=min(dpr[j],dpr[j-cost2]);
                }
                if(dpr[j]<=t){
                    okr[i]=true;
                }
            }
        }
    }
    for(int i=0;i<=n;i++){
        if(okl[i]&&okr[i+1]){
            cout << "Yes\n";
            exit(0);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> l >> n >> t;
    t/=2;
    for(int i=1;i<=n;i++){
        cin >> a[i].first >> a[i].second;
    }
    for(int i=0;i<2;i++){
        sort(a+1,a+n+1);
        solve();
        sort(a+1,a+n+1,[&](pair<int,int> x,pair<int,int> y){
            return x.first<y.first||(x.first==y.first&&x.second>y.second);
        });
        solve();
        for(int i=1;i<=n;i++){
            swap(a[i].first,a[i].second);
        }
    }
    cout << "No\n";
}