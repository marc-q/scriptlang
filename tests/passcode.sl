#
# Test: Passcode
#
int:$code;12145
int:$input;0
int:$puffer;0
int:$puffer2;0
int:$divisor;0

# Function: checkdigit
def:checkdigit

set:$puffer;$input
div:$puffer;$divisor

set:$puffer2;$code
div:$puffer2;$divisor

if:$puffer;=;$puffer2
print:X 
else
print:O 
fi
fed

print:Passcode!\n
print:Find the right number!\n

print:Your guess 
read:$input

set:$divisor;10000
checkdigit:;

set:$divisor;1000
checkdigit:;

set:$divisor;100
checkdigit:;

set:$divisor;10
checkdigit:;

set:$divisor;1
checkdigit:;

print:\n
if:$input;=;$code
print:Success\n
fi
