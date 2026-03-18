#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(m);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    sort(a.rbegin(),a.rend());
    sort(b.rbegin(),b.rend());
    vector<int> c;
    int last=-1;
    c.emplace_back(0);
    for(auto x:a){
        if(x==last){
            c.back()++;
        }else{
            c.emplace_back(1);
            last=x;
        }
    }
    for(int i=1;i<c.size();i++){
        c[i]+=c[i-1];
    }
    auto check=[&](int mid){
        vector<int> d;
        for(int i=0;i<=mid;i++){
            d.emplace_back(c[i]);
        }
        reverse(d.begin(),d.end());
        ll bal=0,lim=0;
        for(int i=0;i<m;i++){
            if(i<mid){
                lim+=c[mid-i];
            }
            bal=min(bal+b[i],lim);
        }
        for(int i=1;i<=mid;i++){
            bal-=c[i];
        }
        return bal>=0;
    };
    int l=0,r=c.size()-1;
    while(l<r){
        int mid=(l+r+1)/2;
        if(check(mid))l=mid;
        else r=mid-1;
    }
    cout << c[l] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}