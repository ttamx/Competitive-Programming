unit molecules;

interface

type 
    TIntArray = array of longint;

function find_subset(l, u: longint; w: TIntArray): TIntArray;

implementation

function find_subset(l, u: longint; w: TIntArray): TIntArray;
var
    res: TIntArray;
begin
    setLength(res, 0);
    find_subset := res;
end;

end.
