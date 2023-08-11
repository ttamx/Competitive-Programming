unit seats;

interface

type
  array_of_longint = array of longint;
  
procedure give_initial_chart(H, W: longint; R, C: array_of_longint);
function swap_seats(a, b: longint): longint;
  
implementation

var
  Row: array of longint;

procedure give_initial_chart(H, W: longint; R, C: array_of_longint);
var
  i: longint;
begin
  setlength(Row, H * W);
  for i := 0 to H * W - 1 do begin
    Row[i] := R[i];
  end;
end;

function swap_seats(a, b: longint): longint;
begin
  exit(Row[a]);
end;

end.
