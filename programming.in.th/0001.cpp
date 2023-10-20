#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b,c;
    cin >> a >> b >> c;
    int x=a+b+c;
    if(x>79)cout << "A";
    else if(x>74)cout << "B+";
    else if(x>69)cout << "B";
    else if(x>64)cout << "C+";
    else if(x>59)cout << "C";
    else if(x>54)cout << "D+";
    else if(x>49)cout << "D";
    else cout << "F";
}