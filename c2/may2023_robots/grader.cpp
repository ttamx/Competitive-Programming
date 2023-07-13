#include "robots.cpp"
#include <string>
#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);
    int q,a,b;
    cin >> q >> a >> b;
    std::string s;
    cin >> s;
    init_robots(s,a,b);
    while(q--){
        int k;
        cin >> k;
        cout << update(k) << "\n";
    }
}
