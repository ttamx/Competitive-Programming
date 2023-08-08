#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> b(n*(n-1)/2);
    for(auto &x:b)cin >> x;
    sort(b.begin(),b.end());
    for(int i=0,c=n-1;c>=1;i+=c--)cout << b[i] << " ";
    cout << b.back() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}