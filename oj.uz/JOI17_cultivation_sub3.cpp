#include<bits/stdc++.h>

using namespace std;

const int N=305;
const int INF=2e9;

int n;
int r,c;
int x[N],y[N];

int calc(int dx){
    vector<int> xs;
    for(int i=0;i<n;i++){
        xs.emplace_back(x[i]);
        xs.emplace_back(x[i]+dx+1);
    }
    sort(xs.begin(),xs.end());
    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    int xn=xs.size();
    vector<vector<pair<int,int>>> event(xn);
    for(int i=0;i<n;i++){
        int xi=lower_bound(xs.begin(),xs.end(),x[i])-xs.begin();
        int xj=lower_bound(xs.begin(),xs.end(),x[i]+dx+1)-xs.begin();
        assert(xi<xj);
        event[xi].emplace_back(y[i],1);
        event[xj].emplace_back(y[i],0);
    }
    multiset<int> mxa,mxb,sum;
    multiset<int> pts,dif;
    int res=INF;
    int pre=1;
    vector<int> mp(xn),ms(xn);
    for(int i=0;i<xn;i++){
        while(xs[i]-xs[pre]-1>=r){
            
        }
        for(auto [x,t]:event[i]){
            if(t){
                auto it=pts.emplace(x);
                if(next(it)!=pts.end()&&it!=pts.begin()){
                    dif.erase(dif.find(*next(it)-*prev(it)));
                }
                if(next(it)!=pts.end()){
                    dif.emplace(*next(it)-*it);
                }
                if(it!=pts.begin()){
                    dif.emplace(*it-*prev(it));
                }
            }else{
                auto it=pts.find(x);
                assert(it!=pts.end());
                if(next(it)!=pts.end()){
                    dif.erase(dif.find(*next(it)-*it));
                }
                if(it!=pts.begin()){
                    dif.erase(dif.find(*it-*prev(it)));
                }
                if(next(it)!=pts.end()&&it!=pts.begin()){
                    dif.emplace(*next(it)-*prev(it));
                }
                pts.erase(it);
            }
        }
        if(pts.empty()){
            mxa=0,mxb=0,sum=0;
            pre=xs[i]+1;
        }else{
            mxa=max(mxa,*pts.begin()-1);
            mxb=max(mxb,c-*pts.rbegin());
            if(!dif.empty()){
                sum=max(sum,*dif.rbegin()-1);
            }
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c >> n;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }
    vector<int> xs;
    for(int i=0;i<n;i++){
        xs.emplace_back(x[i]-1);
        xs.emplace_back(r-x[i]);
        for(int j=0;j<n;j++){
            int d=abs(x[i]-x[j]);
            xs.emplace_back(d);
            if(d>0){
                xs.emplace_back(d-1);
            }
        }
    }
    sort(xs.begin(),xs.end());
    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    int ans=r+c-2;
    for(int dx:xs){
        ans=min(ans,calc(dx));
    }
    cout << ans;
}