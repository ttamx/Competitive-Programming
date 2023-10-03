unit doll;

interface

type
  array_of_longint = array of longint;

procedure create_circuit(M: longint; A: array_of_longint);

implementation

uses doll_lib;

procedure create_circuit(M: longint; A: array_of_longint);
var
  N, i, k: longint;
  C, X, Y: array of longint;
begin
  N := length(A);
  setlength(C, M + 1);
  C[0] := -1;
  for i := 1 to M do begin
    C[i] := 1;
  end;
  setlength(X, N);
  setlength(Y, N);
  for k := 0 to N - 1 do begin
    X[k] := A[k];
    Y[k] := A[k];
  end;
  answer(C, X, Y);
end;

end.
