unit encoder;

interface

procedure encode(N : Longint; M : array of Longint);

implementation

uses encoderlib;

procedure encode(N : Longint; M : array of Longint);
var i : Longint;
begin
  for i:=0 to N-1 do
    send(M[i]);
end;

end.

