import re

log = open('ssh.log', 'r').read()
print(set(re.findall(r'user (.+?) ', log)))
