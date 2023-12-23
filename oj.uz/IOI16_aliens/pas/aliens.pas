unit aliens;

interface

type
    TIntArray = array of longint;

function take_photos(n, m, k : longint; r, c : TIntArray) : Int64;

implementation

function take_photos(n, m, k : longint; r, c : TIntArray) : Int64;
begin
    take_photos := 0;   
end;

end.
