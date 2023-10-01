#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    set<long long> s;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        s.emplace(x);
    }
    int l=0,r=1e9;
    while(l<r){
        int m=(l+r)/2;
        auto it=s.begin();
        bool ok=false;
        for(int i=0;i<3;i++){
            it=s.upper_bound(*it+2*m);
            if(it==s.end()){
                r=m;
                ok=true;
                break;
            }
        }
        if(ok)r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}