#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    string t="";
    for(auto x:s){
        if(x=='B'&&!t.empty()&&t.back()=='A'){
            t.pop_back();
        }else{
            t.push_back(x);
        }
    }
    cout << ((!t.empty()&&t.back()=='A')?"Alice":"Bob") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}