#include<bits/stdc++.h>

using namespace std;

const int S=11;

int main(){
    for(int i=0;i<S;i++){
        for(int j=0;j<S;j++){
            cout << "x[" << i << "][" << j << "]=(";
            for(int k=0;k<S;k++){
                cout << "(ll)l[" << i << "][" << k << "]*r[" << k << "][" << j << "]" << "+)"[k==S-1];
            }
            cout << "%MOD;";
        }
        cout << "\n";
    }
    // for(int j=0;j<S;j++){
    //     cout << "y[" << j << "]=(y[" << j << "]";
    //     for(int k=0;k<S;k++){
    //         cout << "+(ll)x[" << k << "]*pw[i][b][" << k << "][" << j << "]";
    //     }
    //     cout << ")%MOD\n";
    // }
}