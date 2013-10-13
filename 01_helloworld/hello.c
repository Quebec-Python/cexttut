#include <Python.h>

// Pourquoi tant de static partout? parce qu'on ne doit jamais exporter de noms de fonctions dans
// notre librairie pour éviter qu'il y ait des name clash entre les extensions. Pour ce qui est du
// "PyObject *": **tout** dans Python est un PyObject. Toutes les fonctions dans Python ne prennent
// que des PyObject en paramètre, et ne retournent que des PyObject.
static PyObject *
hello_world(PyObject *self, PyObject *args)
{
    printf("Hello World!\n");
    // Remarquez comment je dois incrémenter la référence de la constante None avant de la
    // retourner. Bizarre ein? On va voir pourquoi plus tard.
    Py_INCREF(Py_None);
    return Py_None;
}

// Ici, on se bâtit la liste de fonctions que contient notre module. La liste contient des éléments
// de 4 de long: (nom, fonction, type, docstring). Il n'y a que le type qui ne soit pas directement
// évident: c'est pour spécifier si notre fonction supporte les kwargs ou non. Ça peut paraître con,
// mais ne pas avoir à traiter les kwargs, ça sauve du temps si on en a pas besoin. La sentinelle à
// la fin, c'est pour que l'itérateur sache qu'il est rendu à la fin de la liste.
static PyMethodDef HelloMethods[] = {
    {"hello_world",  hello_world, METH_VARARGS,
     "Prints Hello World!"},
    {NULL, NULL, 0, NULL} /* Sentinelle */
};

// Ici, c'est les méta-données du module. Dans notre cas, on y ajoute que le nom du module et la
// liste des fonctions qu'on a défini plus haut, mais il pourrait y avoir autre chose, comme par
// exemple la liste des classes (oui oui, on peut définir des classes dans un module C. c'est un peu
// compliqué, mais c'est possible).
static struct PyModuleDef hellomodule = {
   PyModuleDef_HEAD_INIT,
   "hello", /* nom of module */
   NULL, /* module docstring, peut être NULL */
   -1, /* Compliqué, garder à -1 */
   HelloMethods
};

// Ici, on initialize notre module en utilisant les méta-données définies plus haut. À remarquer:
// c'est la seule fonction qui n'est pas statique. C'est donc la seule qui sera exportée. Il est
// important de suive la nomenclature "PyInit_<nom module>". Ah oui, PVI: les trucs du genre 
// PyMODINIT_FUNC et PyModuleDef_HEAD_INIT, c'est juste des macros qui sont remplacés par des trucs
// qui varient selon le "linkage" (si on compile en C ou C++ par exemple). Ou bien, dans le cas de
// PyModuleDef_HEAD_INIT, c'est juste des trucs qu'on ne veut pas copier coller (les 4 premiers
// éléments d'un PyModuleDef sont toujours initialisés de la même façon)
PyMODINIT_FUNC
PyInit_hello(void)
{
    return PyModule_Create(&hellomodule);
}
