#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<long long> p(n);
    for(auto &x:p)cin >> x;
    for(int s=1;s<n;s*=2){
        for(int i=0;i<n;i+=2*s){
            if(p[i]<p[i+s]){
                a[i]=a[i+s];
            }else if(p[i]==p[i+s]){
                a[i]+=a[i+s];
            }
            p[i]+=p[i+s];
        }
    }
    cout << a[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}