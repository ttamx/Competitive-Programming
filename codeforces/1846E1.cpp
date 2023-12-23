#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n;
    cin >> n;
    for(int i=2;i<=60;i++){
        auto check=[&](long long x){
            __int128_t sum=0,val=1;
            for(int j=0;j<=i;j++){
                sum+=val;
                if(sum>n)return 1;
                val*=x;
            }
            return sum==n?0:-1;
        };
        long long l=2,r=1e9;
        while(l<r){
            long long m=(l+r)/2;
            if(check(m)>=0)r=m;
            else l=m+1;
        }
        if(check(l)==0)return void(cout << "YES\n");
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}