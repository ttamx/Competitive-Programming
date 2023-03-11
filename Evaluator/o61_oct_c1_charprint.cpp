#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int N=3e5+5;

int m,p[30];
ll ans,f[N];
string s1,s2;

void update(int i,int v){
    for(;i<N;i+=i&-i){
        f[i]+=v;
    }
    return;
}

int read(int i){
    int ret=0;
    for(;i>0;i-=i&-i){
        ret+=f[i];
    }
    return ret;
}

int main(){
    cin.tie(nullptr);
    for(int i=1;i<N;++i)update(i,1);
    cin >> m;
    cin >> s1;
    cin >> s2;
    s1=" "+s1;
    for(auto c:s2){
        while(s1[++p[c-'a']]!=c&&p[c-'a']<s1.size());
        if(p[c-'a']>s1.size()){
            ans=-1;
            break;
        }
        ans+=read(p[c-'a']);
        if(m==1)update(p[c-'a'],-1);
    }
    cout << ans;
    return 0;
}

