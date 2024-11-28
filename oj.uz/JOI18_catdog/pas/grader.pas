program grader;

uses catdog;

function readLongint(): longint;
begin
  if eof then begin
    writeln(stderr, 'Error while reading input.');
    halt(1);
  end;
  {$I-}
  read(readLongint);
  {$I+}
  if ioresult <> 0 then begin
    writeln(stderr, 'Error while reading input.');
    halt(1);
  end;
end;

var
  N: longint;
  A, B: array of longint;
  Q: longint;
  T, v: array of longint;
  i, j: longint;
begin
  N := readLongint();
  setlength(A, N - 1);
  setlength(B, N - 1);
  for i := 0 to N - 2 do begin
    A[i] := readLongint();
    B[i] := readLongint();
  end;
  Q := readLongint();
  setlength(T, Q);
  setlength(v, Q);
  for j := 0 to Q - 1 do begin
    T[j] := readLongint();
    v[j] := readLongint();
  end;
  initialize(N, A, B);
  for j := 0 to Q - 1 do begin
    case T[j] of
      1: writeln(cat(v[j]));
      2: writeln(dog(v[j]));
      3: writeln(neightbor(v[j]));
      else begin
        writeln(stderr, 'Error while reading input.');
        halt(1);
      end;
    end;
  end;
end.
