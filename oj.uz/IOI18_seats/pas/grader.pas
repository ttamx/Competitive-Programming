program grader;

uses seats;

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
  H, W, Q, i, j, answer: longint;
  R, C, A, B: array of longint;
begin
  H := read_longint();
  W := read_longint();
  Q := read_longint();
  setlength(R, H * W);
  setlength(C, H * W);
  for i := 0 to H * W - 1 do begin
    R[i] := read_longint();
    C[i] := read_longint();
  end;
  setlength(A, Q);
  setlength(B, Q);
  for j := 0 to Q - 1 do begin
    A[j] := read_longint();
    B[j] := read_longint();
  end;

  give_initial_chart(H, W, R, C);
  for j := 0 to Q - 1 do begin
    answer := swap_seats(A[j], B[j]);
    writeln(answer);
  end;
end.
