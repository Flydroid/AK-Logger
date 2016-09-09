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

lineFormat = arduinoFileContent[3].rstrip("\n")+";Latitude;Longitude;Altitude;"
arduinoFileContent = arduinoFileContent[4:]
for i,x in enumerate(arduinoFileContent):
	splittedLine = x.split(";",1)
	arduinoFileContent[i] = (str(logDate.hour)+":"+str(logDate.minute)+":"+str(logDate.second)+";"+splittedLine[1]).rstrip("\n")
	logDate += datetime.timedelta(seconds=1)

print "AK-Logger v1.0"
print "Datum: "+str(logDate.year)+"-"+str(logDate.month)+"-"+str(logDate.day)
print ""
print lineFormat

igcFileContent[:] = [x for x in igcFileContent if x.startswith("B")]
igcFileContent = map(lambda s: s.rstrip("\n"), igcFileContent)
igcFileContent = map(lambda s: s[1:], igcFileContent)

for x in arduinoFileContent:
	splittedLine = x.split(";",1)
	lineDate = datetime.datetime.strptime(splittedLine[0],"%H:%M:%S")

	for y in igcFileContent:
		time = y[0:6]
		igcLineDate = datetime.datetime.strptime(time,"%H%M%S")

		if lineDate.hour == igcLineDate.hour and lineDate.minute == igcLineDate.minute and lineDate.second == igcLineDate.second:
			print x+y[6:14]+";"+y[14:23]
			break
