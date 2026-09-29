#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int llave = 0;
    int grado = 0;
    int hijo = 0;
    int hermano = 0;
};

struct Celda {
    int arbol = 0;
    int sig = 0;
};

struct Version {
    int primero = 0;
    int minimo = 0;
    int tam = 0;
};

vector<Nodito> noditos(1);
vector<Celda> celdas(1);

struct FibonacciPersistente {
    vector<Version> versiones = vector<Version>(1);

    int agregarCelda(int arbol, int sig) {
        Celda aux;
        aux.arbol = arbol;
        aux.sig = sig;
        celdas.push_back(aux);
        return celdas.size() - 1;
    }

    int menorDe(int a, int b) {
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }
        if (noditos[b].llave < noditos[a].llave) {
            return b;
        }
        return a;
    }

    int nuevaVersion(Version nv) {
        versiones.push_back(nv);
        return versiones.size() - 1;
    }

    int insert(int v, int llave) {
        Nodito aux;
        aux.llave = llave;
        noditos.push_back(aux);
        int x = noditos.size() - 1;
        Version nv;
        nv.primero = agregarCelda(x, versiones[v].primero);
        nv.minimo = menorDe(versiones[v].minimo, x);
        nv.tam = versiones[v].tam + 1;
        return nuevaVersion(nv);
    }

    int getMin(int v) {
        return noditos[versiones[v].minimo].llave;
    }

    bool empty(int v) {
        if (versiones[v].tam == 0) {
            return true;
        }
        return false;
    }

    int merge(int v1, int v2) {
        int lista = versiones[v1].primero;
        int c = versiones[v2].primero;
        while (c != 0) {
            lista = agregarCelda(celdas[c].arbol, lista);
            c = celdas[c].sig;
        }
        Version nv;
        nv.primero = lista;
        nv.minimo = menorDe(versiones[v1].minimo, versiones[v2].minimo);
        nv.tam = versiones[v1].tam + versiones[v2].tam;
        return nuevaVersion(nv);
    }

    int enlazar(int x, int y) {
        if (noditos[y].llave < noditos[x].llave) {
            int temp = x;
            x = y;
            y = temp;
        }
        Nodito copiaY = noditos[y];
        copiaY.hermano = noditos[x].hijo;
        noditos.push_back(copiaY);
        int nuevoY = noditos.size() - 1;

        Nodito copiaX = noditos[x];
        copiaX.hijo = nuevoY;
        copiaX.grado = copiaX.grado + 1;
        noditos.push_back(copiaX);
        return noditos.size() - 1;
    }

    int extractMin(int v) {
        if (versiones[v].tam <= 1) {
            Version vacia;
            return nuevaVersion(vacia);
        }
        int z = versiones[v].minimo;

        vector<int> lista;
        bool yaSaltado = false;
        int c = versiones[v].primero;
        while (c != 0) {
            if (celdas[c].arbol == z && yaSaltado == false) {
                yaSaltado = true;
            } else {
                lista.push_back(celdas[c].arbol);
            }
            c = celdas[c].sig;
        }
        int h = noditos[z].hijo;
        while (h != 0) {
            lista.push_back(h);
            h = noditos[h].hermano;
        }

        vector<int> porGrado;
        for (int i = 0; i < lista.size(); i++) {
            int x = lista[i];
            int g = noditos[x].grado;
            while (g < porGrado.size() && porGrado[g] != 0) {
                x = enlazar(x, porGrado[g]);
                porGrado[g] = 0;
                g++;
            }
            if (g >= porGrado.size()) {
                porGrado.resize(g + 1, 0);
            }
            porGrado[g] = x;
        }

        Version nv;
        for (int g = 0; g < porGrado.size(); g++) {
            if (porGrado[g] != 0) {
                nv.primero = agregarCelda(porGrado[g], nv.primero);
                nv.minimo = menorDe(nv.minimo, porGrado[g]);
            }
        }
        nv.tam = versiones[v].tam - 1;
        return nuevaVersion(nv);
    }
};