program Grader;

uses ricehub;

const
  MAX_R = 100000;
  
var
  R, L : Longint;
  B : Int64;
  X : Array [0..100000] of Longint;
  Solution : Longint;
  
procedure ReadInput;
var i : Longint;
begin
  ReadLn(R,L,B);
  for i:=0 to R-1 do
    ReadLn(X[i]);
  ReadLn(Solution);
end;

var
  ans : Longint;
begin
  ReadInput;
  ans := besthub(R,L,X,B);
  if ans = Solution then
    WriteLn('Correct.')
  else
    WriteLn('Incorrect.  Answered ', ans, ' instead of ', Solution, '.');
end.
