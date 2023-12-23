#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    string a,b;
    cin >> a >> b;
    for(int i=0;i<=5;i++){
        for(int j=0;j<a.size();j++)if(a.substr(j,b.size())==b)return void(cout << i << "\n");    
        a=a+a;
    }
    cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}