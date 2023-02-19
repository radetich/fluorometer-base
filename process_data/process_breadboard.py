
import sys

#usage: python process_breadboard data.txt

#work in progress


file1 = open(sys.argv[1], 'r')
Lines = file1.readlines()
  
count = 0
# Strips the newline character
for line in Lines:
    count += 1
    print(line.strip())