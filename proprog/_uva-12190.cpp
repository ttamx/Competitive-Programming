#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b;
    while(cin >> a >> b){
        if(a==0&&b==0)break;
        int cnt=0;
        int val=min(100,a/2);
        cnt+=val;
        a-=2*val;
        val=min(9900,a/3);
        cnt+=val;
        a-=3*val;
        val=min(990000,a/5);
        cnt+=val;
        a-=5*val;
        cnt+=a/7;
        int l=0,r=cnt/2;
        auto calc=[&](int x){
            int res=0;
            int val=min(x,100);
            x-=val;
            res+=val*2;
            val=min(x,9900);
            x-=val;
            res+=val*3;
            val=min(x,990000);
            x-=val;
            res+=val*5;
            res+=x*7;
            return res;
        };
        while(l<r){
            int m=(l+r)/2;
            if(calc(cnt-m)-calc(m)<=b)r=m;
            else l=m+1;
        }
        cout << calc(l) << '\n';
    }
}