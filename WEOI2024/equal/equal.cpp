#include "equal.h"
#include <bits/stdc++.h>

using namespace std;

void make_all_equal(int n, int Q_add, int Q_compare){
    int b=5;
    while(!compare(0,n-1)&&b>=0){
        vector<int> a(n/2);
        iota(a.begin(),a.end(),0);
        add(a,1<<b);
        b--;
    }
}