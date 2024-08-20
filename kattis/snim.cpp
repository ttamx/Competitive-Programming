#include<bits/stdc++.h>

using namespace std;

const int L=10000;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> nimber(L+1);
    for(int i=0;i<=L;i++){
        vector<int> res;
        for(auto x:a){
            if(i-x>=0){
                res.emplace_back(nimber[i-x]);
            }
        }
        vector<bool> seen((int)res.size()+1);
        for(auto x:res)seen[x]=true;
        int mex=0;
        while(seen[mex])mex++;
        nimber[i]=mex;
    }
    int q;
    cin >> q;
    while(q--){
        int k;
        cin >> k;
        int sum=0;
        while(k--){
            int x;
            cin >> x;
            sum^=nimber[x];
        }
        cout << (sum?"W":"L");
    }
}