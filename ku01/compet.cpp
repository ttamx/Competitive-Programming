#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,c;
    cin >> n >> c,c--;
    vector<vector<int>> a(n);
    for(auto &v:a){
        v.resize(n);
        for(auto &x:v)cin >> x,x--;
    }
    vector<int> t(n);
    iota(t.begin(),t.end(),0);
    while(t.size()>1){
        vector<int> tmp;
        for(int i=0;i<t.size();i+=2){
            int w=a[t[i]][t[i+1]];
            if((c==t[i]||c==t[i+1])&&w!=c)w=c,c=-1;
            tmp.push_back(w);
        }
        t=tmp;
    }
    cout << t[0]+1;
}