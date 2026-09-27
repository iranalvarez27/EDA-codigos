#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int llave = 0;
    int grado = 0;
    int padre = 0;
    int hijo = 0;
    int izq = 0;
    int der = 0;
    bool marca = false;
};

vector<Nodito> noditos(1);

struct MonticuloFibonacci {
    int primero = 0;
    int ultimo = 0;
    int minimo = 0;

    void agregarRaiz(int x) {
        noditos[x].padre = 0;
        noditos[x].marca = false;
        noditos[x].izq = ultimo;
        noditos[x].der = 0;
        if (ultimo != 0) {
            noditos[ultimo].der = x;
        } else {
            primero = x;
        }
        ultimo = x;
    }

    void quitarRaiz(int x) {
        int a = noditos[x].izq;
        int b = noditos[x].der;
        if (a != 0) {
            noditos[a].der = b;
        } else {
            primero = b;
        }
        if (b != 0) {
            noditos[b].izq = a;
        } else {
            ultimo = a;
        }
    }

    int insert(int llave) {
        Nodito aux;
        aux.llave = llave;
        noditos.push_back(aux);
        int x = noditos.size() - 1;
        agregarRaiz(x);
        if (minimo == 0 || llave < noditos[minimo].llave) {
            minimo = x;
        }
        return x;
    }

    int getMin() {
        return noditos[minimo].llave;
    }

    bool empty() {
        if (minimo == 0) {
            return true;
        }
        return false;
    }

    void merge(MonticuloFibonacci& otro) {
        if (otro.primero == 0) {
            return;
        }
        if (primero == 0) {
            primero = otro.primero;
        } else {
            noditos[ultimo].der = otro.primero;
            noditos[otro.primero].izq = ultimo;
        }
        ultimo = otro.ultimo;
        if (minimo == 0 || noditos[otro.minimo].llave < noditos[minimo].llave) {
            minimo = otro.minimo;
        }
        otro.primero = 0;
        otro.ultimo = 0;
        otro.minimo = 0;
    }

    void enlazar(int y, int x) {
        noditos[y].padre = x;
        noditos[y].marca = false;
        noditos[y].izq = 0;
        noditos[y].der = noditos[x].hijo;
        if (noditos[x].hijo != 0) {
            noditos[noditos[x].hijo].izq = y;
        }
        noditos[x].hijo = y;
        noditos[x].grado = noditos[x].grado + 1;
    }

    void consolidar() {
        vector<int> lista;
        int r = primero;
        while (r != 0) {
            lista.push_back(r);
            r = noditos[r].der;
        }

        vector<int> porGrado;
        for (int i = 0; i < lista.size(); i++) {
            int x = lista[i];
            int g = noditos[x].grado;
            while (g < porGrado.size() && porGrado[g] != 0) {
                int y = porGrado[g];
                if (noditos[y].llave < noditos[x].llave) {
                    int temp = x;
                    x = y;
                    y = temp;
                }
                enlazar(y, x);
                porGrado[g] = 0;
                g++;
            }
            if (g >= porGrado.size()) {
                porGrado.resize(g + 1, 0);
            }
            porGrado[g] = x;
        }

        primero = 0;
        ultimo = 0;
        minimo = 0;
        for (int g = 0; g < porGrado.size(); g++) {
            if (porGrado[g] != 0) {
                agregarRaiz(porGrado[g]);
                if (minimo == 0 || noditos[porGrado[g]].llave < noditos[minimo].llave) {
                    minimo = porGrado[g];
                }
            }
        }
    }

    int extractMin() {
        int z = minimo;
        int h = noditos[z].hijo;
        while (h != 0) {
            int siguiente = noditos[h].der;
            agregarRaiz(h);
            h = siguiente;
        }
        quitarRaiz(z);
        consolidar();
        return noditos[z].llave;
    }

    void cut(int x, int p) {
        int a = noditos[x].izq;
        int b = noditos[x].der;
        if (a != 0) {
            noditos[a].der = b;
        } else {
            noditos[p].hijo = b;
        }
        if (b != 0) {
            noditos[b].izq = a;
        }
        noditos[p].grado = noditos[p].grado - 1;
        agregarRaiz(x);
    }

    void cascadingCut(int y) {
        int z = noditos[y].padre;
        if (z != 0) {
            if (noditos[y].marca == false) {
                noditos[y].marca = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }

    void decreaseKey(int x, int k) {
        noditos[x].llave = k;
        int p = noditos[x].padre;
        if (p != 0 && noditos[x].llave < noditos[p].llave) {
            cut(x, p);
            cascadingCut(p);
        }
        if (noditos[x].llave < noditos[minimo].llave) {
            minimo = x;
        }
    }
};