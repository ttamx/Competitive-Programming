unit catdog;

interface

procedure initialize(N: longint; A, B: array of longint);
function cat(v: longint): longint;
function dog(v: longint): longint;
function neightbor(v: longint): longint;

implementation


var
  x: longint;

procedure initialize(N: longint; A, B: array of longint);
begin
  x := length(A);
end;

function cat(v: longint): longint;
begin
  exit(1)
end;

function dog(v: longint): longint;
begin
  exit(2);
end;

function neightbor(v: longint): longint;
begin
  exit(3);
end;


end.
