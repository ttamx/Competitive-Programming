#include<bits/stdc++.h>

using namespace std;

using db = long double;

const int N=1005;
const db EPS=1e-9;

int n;
array<int,N> a,b,c;
vector<db> points;

struct Line{
    db m,c;
    db isect(const Line &o){
        if(m==o.m)return 0;
        return (c-o.c)/(o.m-m);
    }
}line[N];

int calc(db x){
    pair<db,int> base(a[1]*x+c[1],b[1]);
    int res=1;
    for(int i=2;i<=n;i++)res+=base<make_pair(a[i]*x+c[i],b[i]);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i] >> b[i] >> c[i];
    int ans=n;
    for(int t=0;t<2;t++){
        ans=min(ans,calc(EPS));
        for(int i=2;i<=n;i++){
            if(b[i]!=b[1]){
                line[i].m=1.l*(a[1]-a[i])/(b[i]-b[1]);
                line[i].c=1.l*(c[1]-c[i])/(b[i]-b[1]);
                for(int j=2;j<i;j++)if(b[j]!=b[1])points.emplace_back(line[i].isect(line[j]));
            }
        }
        sort(points.begin(),points.end());
        db p=0;
        for(auto x:points)if(x>0){
            if(x-p<EPS)continue;
            ans=min(ans,calc(x));
            p=x;
        }
        points.clear();
        swap(a,b),swap(a,c);
    }
    cout << ans;
}