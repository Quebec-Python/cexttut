fast.c: optimisation de bottlenecks
===

Pourquoi fait-on des modules C? Parce que c'est plus rapide. Combien plus rapide? Beaucoup. On a ici
un exemple concret d'optimisation par un module C. On se donne on traitement bidon à faire à des
chiffres au hazard. On aurait pu prendre une simple somme, mais alors le code python approprié
aurait été ``sum(l)`` et ``sum()`` est écrit en C, ce qui nous aurait fait comparer deux fonctions
C. Donc, j'ai compliqué un peu le traitement.

On a, d'un côté, le module ``slow.py`` avec des implémentations Python et de l'autre côté,
``fast.c`` avec les implémentations en C. On peut compiler le module C de la même façon que dans
l'autre exercice:

    python setup.py build_ext --inplace

Ensuite, on peut rouler ``run.py``, qui roule toutes les implémentations et les compare.
