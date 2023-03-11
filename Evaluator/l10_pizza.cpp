#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
long long p;
long long t[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p;
    for(int i=1;i<=n;++i)cin >> t[i];
    long long l=0,r=2e9;
    while(l<r){
        long long m=(l+r)>>1;
        long long cnt=0;
        for(int i=1;i<=n;++i)cnt+=m/t[i]+1;
        if(cnt>=p){
            r=m;
        }else{
            l=m+1;
        }
    }
    cout << l;
}