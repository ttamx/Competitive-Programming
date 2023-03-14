#include<bits/stdc++.h>

using namespace std;

int d[7]= {0,1,2,0,2,1,0};

void runcase(){
    vector<int> a(3);
    for(auto &x:a)cin >> x;
    int w=min({a[0]/3,a[1]/2,a[2]/2});
    int ans=w*7;
    a[0]-=w*3;
    a[1]-=w*2;
    a[2]-=w*2;
    int res=0;
    for(int i=0;i<7;i++){
        int sum=0;
        auto v=a;
        for(int j=0;j<7;j++){
            if(v[d[(i+j)%7]]--)sum++;
            else break;
        }
        res=max(res,sum);
    }
    cout << ans+res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}