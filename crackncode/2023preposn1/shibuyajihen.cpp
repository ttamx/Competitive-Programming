#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    cout << "#" << string(2*n-3,' ') << "#";
    cout << "\n";
    for(int i=0;i<n*2-3;i++){
        cout << "#" << string(i,' ') << '#' << string(2*n-4-i,' ') << "#";
        cout << "\n";
    }
    cout << "#" << string(2*n-3,' ') << "#";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}