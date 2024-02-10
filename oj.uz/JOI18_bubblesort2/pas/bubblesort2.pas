unit bubblesort2;

interface

type
  ArrayOfLongint = array of longint;

function countScans(A, X, V: ArrayOfLongint): ArrayOfLongint;

implementation


function countScans(A, X, V: ArrayOfLongint): ArrayOfLongint;
var
  Q, j: longint;
  answer: array of longint;
begin
  Q := length(X);
  setlength(answer, Q);
  for j := 0 to Q - 1 do begin
    answer[j] := X[j];
  end;
  exit(answer);
end;


end.
