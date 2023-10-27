#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;

vector<pair<int,int>> a;
set<int> sx,sy;
vector<int> vx,vy;
vector<int> vec[N];

struct fenwick{
    ll t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}fl,fr;

long long find_rec(vector<vector<int>> Point,int p,int q){
    sx.emplace(0);
    sy.emplace(0);
    int n=Point.size();
    for(auto v:Point){
        int x=v[0],y=v[1];
        a.emplace_back(x,y);
        sx.emplace(x);
        sy.emplace(y);
    }
    for(auto x:sx)vx.emplace_back(x);
    for(auto y:sy)vy.emplace_back(y);
    for(auto &[x,y]:a){
        x=lower_bound(vx.begin(),vx.end(),x)-vx.begin();
        y=lower_bound(vy.begin(),vy.end(),y)-vy.begin();
        vec[x].emplace_back(y);
        fr.add(y,1);
    }
    int X=vx.size()-1;
    int Y=vy.size()-1;
    ll ans=0;
    auto pmn=[&](){
        int l=0,r=Y;
        while(l<r){
            int m=(l+r)/2;
            if(fr.read(m)>=fl.read(Y)-fl.read(m)-p)r=m;
            else l=m+1;
        }
        return l;
    };
    auto pmx=[&](){
        int l=0,r=Y;
        while(l<r){
            int m=(l+r+1)/2;
            if(fr.read(m)<=fl.read(Y)-fl.read(m)+p)l=m;
            else r=m-1;
        }
        return l;
    };
    auto qmn=[&](){
        int l=0,r=Y;
        while(l<r){
            int m=(l+r)/2;
            if(fl.read(m)>=fr.read(Y)-fr.read(m)-q)r=m;
            else l=m+1;
        }
        return l;
    };
    auto qmx=[&](){
        int l=0,r=Y;
        while(l<r){
            int m=(l+r+1)/2;
            if(fl.read(m)<=fr.read(Y)-fr.read(m)+q)l=m;
            else r=m-1;
        }
        return l;
    };
    for(int x=0;x<vx.size();x++){
        //cerr << "CUR : " << x << "\n";
        for(auto y:vec[x]){
            fl.add(y,1);
            fr.add(y,-1);
            //cerr << "ADD : " << y << "\n";
        }
        int l=max(pmn(),qmn()),r=min(pmx(),qmx());
        //cerr << "(" << l << "," << r << ")\n";
        if(l>r)continue;
        ans+=r-l+1;
    }
    return ans;
}
