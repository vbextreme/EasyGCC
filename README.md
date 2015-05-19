EasyGCC v0.3
============
Colora l'output di gcc, personalizza i colori e i token usati.

Setting
=======
le impostazioni dei colori si trovano<br/>
"~/.config/easygcc/setting"<br/>
i token con relativi colori sono in<br/>
"~/.config/easygcc/token"<br/>
I colori sono in formato vt100.

Bug:
====
(0.3)none

Require:
========
Easy Framework https://github.com/vbextreme/EasyFramework

To install it:
==============
Installazione normale, richiede di compilare tramite easygcc al posto di gcc per ottenere i colori<br/>
$ ./generate<br/>
<br/>
Per usare direttamente gcc</br>
$ ./generate --fake-gcc<br/>
$ sudo ./install

To uninstall it:
==============
$ sudo ./uninstall
