unit crocodile;

interface

uses crocodilelib;

function travel_plan(N,M : LongInt;
		     var R : RArray;
		     var L : LArray;
   		     K : LongInt;
		     var P : PArray): LongInt;

implementation

function travel_plan(N,M : LongInt;
		     var R : RArray;
		     var L : LArray;
   		     K : LongInt;
		     var P : PArray): LongInt;
begin
  travel_plan := N;
end;

end.

		     