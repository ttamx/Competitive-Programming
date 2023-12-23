unit decoder;

interface

procedure decode(N : Longint; L : Longint; X : array of Longint);

implementation

uses decoderlib;

procedure decode(N : Longint; L : Longint; X : array of Longint);
var i : integer;
begin
  for i:=0 to L-1 do
    output(X[i]);
end;

end.

