uses aliens;

var
    n, m, k, i : longint;
    r, c : TIntArray;
    ans : int64;
begin
    read(n, m, k);
    setlength(r, n);
    setlength(c, n);
    for i := 0 to n - 1 do
        read(r[i], c[i]);
    ans := take_photos(n, m, k, r, c);
    
        
    writeln(ans);
end.
