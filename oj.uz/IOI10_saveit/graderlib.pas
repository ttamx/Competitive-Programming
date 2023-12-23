unit graderlib;
interface
   procedure encode_bit(bit: longint);
   function decode_bit: longint;
   procedure hops(h,c,d: longint);
implementation
uses gradershare;
   procedure encode_bit(bit: longint);
   begin
      bits[nb] := bit;
      nb := nb + 1;
   end;
   function decode_bit: longint;
   begin
      if curbit >= nb then begin
         halt(92);
      end;
      decode_bit := bits[curbit];
      curbit := curbit + 1;
   end;
   procedure hops(h,c,d: longint);
   begin
      if hh[h][c] <> d then begin
         halt(92);
      end;
      hh[h][c] := -1;
      hcnt := hcnt + 1
   end;
begin
end.
