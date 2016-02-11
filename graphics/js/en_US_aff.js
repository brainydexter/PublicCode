var aff_text='SET ISO8859-1\n' +
"TRY esianrtolcdugmphbyfvkwzESIANRTOLCDUGMPHBYFVKWZ'\n" +
'NOSUGGEST !\n' +

'# ordinal numbers\n' +
'COMPOUNDMIN 1\n' +
'# only in compounds: 1th, 2th, 3th\n' +
'ONLYINCOMPOUND c\n' +
'# compound rules:\n' +
'# 1. [0-9]*1[0-9]th (10th, 11th, 12th, 56714th, etc.)\n' +
'# 2. [0-9]*[02-9](1st|2nd|3rd|[4-9]th) (21st, 22nd, 123rd, 1234th, etc.)\n' +
'COMPOUNDRULE 2\n' +
'COMPOUNDRULE n*1t\n' +
'COMPOUNDRULE n*mp\n' +
'WORDCHARS 0123456789\n' +

'PFX A Y 1\n' + 
'PFX A   0     re         .\n' + 

'PFX I Y 1\n' + 
'PFX I   0     in         .\n' + 

'PFX U Y 1\n' + 
'PFX U   0     un         .\n' + 

'PFX C Y 1\n' + 
'PFX C   0     de          .\n' + 

'PFX E Y 1\n' + 
'PFX E   0     dis         .\n' + 

'PFX F Y 1\n' + 
'PFX F   0     con         .\n' + 

'PFX K Y 1\n' + 
'PFX K   0     pro         .\n' + 

'SFX V N 2\n' + 
'SFX V   e     ive        e\n' + 
'SFX V   0     ive        [^e]\n' + 

'SFX N Y 3\n' + 
'SFX N   e     ion        e\n' + 
'SFX N   y     ication    y \n' + 
'SFX N   0     en         [^ey] \n' + 

'SFX X Y 3\n' + 
'SFX X   e     ions       e\n' + 
'SFX X   y     ications   y\n' + 
'SFX X   0     ens        [^ey]\n' + 

'SFX H N 2\n' + 
'SFX H   y     ieth       y\n' + 
'SFX H   0     th         [^y] \n' + 

'SFX Y Y 1\n' + 
'SFX Y   0     ly         .\n' + 

'SFX G Y 2\n' + 
'SFX G   e     ing        e\n' + 
'SFX G   0     ing        [^e] \n' + 

'SFX J Y 2\n' + 
'SFX J   e     ings       e\n' + 
'SFX J   0     ings       [^e]\n' + 

'SFX D Y 4\n' + 
'SFX D   0     d          e\n' + 
'SFX D   y     ied        [^aeiou]y\n' + 
'SFX D   0     ed         [^ey]\n' + 
'SFX D   0     ed         [aeiou]y\n' + 

'SFX T N 4\n' + 
'SFX T   0     st         e\n' + 
'SFX T   y     iest       [^aeiou]y\n' + 
'SFX T   0     est        [aeiou]y\n' + 
'SFX T   0     est        [^ey]\n' + 

'SFX R Y 4\n' + 
'SFX R   0     r          e\n' + 
'SFX R   y     ier        [^aeiou]y\n' + 
'SFX R   0     er         [aeiou]y\n' + 
'SFX R   0     er         [^ey]\n' + 

'SFX Z Y 4\n' + 
'SFX Z   0     rs         e\n' + 
'SFX Z   y     iers       [^aeiou]y\n' + 
'SFX Z   0     ers        [aeiou]y\n' + 
'SFX Z   0     ers        [^ey]\n' + 

'SFX S Y 4\n' + 
'SFX S   y     ies        [^aeiou]y\n' + 
'SFX S   0     s          [aeiou]y\n' + 
'SFX S   0     es         [sxzh]\n' + 
'SFX S   0     s          [^sxzhy]\n' + 

'SFX P Y 3\n' + 
'SFX P   y     iness      [^aeiou]y\n' + 
'SFX P   0     ness       [aeiou]y\n' + 
'SFX P   0     ness       [^y]\n' + 

'SFX M Y 1\n' + 
"SFX M   0     's         .\n" +

'SFX B Y 3\n' + 
'SFX B   0     able       [^aeiou]\n' + 
'SFX B   0     able       ee\n' + 
'SFX B   e     able       [^aeiou]e\n' + 

'SFX L Y 1\n' + 
'SFX L   0     ment       .\n' + 

'REP 88\n' + 
'REP a ei\n' + 
'REP ei a\n' + 
'REP a ey\n' + 
'REP ey a\n' + 
'REP ai ie\n' + 
'REP ie ai\n' + 
'REP are air\n' + 
'REP are ear\n' + 
'REP are eir\n' + 
'REP air are\n' + 
'REP air ere\n' + 
'REP ere air\n' + 
'REP ere ear\n' + 
'REP ere eir\n' + 
'REP ear are\n' + 
'REP ear air\n' + 
'REP ear ere\n' + 
'REP eir are\n' + 
'REP eir ere\n' + 
'REP ch te\n' + 
'REP te ch\n' + 
'REP ch ti\n' + 
'REP ti ch\n' + 
'REP ch tu\n' + 
'REP tu ch\n' + 
'REP ch s\n' + 
'REP s ch\n' + 
'REP ch k\n' + 
'REP k ch\n' + 
'REP f ph\n' + 
'REP ph f\n' + 
'REP gh f\n' + 
'REP f gh\n' + 
'REP i igh\n' + 
'REP igh i\n' + 
'REP i uy\n' + 
'REP uy i\n' + 
'REP i ee\n' + 
'REP ee i\n' + 
'REP j di\n' + 
'REP di j\n' + 
'REP j gg\n' + 
'REP gg j\n' + 
'REP j ge\n' + 
'REP ge j\n' + 
'REP s ti\n' + 
'REP ti s\n' + 
'REP s ci\n' + 
'REP ci s\n' + 
'REP k cc\n' + 
'REP cc k\n' + 
'REP k qu\n' + 
'REP qu k\n' + 
'REP kw qu\n' + 
'REP o eau\n' + 
'REP eau o\n' + 
'REP o ew\n' + 
'REP ew o\n' + 
'REP oo ew\n' + 
'REP ew oo\n' + 
'REP ew ui\n' + 
'REP ui ew\n' + 
'REP oo ui\n' + 
'REP ui oo\n' + 
'REP ew u\n' + 
'REP u ew\n' + 
'REP oo u\n' + 
'REP u oo\n' + 
'REP u oe\n' + 
'REP oe u\n' + 
'REP u ieu\n' + 
'REP ieu u\n' + 
'REP ue ew\n' + 
'REP ew ue\n' + 
'REP uff ough\n' + 
'REP oo ieu\n' + 
'REP ieu oo\n' + 
'REP ier ear\n' + 
'REP ear ier\n' + 
'REP ear air\n' + 
'REP air ear\n' + 
'REP w qu\n' + 
'REP qu w\n' + 
'REP z ss\n' + 
'REP ss z\n' + 
'REP shun tion\n' + 
'REP shun sion\n' + 
'REP shun cion\n';