print:Starting read tests.\n
#
# Integer
#
int:$i;0

print:Type a number 
read:$i

print:\n
print:Your number was 
printm:$i;intn
#
# Float
#
float:$j;0.0

print:Type a number 
read:$j

print:\n
print:Your number was 
printm:$j;floatn
#
# String
#
str:$aname;

print:Type a name 
read:$aname

print:\n
print:The name was 
printm:$aname;strn
