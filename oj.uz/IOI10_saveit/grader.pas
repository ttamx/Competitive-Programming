program grader;
   uses gradershare, encoder, decoder;
   var i,j: longint;
begin
   readln(nv,ne,c);
   for i:=0 to ne-1 do read(v1[i],v2[i]);
   for i:=0 to c-1 do for j:=0 to nv-1 do read(hh[i][j]);
   encode(nv,c,ne,v1,v2);
   decode(nv,c);
   if hcnt <> c*nv then begin
      halt(92);
   end;
   if nb <= 16000000 then writeln('OK 1 ') else writeln('NO 1');
   if nb <= 360000 then writeln('OK 2 ') else writeln('NO 2');
   if nb <= 80000 then writeln('OK 3 ') else writeln('NO 3');
   if nb <= 70000 then writeln('OK 4 ') else writeln('NO 4');
end.
