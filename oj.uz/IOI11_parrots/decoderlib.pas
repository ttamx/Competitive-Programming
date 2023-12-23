unit decoderlib;

interface

procedure output(b : Longint);

implementation

uses gradershare;

procedure output(b : Longint);
begin
  if olength >= MAX_LENGTH then
  begin
    WriteLn('Output message too large.');
    Halt(0);
  end;
  output_message[olength] := b;
  olength := olength + 1;
end;

end.

