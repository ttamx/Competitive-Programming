#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    int n=s.size();
    vector<int> a(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x-1]=i;
    }
    int l=0,r=n;
    while(l<r){
        int m=(l+r+1)/2;
        int j=0;
        for(int i=0;i<n;i++){
            if(a[i]>=m){
                if(j<t.size()&&s[i]==t[j]){
                    j++;
                }
            }
        }
        if(j==t.size())l=m;
        else r=m-1;
    }
    cout << l << "\n";
}