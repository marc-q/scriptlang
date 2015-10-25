#
# Test: Calculator
#
int:$a;0
int:$b;0
int:$form;0

print:Calculator\n

print:Addition 1, Substraction 2, Multiplication 3, Division 4\n
print:Type the what do you want to do 
read:$form;int

print:Type the first number 
read:$a;int
print:Type the last number 
read:$b;int

print:\n
printm:$a;int

if:$form;=;1;int
print: + 
add:$a;$b
fi
if:$form;=;2;int
print: - 
sub:$a;$b
fi
if:$form;=;3;int
print: * 
mpl:$a;$b
fi
if:$form;=;4;int
print: / 
div:$a;$b
fi

printm:$b;int
print: = 
printm:$a;intn
