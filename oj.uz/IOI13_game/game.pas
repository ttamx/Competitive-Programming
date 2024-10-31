unit game;

interface

procedure init(R, C : LongInt);
procedure update(P, Q : LongInt; K : Int64);
function calculate(P, Q, U, V : LongInt) : Int64;

implementation

function gcd2(X, Y : Int64) : Int64;
var
    tmp : Int64;
begin
    while (X <> Y) and (Y > 0) do begin
        tmp := X;
        X := Y;
        Y := tmp mod Y;
    end;
    gcd2 := X;
end;

procedure init(R, C : LongInt);
begin
    { ... }
end;

procedure update(P, Q : LongInt; K : Int64);
begin
    { ... }
end;

function calculate(P, Q, U, V : LongInt) : Int64;
begin
    { ... }
    calculate := 42;
end;

end.
