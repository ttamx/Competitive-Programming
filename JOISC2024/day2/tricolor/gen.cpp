#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ofstream fout("out.txt");
    int n,q,l;
    cin >> n >> q >> l;
    fout << n << "\n";
    for(int i=0;i<n;i++)fout << "RGB"[rand()%3];
    fout << "\n";
    fout << q << "\n";
    for(int i=1;i<=q;i++)fout << q << " \n"[i==q];
}