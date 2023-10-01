unit highway_lib;

interface

type
  array_of_longint = array of longint;

function ask(w: array_of_longint): int64;
procedure answer(s_, t_: longint);

implementation

uses highway;

const
  MAX_NUM_CALLS: longint = 100;
  INF: int64 = 1 << 61;

var
  N, M, A, B, S, T: longint;
  U, V: array of longint;
  graph_adj, graph_ei: array of array of longint;
  answered, wrong_pair: boolean;
  num_calls: longint;

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

function ask(w: array_of_longint): int64;
var
  visited: array of boolean;
  current_dist: array of int64;
  qa, qb: array of longint;
  qa_top, qa_end, qb_top, qb_end: longint;
  i, j, p, pp, ei: longint;
  d: int64;
begin
  num_calls += 1;
  if num_calls > MAX_NUM_CALLS then begin
    wrong_answer('more than 100 calls to ask');
  end;
  if length(W) <> M then begin
    wrong_answer('w is invalid');
  end;
  for i := 0 to M - 1 do begin
    if not ((w[i] = 0) or (w[i] = 1)) then begin
      wrong_answer('w is invalid');
    end;
  end;

  setlength(visited, N);
  setlength(current_dist, N);
  setlength(qa, M + 2);
  setlength(qb, M + 2);
  qa_top := 0;
  qa_end := 0;
  qb_top := 0;
  qb_end := 0;
  for p := 0 to N - 1 do begin
    visited[p] := false;
    current_dist[p] := INF;
  end;
  qa[qa_end] := S;
  qa_end := qa_end + 1;
  current_dist[S] := 0;
  while (qa_top <> qa_end) or (qb_top <> qb_end) do begin
    if (qb_top = qb_end) or
        ((qa_top <> qa_end) and (current_dist[qa[qa_top]] <= current_dist[qb[qb_top]])) then begin
      p := qa[qa_top];
      qa_top := qa_top + 1;
    end else begin
      p := qb[qb_top];
      qb_top := qb_top + 1;
    end;
    if visited[p] then begin
      continue;
    end;
    visited[p] := true;
    d := current_dist[p];
    if p = T then begin
      exit(d);
    end;
    for j := 0 to length(graph_adj[p]) - 1 do begin
      pp := graph_adj[p][j];
      ei := graph_ei[p][j];
      if not visited[pp] then begin
        if w[ei] = 0 then begin
          if current_dist[pp] > d + A then begin
            current_dist[pp] := d + A;
            qa[qa_end] := pp;
            qa_end := qa_end + 1;
          end;
        end else begin
          if current_dist[pp] > d + B then begin
            current_dist[pp] := d + B;
            qb[qb_end] := pp;
            qb_end := qb_end + 1;
          end;
        end;
      end;
    end;
  end;
  exit(-1);
end;

procedure answer(s_, t_: longint);
begin
  if answered then begin
    wrong_answer('answered not exactly once');
  end;
  answered := true;
  if not (((s_ = S) and (t_ = T)) or ((s_ = T) and (t_ = S))) then begin
    wrong_pair := true;
  end;
end;

var
  i, p: longint;
  degree: array of longint;
begin
  N := read_longint();
  M := read_longint();
  A := read_longint();
  B := read_longint();
  S := read_longint();
  T := read_longint();
  setlength(U, M);
  setlength(V, M);
  for i := 0 to M - 1 do begin
    U[i] := read_longint();
    V[i] := read_longint();
  end;
  setlength(degree, N);
  for p := 0 to N - 1 do begin
    degree[p] := 0;
  end;
  for i := 0 to M - 1 do begin
    degree[U[i]] += 1;
    degree[V[i]] += 1;
  end;
  setlength(graph_adj, N);
  setlength(graph_ei, N);
  for p := 0 to N - 1 do begin
    setlength(graph_adj[p], degree[p]);
    setlength(graph_ei[p], degree[p]);
  end;
  for i := 0 to M - 1 do begin
    degree[U[i]] -= 1;
    graph_adj[U[i]][degree[U[i]]] := V[i];
    graph_ei[U[i]][degree[U[i]]] := i;
    degree[V[i]] -= 1;
    graph_adj[V[i]][degree[V[i]]] := U[i];
    graph_ei[V[i]][degree[V[i]]] := i;
  end;

  answered := false;
  wrong_pair := false;
  num_calls := 0;
  find_pair(N, U, V, A, B);
  if not answered then begin
    wrong_answer('answered not exactly once');
  end;
  if wrong_pair then begin
    wrong_answer('{s, t} is wrong');
  end;
  writeln('Accepted: ', num_calls);
end.
