#!/usr/bin/env python
#
# max_temperature_map.py - Calculate maximum temperature from NCDC Global
#                          Hourly Data - Mapper part

import re   # import regular expressions
import sys  # import system-specific parameters and functions

# loop through the input, line by line
for line in sys.stdin:
  # remove leading and trailing whitespace
  val = line.strip()
  # extract values for year, temperature and quality indicator
  year = val[15:19]
  temp = val[87:92]
  q = val[92:93]
  # temperature is valid if not +9999 and quality indicator is
  # one of 0, 1, 4, 5 or 9
  if (temp != "+9999" and re.match("[01459]", q)):
    print "%s\t%s" % (year, temp)
