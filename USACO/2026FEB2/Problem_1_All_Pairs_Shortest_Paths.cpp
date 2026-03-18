#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> xs,ys,zs;
    vector<tuple<int,int,int,int>> a(n);
    map<tuple<int,int,int>,int> cnt;
    map<tuple<int,int,int,int>,int> cnt2,cnt3;
    map<int,int> cx[3],cy[3],cz[3];
    for(auto &[x,y,z,d]:a){
        int xx,yy;
        cin >> xx >> yy >> d;
        int dd=d/2;
        if(dd==2)xx--;
        if(dd>=3)yy--;
        if(dd==5)xx++;
        x=yy;
        y=xx;
        z=-xx-yy;
        if(d&2)y--;
        xs.emplace_back(x);
        ys.emplace_back(y);
        zs.emplace_back(z);
        cnt[{x,y,z}]++;
        dd=((d+1)/2)%3;
        cnt2[{x,y,z,dd}]++;
        if(!(d&2)){
            cx[dd][x]++;
            cy[dd][y]++;
            cz[dd][z]++;
            cnt3[{x,y,z,dd}]++;
        }
    }
    sort(xs.begin(),xs.end());
    sort(ys.begin(),ys.end());
    sort(zs.begin(),zs.end());
    ll ans=0;
    for(auto [x,y,z,d]:a){
        ans+=1LL*x*(lower_bound(xs.begin(),xs.end(),x)-xs.begin());
        ans+=1LL*y*(lower_bound(ys.begin(),ys.end(),y)-ys.begin());
        ans+=1LL*z*(lower_bound(zs.begin(),zs.end(),z)-zs.begin());
        ans-=1LL*x*(xs.end()-upper_bound(xs.begin(),xs.end(),x));
        ans-=1LL*y*(ys.end()-upper_bound(ys.begin(),ys.end(),y));
        ans-=1LL*z*(zs.end()-upper_bound(zs.begin(),zs.end(),z));
    }
    ans*=2;
    ans-=1LL*n*(n-1)/2;
    for(auto [_,c]:cnt)ans+=1LL*c*(c-1)/2;
    ll add=0;
    for(auto [e,c]:cnt2){
        auto [x,y,z,d]=e;
        add+=1LL*c*(cnt[{x,y,z}]-c);
    }
    ans+=add/2;
    for(auto [x,y,z,d]:a){
        int dd=((d+1)/2)%3;
        int c=cnt[{x,y,z}];
        if(dd==0){
            if(d&2){
                ans+=upper_bound(xs.begin(),xs.end(),x)-xs.begin();
                ans+=cx[dd][x+1]-cnt3[{x+1,y,z,dd}];
            }else{
                ans+=xs.end()-lower_bound(xs.begin(),xs.end(),x);
            }
        }else if(dd==1){
            if(d&2){
                ans+=upper_bound(ys.begin(),ys.end(),y)-ys.begin();
                ans+=cy[dd][y+1]-cnt3[{x,y+1,z,dd}];
            }else{
                ans+=ys.end()-lower_bound(ys.begin(),ys.end(),y);
            }
        }else{
            if(d&2){
                ans+=upper_bound(zs.begin(),zs.end(),z)-zs.begin();
                ans+=cz[dd][z+1]-cnt3[{x,y,z+1,dd}];
            }else{
                ans+=zs.end()-lower_bound(zs.begin(),zs.end(),z);
            }
        }
        ans-=c;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}