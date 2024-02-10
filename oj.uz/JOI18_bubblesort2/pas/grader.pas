program grader;

uses bubblesort2;

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
  N, Q: longint;
  A, X, V: array of longint;
  answer: array of longint;
  i, j: longint;
begin
  N := readLongint();
  Q := readLongint();
  setlength(A, N);
  for i := 0 to N - 1 do begin
    A[i] := readLongint();
  end;
  setlength(X, Q);
  setlength(V, Q);
  for j := 0 to Q - 1 do begin
    X[j] := readLongint();
    V[j] := readLongint();
  end;
  answer := countScans(A, X, V);
  for j := low(answer) to high(answer) do begin
    writeln(answer[j]);
  end;
end.
