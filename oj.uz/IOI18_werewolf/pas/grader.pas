program grader;

uses werewolf;

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
  N, M, Q, i, j: longint;
  X, Y, S, E, L, R, A: array of longint;

begin
  N := read_longint();
  M := read_longint();
  Q := read_longint();
  setlength(X, M);
  setlength(Y, M);
  setlength(S, Q);
  setlength(E, Q);
  setlength(L, Q);
  setlength(R, Q);
  for j := 0 to M - 1 do begin
    X[j] := read_longint();
    Y[j] := read_longint();
  end;
  for i := 0 to Q - 1 do begin
    S[i] := read_longint();
    E[i] := read_longint();
    L[i] := read_longint();
    R[i] := read_longint();
  end;
  A := check_validity(N, X, Y, S, E, L, R);
  for i := low(A) to high(A) do begin
    writeln(A[i]);
  end;
end.
