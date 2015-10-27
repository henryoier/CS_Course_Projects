import sys
f = open("at.txt")
line = f.readline()
count = 0
num = 0
while line:
	if count % 10 != 0:
    	line = line.strip('\n')
    	sys.stdout.write(line)
    	sys.stdout.write(';')
    	print num
    count = count + 1               
    if count % 10 == 0:
       num = num + 1

    line = f.readline()

f.close()
