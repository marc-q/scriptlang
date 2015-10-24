# 
# String
# 
str:$testa;Variable testa.\n
str:$testb;Variable testb.\n
printm:$testa;str
printm:$testb;str
set:$testb;$testa
printm:$testb;str
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
