uses paint, CTypes;

var
    s : ansistring;
    c_len, i : longint;
    c : TIntArray;
    ans : ansistring;
begin
    readln(s);
    read(c_len);
    setlength(c, c_len);
    for i := 0 to c_len - 1 do 
        read(c[i]);
    ans := solve_puzzle(s, c);
    
    
    writeln(ans);
end.
