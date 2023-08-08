uses molecules;

var
    n, l, u, i: longint;
    w, res: TIntArray;

begin
    read(n, l, u);
    setlength(w, n);
    for i := 0 to n - 1 do begin
        read(w[i]);     
    end;

    res := molecules.find_subset(l, u, w);


    writeln(length(res));
    for i := 0 to length(res) - 1 do begin
        write(res[i]); 
        if i + 1 = length(res) then
            writeln
        else
            write(' ')
    end;    
end.
