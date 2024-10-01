#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<long long,long long>> a(n),b(n);
    for(auto &[x,y]:a){
        cin >> x >> y;
    }
    for(auto &[x,y]:b){
        cin >> x >> y;
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    if(a[0]==a[n-1]){
        if(b[0]==b[n-1]){
            cout << 0 << " " << b[0].first << " " << b[0].second;
        }else{
            cout << -1;
        }
        exit(0);
    }
    bool swapp=false;
    if(a[0].first==a[n-1].first){
        swapp=true;
        for(auto &[x,y]:a)swap(x,y);
        for(auto &[x,y]:b)swap(x,y);
    }
    long long aa=a[0].first-a[n-1].first;
    long long bb=b[0].first-b[n-1].first;
    if(bb%aa){
        cout << -1;
        exit(0);
    }
    long long s=bb/aa;
    long long x=b[0].first-s*a[0].first;
    long long y=b[0].second-s*a[0].second;
    for(int i=0;i<n;i++){
        if(s*a[i].first+x!=b[i].first){
            cout << -1;
            exit(0);
        }
        if(s*a[i].second+y!=b[i].second){
            cout << -1;
            exit(0);
        }
    }
    if(swapp){
        swap(x,y);
    }
    cout << s << " " << x << " " << y;
}