#include<bits/stdc++.h>

using namespace std;

int q,cnt=0;

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> q;
	for(int i=1;i<=q;++i){
        ++cnt;
        int x;
        cin >> x;
        if(x==cnt){
            cout << "BENAR" << endl;
        }else{
            cout << "SALAH" << endl;
            cnt=0;
        }
	}
	return 0;
}

