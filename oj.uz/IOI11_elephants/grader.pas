program Grader;

uses elephants;

const
  MAX_N = 1000000;
  MAX_M = 1000000;

var
  N, L, M : LongInt;
  X : array [0..MAX_N] of LongInt;
  ii,yy,sol : array [0..MAX_M] of LongInt;

procedure ReadInput;
var i : LongInt;
begin
  ReadLn(N,L,M);
  for i:=0 to N-1 do
    ReadLn(X[i]);
  for i:=0 to M-1 do
    ReadLn(ii[i],yy[i],sol[i]);
end;

var i,ans : LongInt;
begin
  ReadInput;
  init(N,L,X);
  for i:=0 to M-1 do
  begin
    ans := update(ii[i],yy[i]);
    if ans <> sol[i] then
    begin
      WriteLn('Incorrect. In the ',i+1,'-th move, answered ',
	      ans,' (',sol[i],' expected).');
      Halt(0);
    end;
  end;
  WriteLn('Correct.');
end.

