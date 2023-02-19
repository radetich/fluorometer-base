
import sys

#usage: python process_breadboard data.txt

#work in progress


file1 = open(sys.argv[1], 'r')
emmission = open("emm.txt", 'w')
filterreturn = open("fil.txt", 'w')
Lines = file1.readlines()
  
count = 0
# Strips the newline character
for line in Lines:
    count += 1
    print(line.strip())
    if(line.strip().startswith("FIL")):
        filterreturn.write(line.strip().replace("FIL ", ""))
        filterreturn.write(',\n')
    if(line.strip().startswith("EMM")):
        emmission.write(line.strip().replace("EMM ", ""))
        emmission.write(',\n')