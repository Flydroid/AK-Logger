#!/usr/bin/env python

import sys
import datetime

if len(sys.argv) != 4:
	sys.exit()

arduinoFile = sys.argv[1]
igcFile = sys.argv[2]
logDate = sys.argv[3]

logDate = datetime.datetime.strptime(logDate, "%Y-%m-%d_%H:%M:%S")

with open(arduinoFile) as f:
	arduinoFileContent = f.readlines()
with open(igcFile) as f:
	igcFileContent = f.readlines()

arduinoFileContent = arduinoFileContent[4:]
for i,x in enumerate(arduinoFileContent):
	splittedLine = x.split(";",1)
	arduinoFileContent[i] = (str(logDate.hour)+":"+str(logDate.minute)+":"+str(logDate.second)+";"+splittedLine[1]).rstrip("\n")
	logDate += datetime.timedelta(seconds=1)

for x in arduinoFileContent:
	print x
