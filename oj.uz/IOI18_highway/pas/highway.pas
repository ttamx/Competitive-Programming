unit highway;

interface

type
  array_of_longint = array of longint;

procedure find_pair(N: longint; U, V: array_of_longint; A, B: longint);

implementation

uses highway_lib;

procedure find_pair(N: longint; U, V: array_of_longint; A, B: longint);
var
  M, i, j: longint;
  w: array of longint;
  toll: int64;
begin
  M := length(U);
  setlength(w, M);
  for j := 0 to 49 do begin
    for i := 0 to M - 1 do begin
      w[i] := 0;
    end;
    toll := ask(w);
  end;
  answer(0, N - 1);
end;

end.
