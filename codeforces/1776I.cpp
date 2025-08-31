#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<ll,ll>> pts(n);
    for(auto &[x,y]:pts){
        cin >> x >> y;
    }
    vector<int> l(n),r(n);
    for(int i=0;i<n;i++){
        l[i]=(i+1)%n;
        r[(i+1)%n]=i;
    }
    vector<bool> del(n);
    auto work=[&](int p){
        l[r[p]]=l[p];
        r[l[p]]=r[p];
        del[p]=true;
    };
    auto cross=[&](pair<ll,ll> a,pair<ll,ll> b){
        return a.first*b.second-a.second*b.first;
    };
    int t=0;
    if(n%2==0){
        cout << "Alberto" << endl;
    }else{
        cout << "Beatrice" << endl;
        int p;
        cin >> p;
        p--;
        work(p);
        t++;
    }
    for(;t<n-2;t+=2){
        int p=-1;
        ll area=LLONG_MAX;
        for(int i=0;i<n;i++){
            if(del[i])continue;
            auto a=pts[i],b=pts[l[i]],c=pts[r[i]];
            a.first-=c.first,a.second-=c.second;
            b.first-=c.first,b.second-=c.second;
            ll cur=abs(cross(a,b));
            if(cur<area){
                p=i;
                area=cur;
            }
        }
        assert(p!=-1);
        cout << p+1 << endl;
        work(p);
        cin >> p;
        p--;
        work(p);
    }
}