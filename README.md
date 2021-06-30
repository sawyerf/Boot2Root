# Boot2Root

## Ip
<pre>
$> sudo arp
Address                  HWtype  HWaddress           Flags Mask            Iface
bbox.lan                 ether   ac:84:c9:6c:f6:dc   C                     eth0
Tornado                  ether   74:29:af:33:25:19   C                     eth0
Bbox-TV-001              ether   a8:d3:f7:ff:a5:f2   C                     eth0
BornToSecHackMe          ether   08:00:27:ba:e4:36   C                     eth0
iPhone                   ether   6e:21:b8:7b:18:7a   C                     eth0
192.168.1.91             ether   b8:27:eb:db:44:24   C                     eth0
$> ping BornToSecHackMe
PING BornToSecHackMe (192.168.1.96) 56(84) bytes of data.
64 bytes from BornToSecHackMe (192.168.1.96): icmp_seq=1 ttl=64 time=0.826 ms
</pre>

## nmap
<pre>
$> nmap -A 192.168.1.96
Starting Nmap 7.91 ( https://nmap.org ) at 2021-06-27 01:11 CEST
Nmap scan report for BornToSecHackMe (192.168.1.96)
Host is up (0.064s latency).
Not shown: 994 closed ports
PORT    STATE SERVICE    VERSION
21/tcp  open  ftp        vsftpd 2.0.8 or later
|_ftp-anon: got code 500 "OOPS: vsftpd: refusing to run with writable root inside chroot()".
22/tcp  open  ssh        OpenSSH 5.9p1 Debian 5ubuntu1.7 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey: 
|   1024 07:bf:02:20:f0:8a:c8:48:1e:fc:41:ae:a4:46:fa:25 (DSA)
|   2048 26:dd:80:a3:df:c4:4b:53:1e:53:42:46:ef:6e:30:b2 (RSA)
|_  256 cf:c3:8c:31:d7:47:7c:84:e2:d2:16:31:b2:8e:63:a7 (ECDSA)
80/tcp  open  http       Apache httpd 2.2.22 ((Ubuntu))
|_http-server-header: Apache/2.2.22 (Ubuntu)
|_http-title: Hack me if you can
143/tcp open  imap       Dovecot imapd
|_imap-capabilities: more listed Pre-login ENABLE LOGIN-REFERRALS have IMAP4rev1 LOGINDISABLEDA0001 SASL-IR ID IDLE post-login OK capabilities LITERAL+ STARTTLS
|_ssl-date: 2021-06-26T23:12:00+00:00; -2s from scanner time.
443/tcp open  ssl/http   Apache httpd 2.2.22
|_http-server-header: Apache/2.2.22 (Ubuntu)
|_http-title: 404 Not Found
| ssl-cert: Subject: commonName=BornToSec
| Not valid before: 2015-10-08T00:19:46
|_Not valid after:  2025-10-05T00:19:46
|_ssl-date: 2021-06-26T23:12:00+00:00; -1s from scanner time.
993/tcp open  ssl/imaps?
| ssl-cert: Subject: commonName=localhost/organizationName=Dovecot mail server
| Not valid before: 2015-10-08T20:57:30
|_Not valid after:  2025-10-07T20:57:30
|_ssl-date: 2021-06-26T23:12:00+00:00; -1s from scanner time.
Service Info: Host: 127.0.1.1; OS: Linux; CPE: cpe:/o:linux:linux_kernel

Host script results:
|_clock-skew: mean: -1s, deviation: 0s, median: -1s

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 27.42 seconds
</pre>

## Html
- `gobuster dir -u http://192.168.1.96/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt -t 25 -x html`
<pre>
/index.html           (Status: 200) [Size: 1025]
/forum                (Status: 403) [Size: 285] 
/fonts                (Status: 301) [Size: 312] [--> http://192.168.1.96/fonts/]
</pre>

- `gobuster dir -u https://192.168.1.96/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt -t 25 -k`
<pre>
/forum                (Status: 301) [Size: 314] [--> https://192.168.1.96/forum/]
/webmail              (Status: 301) [Size: 316] [--> https://192.168.1.96/webmail/]
/phpmyadmin           (Status: 301) [Size: 319] [--> https://192.168.1.96/phpmyadmin/]
</pre>

## User
- dans [un post](https://192.168.1.96/forum/index.php?id=6) du forum on a les logs du ssh avec les username des gens connecté
  - root
  - admin
  - lmezard
