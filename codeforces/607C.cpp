#include<bits/stdc++.h>

using namespace std;

template<class STR>
vector<int> z_algorithm(const STR &s){
    int n=(int)s.size();
    vector<int> z(n);
    z[0]=n;
    for(int i=1,l=0,r=1;i<n;i++){
        if(i<r)z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    return z;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    n--;
    string a,b;
    cin >> a >> b;
    for(auto &x:a){
        if(x=='N')x='S';
        else if(x=='S')x='N';
        else if(x=='E')x='W';
        else if(x=='W')x='E';
        else assert(false);
    }
    reverse(a.begin(),a.end());
    auto z=z_algorithm(a+b);
    for(int i=0;i<n;i++){
        if(z[i+n]>=n-i){
            cout << "NO\n";
            exit(0);
        }
    }
    cout << "YES\n";
}