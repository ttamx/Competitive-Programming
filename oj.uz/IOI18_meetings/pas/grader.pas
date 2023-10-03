program grader;

uses meetings;

function read_longint(): longint;
var
  x: longint;
begin
  if eof() then begin
    writeln(stderr, 'Error while reading input');
    halt(1);
  end;
  {$I-}
  read(x);
  {$I+}
  if ioresult() <> 0 then begin
    writeln(stderr, 'Error while reading input');
    halt(1);
  end;
  exit(x);
end;

var
  N, Q: longint;
  H, L, R: array of longint;
  C: array of int64;
  i, j: longint;
begin
  N := read_longint();
  Q := read_longint();
  setlength(H, N);
  for i := 0 to N - 1 do begin
    H[i] := read_longint();
  end;
  setlength(L, Q);
  setlength(R, Q);
  for j := 0 to Q - 1 do begin
    L[j] := read_longint();
    R[j] := read_longint();
  end;
  C := minimum_costs(H, L, R);
  for j := low(C) to high(C) do begin
    writeln(C[j]);
  end;
end.
