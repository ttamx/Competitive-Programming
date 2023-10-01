program Grader;

uses racelib, race;

var
  N,K : LongInt;
  H : HArray;
  L : LArray;
  solution : LongInt;
  
procedure ReadInput;
var i : LongInt;
begin
  ReadLn(N,K);
  for i:=0 to N-2 do
    ReadLn(H[i][0],H[i][1],L[i]);
  ReadLn(solution);
end;

var ans : LongInt;
begin
  ReadInput;
  ans := best_path(N,K,H,L);
  if ans=solution then
    WriteLn('Correct.')
  else
    WriteLn('Incorrect. Returned ',ans,'. Expected ',solution,'.');
end.
