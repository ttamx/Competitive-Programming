#include<bits/stdc++.h>

using namespace std;

int c[9];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<9;i++)cin >> c[i];
    vector<int> a(9);
    iota(a.begin(),a.end(),0);
    int cnt=0;
    do{
        bool ok=true;
        vector<int> h[3],v[3],d[2];
        for(auto i:a){
            int val=c[i];
            h[i/3].emplace_back(val);
            v[i%3].emplace_back(val);
            if(i/3==i%3)d[0].emplace_back(val);
            if(i/3+i%3==2)d[1].emplace_back(val);
        }
        for(int i=0;i<3;i++)if(h[i][0]==h[i][1])ok=false;
        for(int i=0;i<3;i++)if(v[i][0]==v[i][1])ok=false;
        for(int i=0;i<2;i++)if(d[i][0]==d[i][1])ok=false;
        cnt+=ok;
    }while(next_permutation(a.begin(),a.end()));
    cout << fixed << setprecision(10) << 1.0*cnt/362880;
}