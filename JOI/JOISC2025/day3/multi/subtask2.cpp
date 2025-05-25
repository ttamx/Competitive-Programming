#include<bits/stdc++.h>

using namespace std;

ofstream fout("subtask1.txt");

int n,l;

void build(int s){
    int cur=0;
    vector<vector<pair<int,int>>> seq(n);
    vector<vector<int>> val(6,vector<int>(n));
    val[0][s]=1;
    int d=0;
    for(;(2<<d)<n;d++){
        int b=1<<d;
        for(int i=0;i<n;i++){
            val[d+1][i]|=val[d][i];
            val[d+1][i]|=val[d][i^b];
            seq[i].emplace_back(val[d][i],i^b);
        }
    }
    vector<int> pos(n);
    iota(pos.begin(),pos.end(),0);
    for(;d>=1;){
        int b=1<<d;
        for(int i=0;i<n;i++){
            if(!val[d][pos[i]]){
                pos[i]^=b;
                assert(val[d][pos[i]]);
            }
        }
        d--;
        for(int i=0;i<n;i++){
            seq[i].emplace_back(val[d][i],pos[i]);
        }
    }
    fout << s+1 << "\n";
    for(auto &v:seq){
        assert(v.size()==l);
        for(auto [c,p]:v){
            fout << "FT"[c] << " " << p+1 << " ";
        }
        fout << "\n";
    }
}

int main(){
    cin >> n >> l;
    fout << l << "\n";
    for(int i=0;i<n;i++){
        build(i);
    }
}