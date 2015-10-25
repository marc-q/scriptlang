#
# Test: Passcode
#
int:$code;12145
int:$input;0
int:$puffer;0
int:$puffer2;0
int:$divisor;0

# Function: checkdigits
def:checkdigit;void

set:$puffer;$input
div:$puffer;$divisor

set:$puffer2;$code
div:$puffer2;$divisor

if:$puffer;=;$puffer2;int
print:X 
else
print:O 
fi
fed

print:Passcode!\n
print:Find the right number!\n

print:Your guess 
read:$input;int

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
if:$input;=;$code;int
print:Success\n
fi
