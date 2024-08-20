#include<bits/stdc++.h>

using namespace std;

const int N=5e6+5;

int n,m,k;
int a[N],cnt[N],idx[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n >> k;
    for(int i=0;i<m;i++){
        cin >> a[i];
        cnt[a[i]]++;
    }
    sort(a,a+m,greater<int>());
    long long ans=0,sum=0;
    int s=n-k-1;
    for(int i=0;i<s;i++){
        sum+=a[i];
    }
    for(int i=0;i<m;i++)idx[a[i]]=i;
    for(int g=1;g<N;g++){
        int pos=N,pos2=N;
        int num=0;
        for(int i=g;i<N;i+=g){
            if(cnt[i]){
                num++;
                pos2=pos;
                pos=idx[i];
                if(num>k)break;
            }
        }
        if(num<=k)continue;
        int cur=s;
        long long res=sum;
        if(pos<cur){
            res+=a[cur];
            res-=a[pos];
            cur++;
            if(pos2<cur)continue;
        }
        ans=max(ans,res+g);
    }
    cout << ans;
}