#include <bits/stdc++.h>

using namespace std;

int main() {
    string a,b;
    while(cin >> a >> b){
        if(b=="..._.")cout << "k";
        else cout << char('a'+(a.size()-1)*5+b.size()-(a.size()<3));
    }
}