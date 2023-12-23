#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    cout << (n%3==0?"Second":"First") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}