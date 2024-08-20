unit shortcut;

interface

type
    TIntArray = array of longint;

function find_shortcut(n : longint; l, d: TIntArray; c : longint) : int64;

implementation

function find_shortcut(n : longint; l, d: TIntArray; c : longint) : int64;
begin
    find_shortcut := 0;
end;

end.
