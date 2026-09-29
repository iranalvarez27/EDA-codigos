#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int llave = 0;
    int grado = 0;
    int hijo = 0;
    int hermano = 0;
};

vector<Nodito> noditos(1);

int enlazar(int a, int b) {
    if (noditos[b].llave < noditos[a].llave) {
        int temp = a;
        a = b;
        b = temp;
    }
    Nodito copiaB = noditos[b];
    copiaB.hermano = noditos[a].hijo;
    noditos.push_back(copiaB);
    int nuevoB = noditos.size() - 1;

    Nodito copiaA = noditos[a];
    copiaA.hijo = nuevoB;
    copiaA.grado = copiaA.grado + 1;
    noditos.push_back(copiaA);
    return noditos.size() - 1;
}

vector<int> unirRaices(vector<int> a, vector<int> b) {
    int tam = a.size();
    if (b.size() > tam) {
        tam = b.size();
    }
    tam = tam + 1;
    a.resize(tam, 0);
    b.resize(tam, 0);
    vector<int> res(tam, 0);
    int acarreo = 0;

    for (int k = 0; k < tam; k++) {
        int arboles[3];
        int cant = 0;
        if (a[k] != 0) {
            arboles[cant] = a[k];
            cant++;
        }
        if (b[k] != 0) {
            arboles[cant] = b[k];
            cant++;
        }
        if (acarreo != 0) {
            arboles[cant] = acarreo;
            cant++;
        }
        acarreo = 0;
        if (cant == 1) {
            res[k] = arboles[0];
        } else if (cant == 2) {
            acarreo = enlazar(arboles[0], arboles[1]);
        } else if (cant == 3) {
            res[k] = arboles[2];
            acarreo = enlazar(arboles[0], arboles[1]);
        }
    }
    while (res.size() > 0 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

struct BinomialPersistente {
    vector<vector<int>> versiones = vector<vector<int>>(1);

    int nuevaVersion(vector<int> raices) {
        versiones.push_back(raices);
        return versiones.size() - 1;
    }

    int insert(int v, int llave) { 
        Nodito aux;
        aux.llave = llave;
        noditos.push_back(aux);
        int x = noditos.size() - 1;
        vector<int> solo(1, x);
        return nuevaVersion(unirRaices(versiones[v], solo));
    }

    int minNodito(int v) {
        int menor = 0;
        for (int k = 0; k < versiones[v].size(); k++) {
            int r = versiones[v][k];
            if (r != 0) {
                if (menor == 0 || noditos[r].llave < noditos[menor].llave) {
                    menor = r;
                }
            }
        }
        return menor;
    }

    int getMin(int v) {
        int menor = minNodito(v);
        return noditos[menor].llave;
    }

    bool empty(int v) {
        if (versiones[v].size() == 0) {
            return true;
        }
        return false;
    }

    int extractMin(int v) {
        int x = minNodito(v);
        vector<int> resto = versiones[v];
        resto[noditos[x].grado] = 0;

        vector<int> hijosX(noditos[x].grado, 0);
        int h = noditos[x].hijo;
        while (h != 0) {
            hijosX[noditos[h].grado] = h;
            h = noditos[h].hermano;
        }
        return nuevaVersion(unirRaices(resto, hijosX));
    }

    int merge(int v1, int v2) {
        return nuevaVersion(unirRaices(versiones[v1], versiones[v2]));
    }
};