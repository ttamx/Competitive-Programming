unit encoder;
interface
   procedure encode(N,H,S: longint; A,B: array of longint);
implementation
   uses graderlib;
   procedure encode(N,H,S: longint; A,B: array of longint);
   begin
      encode_bit(1);
      encode_bit(0);
   end;
begin
end.
