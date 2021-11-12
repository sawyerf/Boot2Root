import os
import sys
import re

result = {}
if len(sys.argv) == 2:

  for f in os.listdir(sys.argv[1]):
    with open(sys.argv[1] + '/' + f, 'r') as fd:
      content = fd.read()
      file_number = re.findall("//file([0-9]*)", content)[0]
      result[int(file_number)] = content
      
  for fun in sorted(result):
    for i in result[fun].split("\n"):
      if 'useless' not in i and 'Got you' not in i and '//file' not in i and i != '' :
        print(i)
else:
  print("Usage \n python fun.py <PATH>")
