#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    int g=0;
    for(auto &x:a){
        cin >> x;
        g=gcd(g,x);
    }
    for(auto &x:a)x/=g;
    string s="",t="";
    for(int i=0;i<n;i++){
        while(a[i]>=2){
            s.push_back('a'+i);
            a[i]-=2;
        }
        if(a[i]){
            t.push_back('a'+i);
        }
    }
    string pat=s+t;
    reverse(s.begin(),s.end());
    pat+=s;
    cout << (g%2==0||t.size()<2?g:0) << "\n";
    for(int i=0;i<g;i++){
        cout << pat;
        reverse(pat.begin(),pat.end());
    }
    cout << "\n";
}