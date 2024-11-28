#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    ll sum=accumulate(a.begin(),a.end(),0LL);
    int l=-1,r=sum/n;
    while(l<r){
        int m=l+(r-l+1)/2;
        auto b=a;
        for(int t=0;t<30;t++){
            for(int i=0;i<n;i++){
                if(b[i]>m){
                    int d=(b[i]-m+1)/2;
                    b[i]-=d*2;
                    b[(i+1)%n]+=d;
                }
            }
        }
        if(b==vector<int>(n,m)){
            l=m;
        }else{
            r=m-1;
        }
    }
    if(l==-1){
        cout << -1 << "\n";
    }else{
        cout << sum-1LL*l*n << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}