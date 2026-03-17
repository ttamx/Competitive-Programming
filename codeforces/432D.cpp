#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    vector<int> z(n);
    z[0]=n;
    for(int i=1,l=0,r=1;i<n;i++){
        if(i<r)z[i]=min(z[i-l],r-i);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    vector<int> f(n+1);
    for(auto x:z)f[x]++;
    for(int i=n;i>=1;i--)f[i-1]+=f[i];
    vector<int> a;
    for(int i=n-1;i>=0;i--){
        if(i+z[i]==n){
            a.emplace_back(z[i]);
        }
    }
    cout << a.size() << "\n";
    for(auto x:a){
        cout << x << " " << f[x] << "\n";
    }
}