print:Starting if tests.\n
int:$i;2015
str:$a;This is a Test
if:$i;=;2015;int
print:i is 2015\n
else
print:i is not 2015\n
fi
if:$i;>;2000;int
print:i is > than 2000\n
fi
if:$a;=;This is a Test;str
print:Success\n
fi
if:$a;=;ThisisaTest;str
print:Fail\n
else
print:Success\n
fi
print:Test complete.\n
