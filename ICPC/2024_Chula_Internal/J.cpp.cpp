#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3e5+5;

struct Fenwick{
    int n;
    int t[N];
    void init(int _n){
        n=_n;
        for(int i=1;i<=n;i++){
            t[i]=0;
        }
    }
    void update(int x,int v){
        for(int i=x+1;i<=n;i+=i&-i){
            t[i]+=v;
        }
    }
    int query(int x){
        int res=0;
        for(int i=x+1;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
}fx,fy,tx,ty;

void solve(){
    int h,w,n;
    cin >> h >> w >> n;
    fx.init(n);
    fy.init(n);
    tx.init(n);
    ty.init(n);
    vector<pair<int,int>> a(n);
    vector<int> xs,ys;
    for(auto &[x,y]:a){
        cin >> x >> y;
        xs.emplace_back(x);
        ys.emplace_back(y);
    }
    sort(xs.begin(),xs.end());
    sort(ys.begin(),ys.end());
    for(auto &[x,y]:a){
        x=lower_bound(xs.begin(),xs.end(),x)-xs.begin();
        y=lower_bound(ys.begin(),ys.end(),y)-ys.begin();
    }
    vector<int> vx(n),vy(n);
    vector<set<int>> sx(n),sy(n);
    map<pair<int,int>,bool> seen;
    ll ans=0,cx=0,cy=0;
    auto calcx=[&](int x){
        if(sx[x].empty())return 0;
        if(sx[x].size()==1)return w;
        int l=*sx[x].begin(),r=*sx[x].rbegin();
        return ys[l]+w-ys[r]+1+fy.query(r-1)-fy.query(l);
    };
    auto calcy=[&](int y){
        if(sy[y].empty())return 0;
        if(sy[y].size()==1)return h;
        int l=*sy[y].begin(),r=*sy[y].rbegin();
        return xs[l]+h-xs[r]+1+fx.query(r-1)-fx.query(l);
    };
    for(auto [x,y]:a){
        ans-=calcx(x);
        ans-=calcy(y);
        if(!sx[x].empty()){
            cx--;
            fx.update(x,-1);
        }
        if(!sy[y].empty()){
            cy--;
            fy.update(y,-1);
        }
        if(sx[x].size()>1){
            int l=*sx[x].begin(),r=*sx[x].rbegin();
            ty.update(l+1,-1);
            ty.update(r,+1);
        }
        if(sy[y].size()>1){
            int l=*sy[y].begin(),r=*sy[y].rbegin();
            tx.update(l+1,-1);
            tx.update(r,+1);
        }
        if(!seen[{x,y}]){
            if(sx[x].empty()){
                ans+=tx.query(x);
            }
            if(sy[y].empty()){
                ans+=ty.query(y);
            }
            sx[x].emplace(y);
            sy[y].emplace(x);
        }else{
            sx[x].erase(y);
            sy[y].erase(x);
            if(sx[x].empty()){
                ans-=tx.query(x);
            }
            if(sy[y].empty()){
                ans-=ty.query(y);
            }
        }
        seen[{x,y}]^=true;
        if(sx[x].size()>1){
            int l=*sx[x].begin(),r=*sx[x].rbegin();
            ty.update(l+1,+1);
            ty.update(r,-1);
        }
        if(sy[y].size()>1){
            int l=*sy[y].begin(),r=*sy[y].rbegin();
            tx.update(l+1,+1);
            tx.update(r,-1);
        }
        if(!sx[x].empty()){
            cx++;
            fx.update(x,+1);
        }
        if(!sy[y].empty()){
            cy++;
            fy.update(y,+1);
        }
        ans+=calcx(x);
        ans+=calcy(y);
        cout << ans-2*cx*cy << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}