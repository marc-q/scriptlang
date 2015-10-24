# 
# String
# 
str:$testa;Variable testa.
str:$testb;Variable testb.
printm:$testa;str
printm:$testb;str
set:$testb;$testa
printm:$testb;str
# 
# Integer
# 
int:$i;100
int:$j;20
printm:$i;int
printm:$j;int
set:$i;50
printm:$i;int
set:$i;$j
printm:$i;int
