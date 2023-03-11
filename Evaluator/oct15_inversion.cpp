#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

long long ans;

vi merge(vi &a,vi &b){
    int asz=a.size();
    int bsz=b.size();
    int i=0,j=0;
    vi c;
    while(i<asz&&j<bsz){
        if(a[i]<=b[j]){
            c.emplace_back(a[i++]);
        }
        else{
            ans+=asz-i;
            c.emplace_back(b[j++]);
        }
    }
    while(i<asz)c.emplace_back(a[i++]);
    while(j<bsz){
        ans+=asz-i;
        c.emplace_back(b[j++]);
    }
    return c;
}

vi sol(vi &v){
    int sz=v.size();
    if(sz<=1)return v;
    int mid=sz/2;
    vi a(v.begin(),v.begin()+mid);
    vi b(v.begin()+mid,v.end());
    vi sa=sol(a);
    vi sb=sol(b);
    return merge(sa,sb);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vi v(n);
    for(auto &x:v)cin >> x;
    sol(v);
    cout << ans;
}