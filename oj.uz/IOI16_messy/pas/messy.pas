unit messy;

interface

type
    TIntArray = array of longint;
    
function restore_permutation(n, w, r : longint) : TIntArray;

implementation

uses graderlib;

function restore_permutation(n, w, r : longint) : TIntArray;
var
    res : array of longint;
begin
  add_element('0');
  compile_set();
  check_element('0');
  setlength(res, 0);
  restore_permutation := res;
end;

end.

