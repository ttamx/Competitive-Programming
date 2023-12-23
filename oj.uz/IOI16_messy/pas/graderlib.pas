unit graderlib;

interface

procedure init_grader(n_, w_, r_: longint; p_: array of longint);
procedure add_element(x: string);
function check_element(x: string): boolean;
procedure compile_set();


implementation

type
  nodep = ^node;
  node = Record
    zero, one: ^node;
  end;

var
  n, w, r: longint;
  p: array of longint;
  initialized: boolean = false;
  compiled: boolean;
  nodeSet: nodep;


{ A convenience function. }
function get_p(i: longint): longint;
var
  ret: longint;
begin
  ret := p[i];
  get_p := ret;
end;

function create(): nodep;
var
  res: nodep;
begin
  res := new(nodep);
  res^.zero := NIL;
  res^.one := NIL;
  create := res;
end;

procedure wa();
begin
  writeln('WA');
  halt;
end;

procedure init_grader(n_, w_, r_: longint; p_: array of longint);
var
  i: longint;
begin
  if initialized then
     wa;
  n := n_;
  w := w_;
  r := r_;
  setLength(p, n);
  for i := 0 to n - 1 do
      p[i] := p_[i];
  initialized := true;
  nodeSet := create();
  compiled := false;
end;

function check(x: string): Boolean;
var
  i: longint;
  res: boolean;
begin
  res := true;
  if length(x) <> n then
    res := false
  else begin
    for i := 0 to n - 1 do
        if (x[i + 1] <> '0') and (x[i + 1] <> '1') then
           res := false;
  end;
  check := res;
end;

procedure addImpl(nodeSet: nodep; x: string; at: longint);
begin
  if at <> n then begin
    if x[at + 1] = '0' then begin
      if nodeSet^.zero = nil then
         nodeSet^.zero := create();
      addImpl(nodeSet^.zero, x, at + 1);
    end else begin
      if nodeSet^.one = nil then
         nodeSet^.one := create();
      addImpl(nodeSet^.one, x, at + 1);
    end;
  end;
end;

procedure add_element(x: string);
begin
  dec(w);
  if (w < 0) or compiled or (not check(x)) then
     wa;
  addImpl(nodeSet, x, 0);
end;

function check_element(x: string):boolean;
var
  res: Boolean;
  i: LongInt;
  cur: nodep;
begin
  dec(r);
  if (r < 0) or (not compiled) or (not check(x)) then
     wa;
  res := true;
  cur := nodeSet;
  for i := 0 to n - 1 do begin
    if x[i + 1] = '0' then begin
      if cur^.zero = nil then begin
        res := false;
        break;
      end;
      cur := cur^.zero;
    end else begin
      if cur^.one = nil then begin
        res := false;
        break;
      end;
      cur := cur^.one;
    end;
  end;
  check_element := res;
end;

procedure compile(nodeSet: nodep; at: longint; compiledSet: nodep; elem, compElem: string);
var
  i: longint;
begin
  if at = n then begin
    for i := 0 to n - 1 do
      compElem[i + 1] := elem[get_p(i) + 1];
    addImpl(compiledSet, compElem, 0);
    exit;
  end;
  if nodeSet^.zero <> nil then begin
    elem[at + 1] := '0';
    compile(nodeSet^.zero, at + 1, compiledSet, elem, compElem);
  end;
  if nodeSet^.one <> nil then begin
    elem[at + 1] := '1';
    compile(nodeSet^.one, at + 1, compiledSet, elem, compElem);
  end;
end;

procedure compile_set();
var
  compSet: nodep;
  elem, compElem: string;
begin
  if compiled then
     wa;
  compiled := true;
  setLength(elem, n);
  setLength(compElem, n);
  compSet := create();
  compile(nodeSet, 0, compSet, elem, compElem);
  nodeSet := compSet;
end;

end.
