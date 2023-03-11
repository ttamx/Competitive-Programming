#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    string a,b;
    cin >> a >> b;
    if(a==b)return void(cout << "YES\n");
    vector<int> cnt(26);
    for(auto x:a)cnt[x-'a']++;
    for(auto x:b)cnt[x-'a']--;
    for(int i=0;i<26;i++)if(cnt[i]!=0)return void(cout << "NO\n");
    if(n>5)return void(cout << "YES\n");
    if(n<4)return void(cout << "NO\n");
    if(n==4){
        if(a[0]>a[3])swap(a[0],a[3]);
        if(b[0]>b[3])swap(b[0],b[3]);
        if(a==b)cout << "YES\n";
        else cout << "NO\n";
    }else{
        if(a[2]==b[2])cout << "YES\n";
        else cout << "NO\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}