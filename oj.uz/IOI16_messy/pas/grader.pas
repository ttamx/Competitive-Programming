uses messy, graderlib;

var
  n, w, r, i: longint;
  p: array of longint;
  answer: TIntArray;
  

begin
    read(n, w, r);
    setLength(p, n);
    for i := 0 to n - 1 do begin
        read(p[i]);
    end;
    init_grader(n, w, r, p);
    answer := restore_permutation(n, w, r);
    
    if length(answer) <> n then begin
        writeln('098d134608c94f7413faac591054ee35');
        writeln('WA');
        exit;
    end;


    write(answer[0]);
    for i := 1 to n - 1 do begin
        write(' ');
        write(answer[i]);
    end;
    writeln;
end.
