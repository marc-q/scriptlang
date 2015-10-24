#
# Test: Calculator
#
int:$a;0
int:$b;0
int:$form;0
print:Calculator\n
print:Addition 1, Substration 2, Multiplication 3, Division 4\n
print:Type the what do you want to do 
read:$form;int
print:Type the first number 
read:$a;int
print:Type the last number 
read:$b;int
print:\n
printm:$a;int
if:$form;1;int
print: + 
fi
if:$form;2;int
print: - 
fi
if:$form;3;int
print: * 
fi
if:$form;4;int
print: / 
fi
printm:$b;int
print: = 
if:$form;1;int
add:$a;$b
fi
if:$form;2;int
sub:$a;$b
fi
if:$form;3;int
mpl:$a;$b
fi
if:$form;4;int
div:$a;$b
fi
printm:$a;intn
