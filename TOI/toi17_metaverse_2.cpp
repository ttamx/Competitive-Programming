#include<bits/stdc++.h>

using namespace std;

const int N=2e4+5;
const int K=1<<17;

struct segtree{
    int s[K];
    void build(int l,int r,int i){
        s[i]=2e9;
        if(l==r)return;
        int m=(l+r)>>1;
        build(l,m,i<<1);
        build(m+1,r,i<<1|1);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||x>r)return;
        if(l==r)return void(s[i]=min(s[i],v));
        int m=(l+r)>>1;
        update(l,m,i<<1,x,v);
        update(m+1,r,i<<1|1,x,v);
        s[i]=min(s[i<<1],s[i<<1|1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 2e9;
        if(x<=l&&r<=y)return s[i];
        int m=(l+r)>>1;
        return min(query(l,m,i<<1,x,y),query(m+1,r,i<<1|1,x,y));
    }
}seg1,seg2;

int m,n,k,p;
int Wr[N],Wc[N],Or[N],Oc[N],Wci[N],Oci[N],dp[20][N];
vector<int> vr,vc;
vector<int> W[N<<1],O[N<<1];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n >> k >> p;
    int ans1=m+n-2,ans2=0;
    for(int i=1;i<=k;i++){
        cin >> Wr[i] >> Wc[i] >> Or[i] >> Oc[i];
        vr.push_back(Wr[i]);
        vr.push_back(Or[i]);
        vc.push_back(Wc[i]);
        vc.push_back(Oc[i]);
        for(int j=1;j<=p;j++)dp[j][i]=Wr[i]+Wc[i]-2;
        if(dp[1][i]+m+n-Or[i]-Oc[i]<ans1)ans1=dp[1][i]+m+n-Or[i]-Oc[i],ans2=1;
    }
    sort(vr.begin(),vr.end());
    sort(vc.begin(),vc.end());
    vr.erase(unique(vr.begin(),vr.end()),vr.end());
    vc.erase(unique(vc.begin(),vc.end()),vc.end());
    int sr=vr.size();
    int sc=vc.size();
    for(int i=1;i<=k;i++){
        Wci[i]=lower_bound(vc.begin(),vc.end(),Wc[i])-vc.begin()+1;
        Oci[i]=lower_bound(vc.begin(),vc.end(),Oc[i])-vc.begin()+1;
        int Wri=lower_bound(vr.begin(),vr.end(),Wr[i])-vr.begin()+1;
        int Ori=lower_bound(vr.begin(),vr.end(),Or[i])-vr.begin()+1;
        W[Wri].push_back(i);
        O[Ori].push_back(i);
    }
    for(int i=2;i<=p;i++){
        seg1.build(1,sc,1);
        seg2.build(1,sc,1);
        for(int l=1;l<=sr;l++){
            for(auto j:O[l]){
                seg1.update(1,sc,1,Oci[j],dp[i-1][j]-Or[j]-Oc[j]);
                seg2.update(1,sc,1,Oci[j],dp[i-1][j]-Or[j]+Oc[j]);
            }
            for(auto j:W[l]){
                int x=seg1.query(1,sc,1,1,Wci[j])+Wr[j]+Wc[j];
                int y=seg2.query(1,sc,1,Wci[j],sc)+Wr[j]-Wc[j];
                dp[i][j]=min({dp[i][j],x,y});
            }
        }
        seg1.build(1,sc,1);
        seg2.build(1,sc,1);
        for(int l=sr;l>=1;l--){
            for(auto j:O[l]){
                seg1.update(1,sc,1,Oci[j],dp[i-1][j]+Or[j]-Oc[j]);
                seg2.update(1,sc,1,Oci[j],dp[i-1][j]+Or[j]+Oc[j]);
            }
            for(auto j:W[l]){
                int x=seg1.query(1,sc,1,1,Wci[j])-Wr[j]+Wc[j];
                int y=seg2.query(1,sc,1,Wci[j],sc)-Wr[j]-Wc[j];
                dp[i][j]=min({dp[i][j],x,y});
            }
        }
        for(int j=1;j<=k;j++)if(dp[i][j]+m+n-Or[j]-Oc[j]<ans1)ans1=dp[i][j]+m+n-Or[j]-Oc[j],ans2=i;
    }
    cout << ans1 << ' ' << ans2;
}