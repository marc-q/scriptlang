# 
# Integer
# 
int:$a;100
int:$b;20

printm:$a;intn
printm:$b;intn

set:$a;50
printm:$a;intn

set:$a;$b
printm:$a;intn
print:\n

# 
# Float
# 
float:$c;100.121
float:$d;20.121

printm:$c;floatn
printm:$d;floatn

set:$c;50.121
printm:$d;floatn

set:$c;$d
printm:$c;floatn
print:\n

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
print:\n

# 
# Set
# 
print:Should be 6 errors\n

print:\n
set:$a;$c
set:$a;$testa

print:\n
set:$c;$a
set:$c;$testa

print:\n
set:$testa;$a
set:$testa;$c

print:\n
print:Tests complete\n
