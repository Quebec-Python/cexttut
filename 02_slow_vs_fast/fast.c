#include <Python.h>

// fast1 est une implémentation sans error checking. Il ne *faut pas* faire ça dans la vraie vie
// parce que ça résulte en des "hard crash", mais ne pas avoir le error checking dans les jambes
// rend le code plus facile à lire.

static PyObject *
fast1(PyObject *self, PyObject *args)
{
    // Le code C de Python n'est pas en C99, mais bien en ANSI C, ce qui fait que nos déclarations
    // de variables doivent être au début de nos blocs.
    PyObject *plist, *pnumber, *presult;
    // Py_ssize_t change selon la plateforme et les flags de compilation. Toutes les fonctions qui
    // on rapport avec des longueurs de listes ou des indexes de listes sont de ce type.
    Py_ssize_t i, list_count;
    long result, tmpnumber;

    // L'argument *args est une liste de PyObject, ce qui des fois est compliqué à traiter. C'est
    // pour ça qu'on a PyArg_ParseTuple(), qui aide à "dépacker" les arguments de la liste dans le
    // format qu'on veut. "O", c'est pour objet, mais on pourrait avoir un "i" qu'on dépack dans une
    // variable int ou un "s" qu'on dépack dans un char*.
    PyArg_ParseTuple(args, "O", &plist);
    result = 0;
    // C n'est pas orienté objet. On a pas de méthode, juste des fonctions qui prennent comme
    // premier paramètre notre structure cible (ici, notre liste).
    list_count = PyList_Size(plist);
    for (i=0; i<list_count; i++) {
        // On va chercher l'item à l'index i de notre plist
        pnumber = PyList_GET_ITEM(plist, i);
        // On le converti en long
        tmpnumber = PyLong_AsLong(pnumber);
        // On fait notre calcul
        result = result + (tmpnumber * i);
    }
    // Et hop, on retourne notre résultat
    presult = PyLong_FromLong(result);
    return presult;
}
// Ici, on est chanceux parce que le type de traitement qu'on fait ne nous oblige pas à gosser avec
// les références. Mais normalement, on a plein de Py_INCREF et Py_DECREF à mettre un peu partout si
// on ne veut pas de memory leak et/ou crash. Je vous en parlerai plus tard.


// Ici, c'est la même chose, mais avec le error checking. Dans une fonction Python, il faut toujours
// retourner un PyObject* si la fonction n'a pas eu d'exception, et NULL si il y a eu une exception.
// Oui, C ne gère pas les exceptions, donc il faut faire ça manuellement. Ce que ça veut dire, c'est
// qu'il faut *toujours* vérifier que le résultat de ce qu'on call n'est pas NULL, et si c'est NULL,
// il faut propager l'exception en retournant NULL soi-même. C'est compliqué vous trouvez? Attendez
// d'avoir à gérer les cas spéciaux de Py_DECREF/Py_INCREF en condition d'exception. *Là* c'est
// compliqué. La gestion de mémoire et d'exception est sans aucun doute la partie la plus complexe
// de l'API C de Python. Il suffit de regarder le code de Python pour s'en rendre compte.
static PyObject *
fast2(PyObject *self, PyObject *args)
{
    PyObject *plist, *pnumber, *presult;
    Py_ssize_t i, list_count;
    long result, tmpnumber;

    // Si on a pas le bon nombre ou type d'argument, PyArg_ParseTuple() va créer une exception. Si
    // elle le fait, elle retourne non-zero. Quand elle fait ça, on propage en retournant NULL.
    if (!PyArg_ParseTuple(args, "O", &plist)) {
        return NULL;
    }
    
    // On vérifie que notre argument est une liste
    if (!PyList_Check(plist)) {
        PyErr_SetString(PyExc_TypeError, "The first argument must be a list");
        return NULL;
    }
    result = 0;
    list_count = PyList_Size(plist);
    for (i=0; i<list_count; i++) {
        // Ici, si on ne contrôlait pas notre "i", il faudrait utiliser PyList_GetItem() et vérifier
        // que notre résultat n'est pas NULL (à cause d'un IndexError). Mais ici, on est certain que
        // i ne dépassera jamais len(plist), donc on peut utiliser la macro qui ne fait pas d'error
        // checking.
        pnumber = PyList_GET_ITEM(plist, i);
        // On vérifie que chaque élément est un int. En passant, dans Python, PyLong == int. Ça
        // s'appelle PyLong parce qu'avant, il y avait 2 type d'int (int et long) et il y avait
        // aussi PyInt et PyLong. Il y a eu unification et on a juste gardé PyLong.
        if (!PyLong_Check(pnumber)) {
            PyErr_SetString(PyExc_TypeError, "The list must contain only integers");
            return NULL;
        }
        tmpnumber = PyLong_AsLong(pnumber);
        result = result + (tmpnumber * i);
    }
    presult = PyLong_FromLong(result);
    return presult;
}

static PyMethodDef FastMethods[] = {
    {"fast1",  fast1, METH_VARARGS, NULL},
    {"fast2",  fast2, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL} /* Sentinelle */
};

static struct PyModuleDef fastmodule = {
   PyModuleDef_HEAD_INIT,
   "fast", /* nom of module */
   NULL, /* module docstring, peut être NULL */
   -1, /* Compliqué, garder à -1 */
   FastMethods
};

PyMODINIT_FUNC
PyInit_fast(void)
{
    return PyModule_Create(&fastmodule);
}
