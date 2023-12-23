#include<bits/stdc++.h>

using namespace std;

const int N=200005;
const int M=255;
int b,n,d,m;

struct fenwick{
    int t[N];
    void add(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int read(int i){
        i=min(i,N-1);
        i=max(i,0);
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

struct fenwick3d{
    int t[M][M][M];
    void add(int x,int y,int z,int v){
        for(int xx=x;xx<M;xx+=xx&-xx)for(int yy=y;yy<M;yy+=yy&-yy)for(int zz=z;zz<M;zz+=zz&-zz)t[xx][yy][zz]+=v;
    }
    int read(int x,int y,int z){
        int res=0;
        x=min(x,M-1);
        x=max(x,0);
        y=min(y,M-1);
        y=max(y,0);
        z=min(z,M-1);
        z=max(z,0);
        for(int xx=x;xx>0;xx-=xx&-xx)for(int yy=y;yy>0;yy-=yy&-yy)for(int zz=z;zz>0;zz-=zz&-zz)res+=t[xx][yy][zz];
        return res;
    }
}f2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> b >> n >> d >> m;
    long long ans=0;
    if(b==1){
        vector<int> a(n);
        for(auto &x:a)cin >> x;
        sort(a.begin(),a.end());
        for(int i=0;i<n;i++)ans+=i-(lower_bound(a.begin(),a.end(),a[i]-d)-a.begin());
    }else if(b==2){
        vector<pair<int,int>> a(n);
        for(auto &[x,y]:a){
            int xx,yy;
            cin >> xx >> yy;
            x=xx-yy;
            y=xx+yy;
        }
        sort(a.begin(),a.end());
        int idx=0;
        for(auto [x,y]:a){
            while(x-a[idx].first>d)f.add(a[idx++].second,-1);
            ans+=f.read(y+d)-f.read(y-d-1);
            f.add(y,1);
        }
    }else{
        vector<tuple<int,int,int,int>> a(n);
        for(auto &[w,x,y,z]:a){
            int xx,yy,zz;
            cin >> xx >> yy >> zz;
            w=xx+yy+zz;
            x=xx+yy-zz+75;
            y=xx-yy+zz+75;
            z=xx-yy-zz+150;
        }
        sort(a.begin(),a.end());
        int idx=0;
        for(auto [w,x,y,z]:a){
            while(w-get<0>(a[idx])>d){
                auto [ww,xx,yy,zz]=a[idx++];
                f2.add(xx,yy,zz,-1);
            }
            ans+=(f2.read(x+d,y+d,z+d)-f2.read(x+d,y+d,z-d-1)-f2.read(x+d,y-d-1,z+d)+f2.read(x+d,y-d-1,z-d-1))-(f2.read(x-d-1,y+d,z+d)-f2.read(x-d-1,y+d,z-d-1)-f2.read(x-d-1,y-d-1,z+d)+f2.read(x-d-1,y-d-1,z-d-1));
            f2.add(x,y,z,1);
        }
    }
    cout << ans;
}