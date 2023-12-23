#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    int cnt=0;
    for(auto &x:s)cnt+=x=='B';
    if(cnt==k)return void(cout << 0 << "\n");
    cout << 1 << "\n";
    if(cnt<k){
        int id=0;
        while(cnt<k)if(s[id++]=='A')cnt++;
        cout << id << " B\n";
    }else{
        int id=0;
        while(cnt>k)if(s[id++]=='B')cnt--;
        cout << id << " A\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}