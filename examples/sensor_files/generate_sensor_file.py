#!/usr/bin/env python

import sys
import random
import datetime

numberOfEntries = 30
logDate		= 0

if len(sys.argv) >= 2:
	numberOfEntries = int(sys.argv[1])

if len(sys.argv) >= 3:
	logDate = datetime.datetime.strptime(sys.argv[2], "%H:%M:%S")
else:
	logDate = datetime.datetime.strptime(str(random.randint(0,23))+":"+str(random.randint(0,59))+":"+str(random.randint(0,59)),"%H:%M:%S")

print "AK-Logger v1.0"
print "Datum: "+str(logDate.year)+"-"+str(logDate.month)+"-"+str(logDate.day)
print ""
print "Timestamp;Temperature;Humidity;"

for i in range(0,numberOfEntries):
	print str(logDate.hour)+":"+str(logDate.minute)+":"+str(logDate.second)+";"+"{0:.2f}".format(random.uniform(15.0,30.0))+";"+"{0:.2f}".format(random.uniform(30.0,80.0))+";"
	logDate += datetime.timedelta(seconds=1)

