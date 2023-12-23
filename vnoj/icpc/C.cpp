#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    cout << "YES\n";
    cout << n*7 << "\n";
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        cout << x << " " << y << " " << 3 << "\n";
        cout << x << " " << y+1 << " " << 2 << "\n";
        cout << x+1 << " " << y+1 << " " << 2 << "\n";
        cout << x-1 << " " << y << " " << 2 << "\n";
        cout << x+1 << " " << y << " " << 2 << "\n";
        cout << x-1 << " " << y-1 << " " << 2 << "\n";
        cout << x << " " << y-1 << " " << 2 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}