#
# Test: Passcode
#
int:$code;12145
int:$input;0
int:$puffer;0

print:Passcode!\n
print:Find the right number!\n

print:Your guess 
read:$input;int

set:$puffer;$input
div:$puffer;10000

if:$puffer;1;int
print:X\n
fi

set:$puffer;$input
div:$puffer;1000

if:$puffer;12;int
print:X\n
fi

set:$puffer;$input
div:$puffer;100

if:$puffer;121;int
print:X\n
fi

set:$puffer;$input
div:$puffer;10

if:$puffer;1214;int
print:X\n
fi

set:$puffer;$input
div:$puffer;1

if:$puffer;12145;int
print:X\n
fi

if:$input;$code;int
print:Success\n
fi
