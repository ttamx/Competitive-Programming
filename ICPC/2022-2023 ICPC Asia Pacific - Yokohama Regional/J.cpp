#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using point = complex<ll>;


ll dot(const point &a,const point &b){return real(conj(a)*b);}
ll cross(const point &a,const point &b){return imag(conj(a)*b);}
ll cross(const point &a,const point &b,const point &o){return cross(a-o,b-o);}
int sgn(ll x){
    return x<0?-1:x>0?1:0;
}

bool on_segment(const point &p,const point &a,const point &b){
    return cross(a-p,b-p)==0&&dot(a-p,b-p)<0;
}

bool intersect(const point &a,const point &b,const point &c,const point &d){
    return sgn(cross(c,d,a))*sgn(cross(c,d,b))==-1&&sgn(cross(a,b,c))*sgn(cross(a,b,d))==-1;
}

const int N=205;

int n,m;
point a[N];
int id[N];
double ans;
double dp[N][N];

ll get_dist(int i){
    return norm(a[i]-a[id[i]]);
}

bool inside(const point &p){
    int res=0;
    for(int i=1;i<=n;i++){
        point u=a[i],v=a[i%n+1];
        if(on_segment(p,u,v)||u==p)return true;
        ll cur=cross(v,p,u);
        if(imag(u)<imag(p)&&imag(p)<=imag(v)&&cur>0)res^=1;
        if(imag(u)>=imag(p)&&imag(p)>imag(v)&&cur<0)res^=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n+m;i++){
        ll x,y;
        cin >> x >> y;
        a[i]=point(x*2,y*2);
    }
    for(int i=n+1;i<=n+m;i++){
        for(int j=1;j<=n;j++){
            if(on_segment(a[i],a[j],a[j%n+1])||a[i]==a[j]){
                id[i]=j;
                break;
            }
        }
        assert(id[i]!=0);
    }
    vector<int> ord(m);
    iota(ord.begin(),ord.end(),n+1);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return id[i]<id[j]||(id[i]==id[j]&&get_dist(i)<get_dist(j));
    });
    for(int i=1;i<=n+m;i++){
        for(int j=1;j<=n+m;j++){
            dp[i][j]=sqrt(norm(a[i]-a[j])/4);
            for(int k=1;k<=n;k++){
                if(intersect(a[i],a[j],a[k],a[k%n+1])){
                    dp[i][j]=1e18;
                    break;
                }
            }
            if(!inside((a[i]+a[j])/point(2)))dp[i][j]=1e18;
        }
    }
    for(int x=1;x<=n+m;x++){
        for(int u=1;u<=n+m;u++){
            for(int v=1;v<=n+m;v++){
                dp[u][v]=min(dp[u][v],dp[u][x]+dp[x][v]);
            }
        }
    }
    for(int _i=0;_i<m;_i++){
        int i=ord[_i],j=ord[(_i+1)%m];
        ans+=dp[i][j];
    }
    cout << fixed << setprecision(15);
    cout << ans << "\n";
}