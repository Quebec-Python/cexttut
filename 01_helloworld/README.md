hello.c: Extension vraiment minimale
===

Ceci est à peu près le plus minimal qu'on peut faire en termes d'extensions C. Il est fortement
basé sur l'excellent [tutoriel de la doc Python][exttut].

On crée une simple méthode qui ne prend pas d'argument et qui call ``printf``. Le reste, c'est du
"boilerplate" de base: la liste des méthodes du module, puis la structure de donnée contenant les
méta-données nécessaires à la création du module. Ensuite hop! on crée le module.

On compile ce module en utilisant ``distutils`` (inclut dans Python). On compile notre extension
avec cette commande:

    python setup.py build_ext --inplace

On aurait pu faire juste ``python setup.py install``, mais il aurait fallu faire une virtualenv et
tout. Avec ``build_ext --inplace``, on dit à distutils de juste compiler les extensions et de mettre
le résultat de cette compilation directement dans notre répertoire de travail.

On a donc directement notre ``.so`` à portée de main et on peut l'importer dans python:

    >>> import hello
    >>> hello.hello_world()

Voilà!

[exttut]: http://docs.python.org/3/extending/extending.html
