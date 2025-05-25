#include<bits/stdc++.h>

using namespace std;

using P = pair<double,double>;

const double EPS=1e-9;
const double INF=1e18;

int n,m;
double ans;
priority_queue<P,vector<P>,greater<P>> pq;

void update(double s,double l){
    if(l<EPS)return;
    double slope=1.0/(s+1);
    double len=s>EPS?l/s+l/(s+2):INF;
    double saved=l/(s+2);
    ans+=saved;
    pq.emplace(slope,len);
    while(!pq.empty()&&saved>0){
        auto [m,w]=pq.top();
        pq.pop();
        if(saved>=w){
            saved-=w;
            ans+=m*w;
        }else{
            ans+=m*saved;
            pq.emplace(m,w-saved);
            break;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    int last=0;
    for(int i=0;i<n;i++){
        int l,r;
        double s;
        cin >> l >> r >> s;
        update(0.0,l-last);
        update(s,r-l);
        last=r;
    }
    update(0.0,m-last);
    cout << fixed << setprecision(12) << ans << "\n";
}