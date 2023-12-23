unit meetings;

interface

type
  array_of_longint = array of longint;
  array_of_int64 = array of int64;

function minimum_costs(H, L, R: array_of_longint): array_of_int64;

implementation

function minimum_costs(H, L, R: array_of_longint): array_of_int64;
var
  Q, j: longint;
  C: array of int64;
begin
  Q := length(L);
  setlength(C, Q);
  for j := 0 to Q - 1 do begin
    C[j] := H[L[j]];
  end;
  exit(C);
end;

end.
