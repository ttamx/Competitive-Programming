unit werewolf;

interface

type
  array_of_longint = array of longint;

function check_validity(N: longint; X, Y, S, E, L, R: array_of_longint)
    : array_of_longint;

implementation

function check_validity(N: longint; X, Y, S, E, L, R: array_of_longint)
    : array_of_longint;
var
  Q, i: longint;
  A: array of longint;
begin
  Q := length(S);
  setlength(A, Q);
  for i := 0 to Q - 1 do begin
    A[i] := 0;
  end;
  exit(A);
end;

end.
