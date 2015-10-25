#
# Test: Calculator
#
float:$a;0.0
float:$b;0.0
int:$form;0

print:Calculator\n

print:Addition 1, Substraction 2, Multiplication 3, Division 4\n
print:Type what do you want to do 
read:$form;int

print:Type the first number 
read:$a;float
print:Type the last number 
read:$b;float

print:\n
printm:$a;float

if:$form;=;1
print: + 
add:$a;$b
fi
if:$form;=;2
print: - 
sub:$a;$b
fi
if:$form;=;3
print: * 
mpl:$a;$b
fi
if:$form;=;4
print: / 
div:$a;$b
fi

printm:$b;float
print: = 
printm:$a;floatn
