#include<bits/stdc++.h>

using namespace std;

int main(){
    auto gen=[&](int testcase){
        cout << "TEST CASE #" << testcase << endl;
        string name=to_string(testcase);
        if(name.size()==1)name="0"+name;
        ifstream fin("input/"+name+".in");
        ofstream fout("espresso/test_"+name+".in");
        int n,m;
        fin >> n >> m;
        map<vector<int>,int> a;
        vector<bool> seen((1<<n),false);
        fout << ".i " << n << "\n";
        fout << ".o 1\n";
        fout << ".ilb";
        for(int i=0;i<n;i++)fout << " " << char('a'+i);
        fout << "\n";
        for(int j=0;j<m;j++){
            vector<int> v(n);
            int mask=0;
            bool ok=true;
            for(int i=0;i<n;i++){
                if(!(fin >> v[i])){
                    ok=false;
                    break;
                }
                if(v[i]){
                    mask|=(1<<i);
                }
            }
            if(!ok)break;
            int r;
            fin >> r;
            assert(!seen[mask]);
            seen[mask]=true;
            a[v]=r;
        }
        for(int mask=0;mask<(1<<n);mask++){
            if(seen[mask])continue;
            vector<int> v(n);
            for(int i=0;i<n;i++){
                if(mask>>i&1){
                    v[i]=1;
                }
            }
            a[v]=2;
        }
        fout << ".p " << a.size() << "\n";
        for(auto [v,x]:a){
            for(auto i:v)fout << i;
            fout << " " << "01-"[x] << "\n";
        }
        fout << ".e\n";
        // vector<vector<int>> prime;
        // while(!a.empty()){
        //     int s=a.size();
        //     cerr << s << " ";
        //     map<vector<int>,int> b;
        //     map<vector<int>,bool> good;
        //     for(auto [v,c]:a){
        //         for(int j=0;j<n;j++){
        //             auto state=v;
        //             if(state[j]==-1)continue;
        //             state[j]^=1;
        //             auto it=a.find(state);
        //             if(it!=a.end()){
        //                 good[v]=true;
        //                 good[state]=true;
        //                 state[j]=-1;
        //                 b[state]|=(c|it->second);
        //             }
        //         }
        //     }
        //     for(auto [v,x]:a){
        //         if(!good[v]){
        //             prime.emplace_back(v);
        //         }
        //     }
        //     swap(a,b);
        // }
        // cerr << "\n";
        // fout << ans.size() << "\n";
        // int sum=ans.size()-1;
        // for(auto v:ans){
        //     vector<int> b;
        //     for(int i=0;i<n;i++){
        //         if(v[i]==0)b.emplace_back(-i-1);
        //         if(v[i]==1)b.emplace_back(i+1);
        //     }
        //     fout << b.size();
        //     for(auto x:b)fout << " " << x;
        //     fout << "\n";
        //     sum+=b.size()-1;
        // }
        // cout << "SIZE = " << sum << "\n";
    };
    for(int i=6;i<=7;i++)gen(i);
}