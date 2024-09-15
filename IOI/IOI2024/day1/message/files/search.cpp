#include<bits/stdc++.h>

using namespace std;

mt19937 rng(1231);

int main(){
    cout << "{";
    for(int i=0;i<30;i++){
        cout << (rng()&((1<<31)-1)) << ",}"[i==29];
    }
}