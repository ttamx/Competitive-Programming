#include<bits/stdc++.h>

using namespace std;

string t[9]={"la","le","lon","sha","she","shon","ta","te","ton"};

int get_back(string &s){
    if(s.empty())return 0;
    for(int i=0;i<9;i++){
        if(s.size()>=t[i].size()&&s.substr(s.size()-t[i].size(),t[i].size())==t[i]){
            for(int j=0;j<t[i].size();j++)s.pop_back();
            return i;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string a,b;
    cin >> a >> b;
    a.pop_back(),b.pop_back();
    vector<int> c;
    int x=0;
    while(!a.empty()||!b.empty()||x>0){
        x+=get_back(a)+get_back(b);
        c.emplace_back(x%9);
        x/=9;
    }
    reverse(c.begin(),c.end());
    for(auto i:c)cout << t[i];
    cout << "s\n";
}