unit doll_lib;

interface

type
  array_of_longint = array of longint;

procedure answer(C, X, Y: array_of_longint);

implementation

uses sysutils, doll;

const
  P_MAX: longint = 20000000;
  S_MAX: longint = 400000;

var
  M, N: longint;
  A: array of longint;
  S: longint;
  IC, IX, IY: array of longint;

function read_longint(): longint;
var
  x: longint;
begin
  if eof() then begin
    writeln(stderr, 'Error while reading input');
    halt(1);
  end;
  {$I-}
  read(x);
  {$I+}
  if ioresult() <> 0 then begin
    writeln(stderr, 'Error while reading input');
    halt(1);
  end;
  exit(x);
end;

procedure wrong_answer(MSG: ansistring);
begin
  writeln('Wrong Answer: ', MSG);
  halt(0);
end;

procedure simulate();
var
  P, pos, i, j, k: longint;
  state: array of boolean;
  str: ansistring;
  file_log: text;
begin
  if S > S_MAX then begin
    writestr(str, 'over ', S_MAX, ' switches');
    wrong_answer(str);
  end;
  for i := 0 to M do begin
    if not ((-S <= IC[i]) and (IC[i] <= M)) then begin
      wrong_answer('wrong serial number');
    end;
  end;
  for j := 1 to S do begin
    if not ((-S <= IX[j - 1]) and (IX[j - 1] <= M)) then begin
      wrong_answer('wrong serial number');
    end;
    if not ((-S <= IY[j - 1]) and (IY[j - 1] <= M)) then begin
      wrong_answer('wrong serial number');
    end;
  end;

  P := 0;
  setlength(state, S + 1);
  for j := 0 to S do begin
    state[j] := false;
  end;
  pos := IC[0];
  k := 0;
  assign(file_log, 'log.txt');
  rewrite(file_log);
  writeln(file_log, 0);
  while true do begin
    writeln(file_log, pos);
    if pos < 0 then begin
      P := P + 1;
      if P > P_MAX then begin
        close(file_log);
        writestr(str, 'over ', P_MAX, ' inversions');
        wrong_answer(str);
      end;
      state[-pos] := not state[-pos];
      if state[-pos] then begin
        pos := IX[-(1 + pos)];
      end else begin
        pos := IY[-(1 + pos)];
      end;
    end else begin
      if pos = 0 then begin
        break;
      end;
      if k >= N then begin
        close(file_log);
        wrong_answer('wrong motion');
      end;
      if pos <> A[k] then begin
        close(file_log);
        wrong_answer('wrong motion');
      end;
      k := k + 1;
      pos := IC[pos];
    end;
  end;
  close(file_log);
  if k <> N then begin
    wrong_answer('wrong motion');
  end;
  for j := 1 to S do begin
    if state[j] then begin
      wrong_answer('state ''Y''');
    end;
  end;
  writeln('Accepted: ', S, ' ', P);
end;

var
	answered: boolean;

procedure answer(C, X, Y: array_of_longint);
var
  i, j: longint;
begin
  if answered then begin
    wrong_answer('answered not exactly once');
  end;
  answered := true;
  if length(C) <> M + 1 then begin
    wrong_answer('wrong array length');
  end;
  if length(X) <> length(Y) then begin
    wrong_answer('wrong array length');
  end;
  S := length(X);
  setlength(IC, M + 1);
  setlength(IX, S);
  setlength(IY, S);
  for i := 0 to M do begin
    IC[i] := C[low(C) + i];
  end;
  for j := 1 to S do begin
    IX[j - 1] := X[low(X) + (j - 1)];
    IY[j - 1] := Y[low(Y) + (j - 1)];
  end;
end;


var
  i, j, k: longint;
  file_out: text;
begin
  M := read_longint();
  N := read_longint();
  setlength(A, N);
  for k := 0 to N - 1 do begin
    A[k] := read_longint();
  end;

  answered := false;
  create_circuit(M, A);
  if not answered then begin
    wrong_answer('answered not exactly once');
  end;
  assign(file_out, 'out.txt');
  rewrite(file_out);
  writeln(file_out, S);
  for i := 0 to M do begin
    writeln(file_out, IC[i]);
  end;
  for j := 1 to S do begin
    writeln(file_out, IX[j - 1], ' ', IY[j - 1]);
  end;
  close(file_out);
  simulate();
end.
