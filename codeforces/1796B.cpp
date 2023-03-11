#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string a,b;
    cin >> a >> b;
    if(a[0]==b[0]){
        cout << "YES\n";
        cout << a[0] << "*\n";
        return;
    }
    if(a.back()==b.back()){
        cout << "YES\n";
        cout << "*" << a.back() << "\n";
        return;
    }
    for(int i=0;i+1<a.size();i++){
        for(int j=0;j+1<b.size();j++){
            if(a[i]==b[j]&&a[i+1]==b[j+1]){
                cout << "YES\n";
                cout << "*" << a[i] << a[i+1] << "*\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}