unit elephants;

interface

procedure init(N : LongInt;
	       L : LongInt;
	       var X : array of LongInt);

function update(i : LongInt;
		y : LongInt): LongInt;

implementation

var
  myN : LongInt;

procedure init(N : LongInt;
	       L : LongInt;
	       var X : array of LongInt);
begin
  myN := N;
end;

function update(i : LongInt;
		y : LongInt): LongInt;
begin
  update := myN;
end;

end.