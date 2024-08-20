#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> nimber(n+1);
    for(int i=1;i<=n;i++){
        vector<bool> seen(3);
        if(nimber[i-1]<3)seen[nimber[i-1]]=true;
        if(nimber[i/k]<3)seen[nimber[i/k]]=true;
        int mex=0;
        while(seen[mex])mex++;
        nimber[i]=mex;
    }
    for(int i=0;i<=n;i++){
        cerr << nimber[i] << " \n"[i%k==k-1];
    }
}