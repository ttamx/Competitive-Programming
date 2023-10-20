#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2005;

string a,b;
ll qa[N],qb[N],hsh[30];

mt19937 rng(time(0));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<30;i++)hsh[i]=llabs(rng())+1ll;
    cin >> a >> b;
    a=" "+a;
    b=" "+b;
    for(int i=1;i<a.size();i++)qa[i]=qa[i-1]+hsh[a[i]-'A'];
    for(int i=1;i<b.size();i++)qb[i]=qb[i-1]+hsh[b[i]-'A'];
    for(int sz=min(a.size(),b.size())-1;sz>0;sz--){
        map<ll,bool> mp;
        for(int l=1,r=sz;r<a.size();l++,r++)mp[qa[r]-qa[l-1]]=true;
        for(int l=1,r=sz;r<b.size();l++,r++)if(mp[qb[r]-qb[l-1]])cout << sz,exit(0);
    }
    cout << 0;
}