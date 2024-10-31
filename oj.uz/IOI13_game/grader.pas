program grader;

uses game;

procedure fail(s: string);
begin
    writeln(stderr, s);
    halt(1);
end;

var
    R, C, N : longint;
    P, Q, U, V : longint;
    K : int64;
    i, action : longint;
    f: text;
    answer: longint;

begin
    assign(f, 'game.in');
    {$I-} reset(f); {$I+}
    if IOResult <> 0 then
        fail('Failed to open input file.');

    readln(f, R, C, N);

    init(R, C);

    for i := 0 to N-1 do begin
        read(f, action);
        if action = 1 then begin
            readln(f, P, Q, K);
            update(P, Q, K);
        end else if action = 2 then begin
            readln(f, P, Q, U, V);
            writeln(calculate(P, Q, U, V));
        end else
            fail('Invalid action type in input file.');
    end;
    close(f);
end.
