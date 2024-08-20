#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=505;
const int M=100005;

int n,m,q;
tuple<int,int,int> e[M];
int p[N],l[M],r[M];
vector<tuple<int,int,int>> a;

int fp(int u){
    return p[u]=(p[u]==u?u:fp(p[u]));
}

void uni(int u,int v){
    u=fp(u),v=fp(v);
    p[u]=v;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        auto &[w,u,v]=e[i];
        cin >> u >> v >> w;
    }
    sort(e,e+m);
    for(int i=0;i<m;i++)r[i]=m;
    for(int i=0;i<m;i++){
        iota(p+1,p+n+1,1);
        l[i]=i;
        auto [w,u,v]=e[i];
        while(fp(u)!=fp(v)){
            l[i]--;
            if(l[i]<0)break;
            auto [_,x,y]=e[l[i]];
            uni(x,y);
        }
        if(l[i]>=0)r[l[i]]=i;
    }
    for(int i=0;i<m;i++){
        int w=get<0>(e[i]);
        if(l[i]>=0){
            int wl=get<0>(e[l[i]]);
            int wm=(wl+w+1)/2;
            a.emplace_back(wm,-1,w-wm);
        }else{
            a.emplace_back(0,-1,w);
        }
        a.emplace_back(w,+2,0);
        if(r[i]<m){
            int wr=get<0>(e[r[i]]);
            int wm=(w+wr+1)/2;
            a.emplace_back(wm,-1,w-wm);
        }
    }
    sort(a.rbegin(),a.rend());
    ll sum=0,m=0,p=0;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        while(!a.empty()&&get<0>(a.back())<=x){
            auto [p2,m2,c]=a.back();
            a.pop_back();
            sum+=(p2-p)*m+c;
            m+=m2;
            p=p2;
        }
        cout << sum+(x-p)*m << "\n";
    }
}