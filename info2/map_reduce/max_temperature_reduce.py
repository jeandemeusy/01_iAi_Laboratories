#!/usr/bin/env python
#
# max_temperature_reduce.py - Calculate maximum temperature from NCDC Global
#                             Hourly Data - Reducer part

import sys

last_key = None
max_val = -sys.maxint
# loop through the input, line by line
for line in sys.stdin:
  # each line contains a key and a value separated by a tab character
  (key, val) = line.strip().split("\t")
  # Hadoop has sorted the input by key, so we get the values
  # for the same key immediately one after the other.
  # Test if we just got a new key, in this case output the maximum
  # temperature for the previous key and reinitialize the variables.
  # If not, keep calculating the maximum temperature.
  if last_key and last_key != key:
    print "%s\t%s" % (last_key, max_val)
    max_val = int(val)
  else:
    max_val = max(max_val, int(val))
  last_key = key

# we've reached the end of the file, output what is left
if last_key:
  print "%s\t%s" % (last_key, max_val)
