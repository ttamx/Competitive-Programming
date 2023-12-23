#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    string s;
    cin >> n >> k >> s;
    if(k%2==0){
        sort(s.begin(),s.end());
        cout << s << "\n";
    }else{
        vector<char> a[2];
        for(int i=0;i<n;i++)a[i&1].emplace_back(s[i]);
        for(int i=0;i<2;i++)sort(a[i].begin(),a[i].end());
        int c[2]={};
        for(int i=0;i<n;i++)cout << a[i&1][c[i&1]++];
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}