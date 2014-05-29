import os
import re

#dr = '/Users/priyank/Desktop/Queen'
dr = '/Users/priyank/Dropbox'

#tree = os.listdir(dir)

patterns = ["(songs.pk)", "[songs.pk]", "[Songspk.info]"]

regExps = [ re.compile(re.escape(p), re.IGNORECASE) for p in patterns ]


def cleanup(dir, tree):
	print "cleaning Dir: " + dir
	for item in tree:
		old = item
		print "cleaning File: " + old
		#new = old.replace(songsPk, "")
		new = ""
		for regExp in regExps:
			if regExp.search(old):
				# print "match found of %s in %s" % (regExp.pattern, old)
				new = regExp.sub("", old).strip()
				print "old: " + os.path.join(dir, old)
				print "new: " + os.path.join(dir, new)
				os.rename(os.path.join(dir, old) , os.path.join(dir, new) )
		#new = regExps.sub("", old)

for root,dirs,files in os.walk(dr):
	# print "root: " + root
	# for dir in dirs:
	# 	#print "dirs: " + dir
	# 	cleanup(root, dir)
	# for file in files:
	#  	print "root %s, files %s " % (root, file)
	cleanup(root, dirs)
	cleanup(root, files)
	print "****************"
