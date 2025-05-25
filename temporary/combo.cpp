#include <bits/stdc++.h>
#include "combo.h"

using namespace std;

string guess_sequence( int N )
{
    string s = "";
    string a = "ABXY";
    vector<char> bt;
    if( press("A") ) s += "A";
    else if( press("B") ) s += "B";
    else if( press("X") ) s += "X";
    else s += "Y";
    if( N == 1 ) return s;
    for( auto c : a ) if( s[0] != c ) bt.push_back( c );
    for( int i=1;i<N-1;i++ )
    {
        string tp = s+bt[0] + s+bt[1]+bt[0] + s+bt[1]+bt[1] + s+bt[1]+bt[2];
        int sz = s.size();
        int res = press(tp);
        if( res == sz+1 ) s += bt[0];
        else if( res == sz+2 ) s += bt[1];
        else s += bt[2];
    }
    // (i + 1) + (i + 2) * 3 = 4 * i + 7
    // 4 * (n - 2) + 7 = 4 * n - 1
    if( press(s+bt[0]) == N ) s += bt[0];
    else if( press(s+bt[1]) == N ) s += bt[1];
    else s += bt[2];
    return s;
}

/*
PRESS : A
PRESS : ABAXBAXXAXY
PRESS : ABAXBAXXAXY
PRESS : AYBAYXBAYXXAYXY
PRESS : AYBAYXBAYXXAYXY
PRESS : AYYBAYYXBAYYXXAYYXY
PRESS : AYYBAYYXBAYYXXAYYXY
PRESS : AYYYBAYYYXBAYYYXXAYYYXY

*/