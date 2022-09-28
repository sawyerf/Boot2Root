import re
import requests

req = requests.get('https://boot2root.htb/forum/index.php?id=6', verify=False)
listUser = set(re.findall(r'user (.+?) ', req.text))
for user in listUser:
	print(user)