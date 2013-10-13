amount.c: Un exemple de classe Python en C
===

Là on commence à embarquer dans le complexe. Pour cet exercice, je suis allé cherché un exemple
concret d'optimisation C que j'ai fait pour une de mes propres applications, [moneyGuru][moneyguru].

C'est une application de finances personelles et la class ``Amount``, qui représente une paire
nombre/devise, est central à cette application et est un bottleneck à beaucoup d'endroits.

J'ai repris le code intégral en l'adaptant un peu pour qu'il puisse rouler en isolation.
Contrairement aux autres exercices, je n'ai pas ajouté de commentaires. Je ferai les commentaires
en live lors du talk.

Pour compiler ``amountc.c``, on fait comme toujours:

    python setup.py build_ext --inplace

On peut ensuite rouler ``run.py`` qui compare la vitesse des deux implémentations de ``Amount``.

Une nouveauté ici c'est que j'ai aussi ajouté les unit tests associés à ``Amount``. Il faut
installer [pytest][pytest] pour les rouler. Par défaut, les tests roulent sur ``amountpy``, mais
on peut les faire rouler sur ``amountc`` en changeant la ligne commentée au début de ``test.py``. On
roule le test en faisant:

    py.test test.py

[moneyguru]: https://github.com/hsoft/moneyguru
[pytest]: http://pytest.org
