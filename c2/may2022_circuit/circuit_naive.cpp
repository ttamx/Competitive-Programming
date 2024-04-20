#include<bits/stdc++.h>

using namespace std;

int main(){
    for(int i=3;i<=10;i++){
        string name=to_string(i);
        if(name.size()==1)name="0"+name;
        ifstream fin("input/"+name+".in");
        ofstream fout("output/"+name+".out");
        int n,m;
        fin >> n >> m;
        vector<vector<int>> ans;
        for(int j=1;j<=m;j++){
            vector<int> v(n);
            for(auto &x:v)fin >> x;
            int r;
            fin >> r;
            if(r){
                vector<int> res;
                for(int k=1;k<=n;k++)res.emplace_back(v[k-1]?k:-k);
                ans.emplace_back(res);
            }
        }
        fout << ans.size() << "\n";
        for(auto v:ans){
            fout << v.size();
            for(auto x:v)fout << ' ' << x;
            fout << '\n';
        }
    }
}