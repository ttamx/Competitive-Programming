#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    auto read=[&](){
        int k;
        cin >> k;
        for(int i=0;i<k;i++){
            string s;
            cin >> s;
        }
        return k;
    };
    while(true){
        cout << "next 0" << endl;
        read();
        cout << "next 0 1" << endl;
        if(read()==2)break;
    }
    while(true){
        cout << "next 0 1 2 3 4 5 6 7 8 9" << endl;
        if(read()==1)break;
    }
    cout << "done" << endl;
}