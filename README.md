Tutoriel de création d'extensions Python en C
===

Ceci est un support pour un talk qui montre comment créer des extensions Python en C. Il est divisé
en sous-projets qui ont chacun leurs instructions. Ce code est en Python 3. Comme on a à compiler
des extensions, ça veut dire qu'on a besoin d'un compilateur des des headers de Python. Cela veut
dire qu'il faut installer le package "python3-dev".

Sous OS X, normalement, Python est toujours installé avec ses headers. XCode avec les "command line
tools" devrait alors être suffisant.

Sous Windows, arrangez vous. Compiler des trucs sous Windows, c'est vraiment compliqué.

Bootstrapping
---

Les projets 2 et 3 ont besoin, optionellement, de [pytest][pytest] et [cython][cython]. Le script
``bootstrap.sh`` permet d'automatiquement configurer cet environnement. Il faut Python 3.3+. On peut
le rouler avec:

    ./bootstrap.sh

[pytest]: http://pytest.org/
[cython]: http://cython.org/
