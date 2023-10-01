program Grader;

uses crocodilelib, crocodile;

var
  N, M, K : LongInt;
  R : RArray;
  L : LArray;
  P : PArray;
  solution : LongInt;
  
procedure ReadInput;
var i : LongInt;
begin
  ReadLn(N,M,K);
  for i:=0 to M-1 do
    ReadLn(R[i][0], R[i][1], L[i]);
  for i:=0 to K-1 do
    Read(P[i]);
  ReadLn;
  ReadLn(solution);
end; 

var ans : LongInt;
begin
  ReadInput;
  ans := travel_plan(N,M,R,L,K,P);
  if ans = solution then
    WriteLn('Correct.')
  else
    WriteLn('Incorrect. Returned ',ans,'. Expected ',solution,'.');
end.
