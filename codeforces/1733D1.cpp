#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,x,y;
    cin >> n >> x >> y;
    string a,b;
    cin >> a >> b;
    vector<int> v;
    for(int i=0;i<n;++i){
        if(a[i]!=b[i])v.emplace_back(i);
    }
    if(v.size()%2==1){
        cout << -1 << '\n';
        return;
    }else if(v.size()==2 && v[0]+1==v[1]){
        cout << min(y*2ll,x) << '\n';
        return;
    }
    cout << y*(long long)(v.size()/2) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}

