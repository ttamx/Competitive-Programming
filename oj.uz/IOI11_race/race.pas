unit race;

interface

uses racelib;

function best_path(N : LongInt;
                   K : LongInt;
                   var H : HArray;
                   var L : LArray) : LongInt;
implementation

function best_path(N : LongInt;
                   K : LongInt;
                   var H : HArray;
                   var L : LArray) : LongInt;
begin
	best_path := N;
end; 

end.
