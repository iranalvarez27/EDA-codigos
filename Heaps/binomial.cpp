#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int llave = 0;
    int grado = 0;
    int padre = 0;
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
    noditos[b].padre = a;
    noditos[b].hermano = noditos[a].hijo;
    noditos[a].hijo = b;
    noditos[a].grado = noditos[a].grado + 1;
    return a;
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

struct MonticuloBinomial {
    vector<int> raices;

    int insert(int llave) {
        Nodito aux;
        aux.llave = llave;
        noditos.push_back(aux);
        int x = noditos.size() - 1;
        vector<int> solo(1, x);
        raices = unirRaices(raices, solo);
        return x;
    }

    int minNodito() {
        int menor = 0;
        for (int k = 0; k < raices.size(); k++) {
            if (raices[k] != 0) {
                if (menor == 0 || noditos[raices[k]].llave < noditos[menor].llave) {
                    menor = raices[k];
                }
            }
        }
        return menor;
    }

    int getMin() {
        int menor = minNodito();
        return noditos[menor].llave;
    }

    bool empty() {
        if (raices.size() == 0) {
            return true;
        }
        return false;
    }

    int extractMin() {
        int x = minNodito();
        raices[noditos[x].grado] = 0;

        vector<int> hijosX(noditos[x].grado, 0);
        int h = noditos[x].hijo;
        while (h != 0) {
            int siguiente = noditos[h].hermano;
            noditos[h].padre = 0;
            noditos[h].hermano = 0;
            hijosX[noditos[h].grado] = h;
            h = siguiente;
        }
        raices = unirRaices(raices, hijosX);
        return noditos[x].llave;
    }

    void merge(MonticuloBinomial& otro) {
        raices = unirRaices(raices, otro.raices);
        otro.raices.clear();
    }

    void decreaseKey(int x, int k) {
        noditos[x].llave = k;
        while (noditos[x].padre != 0 && noditos[x].llave < noditos[noditos[x].padre].llave) {
            int p = noditos[x].padre;
            int temp = noditos[x].llave;
            noditos[x].llave = noditos[p].llave;
            noditos[p].llave = temp;
            x = p;
        }
    }
};