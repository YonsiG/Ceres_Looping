#!/usr/bin/env python
import sys
import os
import re

def main():
    outname = sys.argv[2]
    outfile = open(outname,'w')
    fin = open(sys.argv[1],'r')
    fileNumber = int(sys.argv[3])
    line = fin.readline()
    while line:
        print line
        line = line.strip('\n')
        files = os.listdir(line)
        nfile=0
        for infile in files:
            index = re.search('.root', infile)
            if index:
                nfile=nfile+1
                print nfile
                if (nfile-5*int(nfile/5))==fileNumber:
                    outfile.write(line)
                    outfile.write(infile)
                    outfile.write('\n')
        line=fin.readline()

if __name__ == '__main__':
    main() 
