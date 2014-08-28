import os
import re
import eyed3

#TODO: 1. after cleaning filenames like askljd - .mp3 is left behind
#TODO: 2. patterns are repeatedly removed from given string. order of pattern matters right now. It should not.

dr = '/Users/priyank/Desktop/Queen'
#dr = '/Users/priyank/Dropbox/mujik4pk'

patterns = [
            "www.Songs.PK","songs.pk", "Songspk.info", "songspk.name",
            "www.dholbeat.in",
            "rKmania.com",
            "www.songsmela.com",
            "DjMaza.Info",
            "mp3clan.com",
            "[]", "()", "{}"
            ]

regExps = [ re.compile(re.escape(p), re.IGNORECASE) for p in patterns ]

def cleanseName(dirName, name):
    old = name
    new = ""
    for regExp in regExps:
        if regExp.search(old):
            new = regExp.sub("", old).strip()
            old = new
    if new != "":
        os.rename(os.path.join(dirName, name) , os.path.join(dirName, new) )


for dirName, subdirList, fileList in os.walk(dr):
    print('Files within: %s' % dirName)
    for fname in fileList:
        print('\t%s' % fname)
        cleanseName(dirName, fname)
    print('Directories within: %s' % dirName)
    for dname in subdirList:
        print('\t%s' % dname)
        cleanseName(dirName, dname)
	
#
#   for f in files:
#   	if "mp3" in f:
#   		print(f)
#   		id3File = eyed3.load(os.path.join(root,f))
#   		for regExp in regExps:
#   			if (id3File.tag.title != None) and regExp.search(id3File.tag.title):
#   				print("cleaning " + id3File.tag.title)
#   				id3File.tag.title = regExp.sub("", id3File.tag.title).strip()
#   				id3File.tag.save()
			
	#===========================================================================
	# print "****************"
	#===========================================================================
