import csv
import random

def printRandom(name, collection):
    if len(collection) == 0:
        print("Empty Collection: " + name)
        return
    val = random.choice(collection)
    print("{0} => {1} : {2}".format(name, val[0], val[1]))

with open('new.txt', 'r') as f:
    lines = []
    while True:
        line1 = f.readline()
        line2 = f.readline()
        if not line2:
            break
        line2 = line2.replace('\t', '  ')
        line = ','.join(filter(None, line2.split('  ')))
        lines.append( line1.rstrip() + ',' + line.rstrip())
    with open('processed.txt', 'w') as f:
        f.write('\n'.join(lines))

with open('processed.txt', 'r') as csvfile:
    reader = csv.reader(csvfile, skipinitialspace=True, delimiter=',')
    easy = []
    medium = []
    hard = []

    for row in reader:
        num = row[0]
        name = row[1]
        difficulty = row[3]

        if difficulty == "Easy":
            easy.append((num , name))
        elif difficulty == "Medium":
            medium.append((num , name))
        elif difficulty == "Hard":
            hard.append((num , name))
        else:
            print("YIKES, difficulty not found " + difficulty)
    
    printRandom("Easy", easy)
    printRandom("Medium", medium)
    printRandom("Hard", hard)

    '''
    with open('easy.txt', 'w') as f:
        f.write('\n'.join(easy))
    with open('medium.txt', 'w') as f:
        f.write('\n'.join(medium))
    with open('hard.txt', 'w') as f:
        f.write('\n'.join(hard))
    '''