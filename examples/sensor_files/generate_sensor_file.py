#!/usr/bin/env python

import sys
import random
from datetime import datetime

numberOfEntries = 0
logDate		= 0

if len(sys.argv) == 2:
	numberOfEntries = sys.argv[1]

if len(sys.argv) == 3:
	logDate = datetime.strptime(sys.argv[2], "%H:%M:%S")
else:
	logDate = datetime.strptime(str(random.randint(0,24))+":"+str(random.randint(0,59))+":"+str(random.randint(0,59)),"%H:%M:%S")

print numberOfEntries
print logDate

