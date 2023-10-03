unit encoderlib;

interface

procedure send(a : Longint);

implementation

uses gradershare;

procedure send(a : Longint);
begin
  if elength = MAX_LENGTH then
  begin
    WriteLn('Encoded message too long.');
    Halt(0);
  end;
  encoded_message[elength] := a;
  elength := elength + 1;
end;

end.

