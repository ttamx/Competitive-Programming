#include<bits/stdc++.h>

using namespace std;

int main(){
    auto gen=[&](int testcase){
        cout << "TEST CASE #" << testcase << endl;
        string name=to_string(testcase);
        if(name.size()==1)name="0"+name;
        ifstream in("input/"+name+".in");
        ifstream fin("espresso_output/out"+name+".txt");
        ofstream fout("output/output_"+name+".txt");
        int n,m;
        in >> n >> m;
        map<vector<int>,int> a;
        vector<bool> seen(1<<n);
        int s;
        fin >> s;
        vector<vector<int>> ans;
        for(int i=0;i<s;i++){
            vector<int> a;
            string str;
            fin >> str;
            int x;
            fin >> x;
            for(int j=0;j<n;j++){
                if(str[j]=='-')continue;
                a.emplace_back(str[j]=='1'?(j+1):-(j+1));
            }
            if(!a.empty()){
                ans.emplace_back(a);
            }
        }
        fout << ans.size() << "\n";
        int sum=ans.size()-1;
        for(auto v:ans){
            fout << v.size();
            for(auto x:v)fout << " " << x;
            fout << "\n";
            sum+=v.size()-1;
        }
        cout << "SIZE = " << sum << "\n";
    };
    for(int i=6;i<=7;i++)gen(i);
}