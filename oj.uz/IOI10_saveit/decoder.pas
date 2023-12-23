unit decoder;
interface
   procedure decode(N,H:longint);
implementation
   uses graderlib;
   procedure decode(N,H:longint);
      var x,y: longint;
   begin
      x := decode_bit;
      y := decode_bit;
      hops(0,0,0);
      hops(0,1,1);
   end;
begin
end.
