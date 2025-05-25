#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    (*max_element(a.begin(),a.end()))--;
    if(*max_element(a.begin(),a.end())-*min_element(a.begin(),a.end())>k){
        cout << "Jerry\n";
        return;
    }
    cout << (accumulate(a.begin(),a.end(),0LL)%2==0?"Tom":"Jerry") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}