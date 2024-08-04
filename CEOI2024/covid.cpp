#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int n,t,k;
double p;
string ans;

int ask(int l,int r){
    if(l>r)return false;
    string s(n,'0');
    for(int i=l;i<=r;i++)s[i]='1';
    cout << "Q " << s << endl;
    char res;
    cin >> res;
    return res=='P';
}

int solve(int l,int r){
    while(l<r){
        int m=(l+r)/2;
        if(ask(l,m))r=m;
        else l=m+1;
    }
    ans[l]='1';
    return l;
}

void runcase(){
    ans=string(n,'0');
    for(int l=0;l<n;){
        int r=min(l+k-1,n-1);
        if(ask(l,r)){
            l=solve(l,r)+1;
        }else{
            l+=k;
        }
    }
    cout << "A " << ans << endl;
    string s;
    cin >> s;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> p >> t;
    double q=1-p,r=q;
    double cut=0.57;
    if(p==0.2)cut=0.50;
    if(p==0.039856)cut=0.54;
    if(p==0.104571)cut=0.45;
    k=1;
    while(r>cut&&k<n){
        r*=q;
        k++;
    }
    while(t--)runcase();
}