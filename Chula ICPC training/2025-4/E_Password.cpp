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
        if(i<r)z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    int mx=0;
    for(int i=1;i<n;i++){
        int cur=z[i];
        if(i+cur==n)cur--;
        mx=max(mx,cur);
    }
    for(int i=mx;i>=1;i--){
        if(z[n-i]!=i)continue;
        cout << s.substr(0,i) << "\n";
        exit(0);
    }
    cout << "Just a legend\n";
}