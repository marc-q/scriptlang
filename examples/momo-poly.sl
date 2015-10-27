#
# Momo-poly: Copyright 2015 Marc Volker Dickmann
#
# Variables
int:$exitnow;0
int:$cache;0
int:$cache2;0
int:$round;0
int:$cubes;0
int:$whois;0

# DEBUGVALUES
# 99999999999 - Own all houses

# Player
int:$m_player;10000
int:$f_player;0
int:$o_player;0

# KI
int:$m_ki;10000
int:$f_ki;0
int:$o_ki;0

# Prints a new line
def:nl
	print:\n
fed

# Checks if its even / Who is playing
def:who
	set:$whois;$round
	mod:$whois;2
fed

# Cubes
def:cube
	rand:$cubes
	mod:$cubes;12
	add:$cubes;1

	if:$whois;=;0
		print:You cubed 
	else
		print:KI cubed 
	fi

	printm:$cubes;intn
fed

# Builds the house
def:buildhouse
	set:$cache;1
	nl:;
	
	if:$whois;=;0
		getbit:$o_player;$f_player;$cache;0
		print:You 
	else
		getbit:$o_ki;$f_ki;$cache;0
		print:KI 
	fi
	
	print: builded a house.\n
fed

# Pay the bills of buying a house
def:payhouse
	print:Pay the bills (200$).\n
	
	if:$whois;=;0
		$sub:$m_player;200
	else
		$sub:$m_ki;200
	fi
fed

# Pay the bills of getting onto a companion field
def:paybills
	print:Pay the bills (200$).\n
	
	if:$whois;=;0
		$sub:$m_player;200
		$add:$m_ki;200
	else
		$sub:$m_ki;200
		$add:$m_player;200
	fi
fed

# Asks what to do when hitting a field
def:buildmenu
	print:Build a house (1), no house (2)\n
	print:What do you wanna do 
	read:$cache
	
	if:$cache;=;1
		buildhouse:;
		payhouse:;
	fi
fed
		

# Checks if the field can be bought
def:checkfield
	set:$cache;0
	if:$whois;=;0
		getbit:$cache;0;$o_ki;$f_player
	else
		getbit:$cache;0;$o_player;$f_ki
	fi
	
	# TODO: Fix this!
	# NOTE: This should be checking if the player already owns the house.
	#if:$cache;=;0
	#	if:$whois;=;0
	#		getbit:$cache;0;$o_player;$f_player
	#	else
	#		getbit:$cache;0;$o_ki;$f_ki
	#	fi
	#fi
	
	# TODO: Needs to be fixed!
	# NOTE: Should be fixed!
	if:$cache;=;0
		print:Field can be bought\n
		buildmenu:;
	else
		print:Field cant be bought\n
		nl:;
		paybills:;
	fi
fed

# Do a round
def:do_round
	add:$round;1
	who:;

	nl:;
	cube:;
	
	# Add the cubes to the field first
	if:$whois;=;0
		add:$f_player;$cubes
	else
		add:$f_ki;$cubes
	fi
	
	# Check if the player has lost due to bankcrupcy
	if:$m_player;<;1
		print:KI WIN!\n
	fi
	# Field 24 = field before field start 
	if:$f_player;>;23
		# Gone over the start field: +200$
		add:$m_player;200
		sub:$f_player;24
	fi
	
	if:$m_ki;<;1
		print:You WIN!\n
	fi
	if:$f_ki;>;23
		# Gone over the start field: +200$
		add:$m_ki;200
		sub:$f_ki;24
	fi
	
	print:Money 
	if:$whois;=;0
		printm:$m_player;int
		print:$.\n
		print:Your on field 
		printm:$f_player;intn
	else
		printm:$m_ki;int
		print:$.\n
		print:KI is on field 
		printm:$f_ki;intn
	fi

	checkfield:;
fed

# Asks if the player wants to quit
def:askexit
	print:Exit (y=0|N=1)? 
	read:$cache
	
	if:$cache;=;0
		set:$exitnow;1
	fi
fed

# The main gameloop
def:gameloop
	for:$exitnow;=;0
		do_round:;
		askexit:;
	rof
fed

# Prints the logo in ascii art
def:printintro
	print: __    __   ____   __    __   ____         ____   ____       _    _\n
	print:||\\  //|| ||  || ||\\  //|| ||  ||  ___  ||  || ||  || ||   \\  //\n
	print:|| \\// || ||  || || \\// || ||  || |___| ||__|| ||  || ||     ||\n
	print:||      || ||__|| ||      || ||__||       ||     ||__|| ||__   ||\n
fed

# The main function
def:main
	print:Monopoly (C) 2015 Marc Volker Dickmann\n
	nl:;
	printintro:;
	nl:;
	nl:;

	gameloop:;
fed

# Calling the main function
main:;
