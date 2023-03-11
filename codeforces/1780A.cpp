#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> e,o;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x&1)o.push_back(i+1);
        else e.push_back(i+1);
    }
    if(o.empty()||(n==3&&o.size()==2)){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    if(o.size()>=3){
        cout << o[0] << ' ' << o[1] << ' ' << o[2] << '\n';
    }else{
        cout << o[0] << ' ' << e[0] << ' ' << e[1] << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}