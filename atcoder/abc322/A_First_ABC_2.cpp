#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    for(int i=0;i<n-2;i++)if(s.substr(i,3)=="ABC")return void(cout << i+1 << "\n");
    cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}