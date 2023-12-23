program grader;

uses encoder, decoder, gradershare;

const
  MAX_EXPANSION = 10;
  CHANNEL_RANGE = 65535;
  
var
  N : LongInt;
  i : LongInt;
  t : LongInt;
  message : array [0..100] of Longint;
  correct : Boolean;
  
procedure Shuffle;
var i,t : longint;
begin
  i := 0;
  while i < elength-1 do
  begin
    t := encoded_message[i];
    encoded_message[i] := encoded_message[i+1];
    encoded_message[i+1] := t;
    i := i + 2;
  end;
end;

procedure CheckEncodedMessage;
begin
  if elength > MAX_EXPANSION * N then
  begin
    WriteLn('Encoded message too long.');
    Halt(0);
  end;
  for i:=0 to elength-1 do
    if (encoded_message[i] < 0) or
      (encoded_message[i] > CHANNEL_RANGE) then
    begin
      WriteLn('Bad encoded integer.');
      Halt(0);
    end;
end;

function CheckOutput: Boolean;
begin
  if olength<>N then
    Exit(false)
  else
    for i:=0 to N-1 do
      if output_message[i]<>message[i] then
	Exit(false);
  CheckOutput := true;
end;

var
  ratio : Real;

begin
  ReadLn(N);
  for i:=0 to N-1 do
    Read(message[i]);
  ReadLn;

  ratio := 0;
  
  for t := 1 to 2 do
  begin
    elength := 0;
    encode(N, message);
    CheckEncodedMessage;

    if elength / N > ratio then
      ratio := elength / N;

    if t = 2 then
      Shuffle;
    ereadlength := 0;
    olength := 0;
    decode(N, elength, encoded_message);
    if not CheckOutput then
    begin
      WriteLn('Incorrect.');
      Halt(0);
    end;
  end;
  WriteLn('Correct.');
  WriteLn(StdErr,'Ratio = ',ratio:5:3);
end.

