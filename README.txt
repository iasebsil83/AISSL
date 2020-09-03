	AISSL : Artificial Intelligence - Simple Statistic Learning

AISSL is a basic learning software for all kind of numeric information.
It basically works using channels and symbols :

	- Symbols represent potential outputs/results
	- Channels are the numbers where inputs will be pushed

The mechanics between AISSL is quite simple :
	-> User create environment (symbols & channels)
	-> User pushes learning sequences into AISSL :
		"symbol s1 corresponds to channels values (c1_1, c1_2, ..., c1_n)"
		"symbol s2 corresponds to channels values (c2_1, c2_2, ..., c2_n)"
		...
	-> User asks AISSL which symbol corresponds the most to channels values :
		"ask (c1, c2, ..., cn)"
	-> AISSL answers for each channel which symbol is the most appropriate.
