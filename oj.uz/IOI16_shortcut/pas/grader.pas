uses shortcut;

var
    n, c, i : longint;
    l, d : TIntArray;

begin
    read(n);
    read(c);
    setlength(l, n - 1);
    for i := 0 to n - 2 do 
        read(l[i]);
    setlength(d, n);
    for i := 0 to n - 1 do 
        read(d[i]);
        
        
    writeln(find_shortcut(n, l, d, c));
end.
