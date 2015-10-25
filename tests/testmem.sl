# 
# String
# 
str:$testa;Variable testa.
str:$testb;Variable testb.
printm:$testa;strn
printm:$testb;strn
set:$testb;$testa
printm:$testb;strn
set:$testa;Variable.
printm:$testa;strn
# 
# Integer
# 
int:$i;100
int:$j;20
printm:$i;intn
printm:$j;intn
set:$i;50
printm:$i;intn
set:$i;$j
printm:$i;intn
# 
# Cpy
# 
print:Should be an error\n
set:$i;$testa
