#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int izq = 0;
    int der = 0;
    long long suma = 0;
};

struct SegmentTreePersistente {
    int n;
    vector<int> raiz = vector<int>(1, 0);
    vector<Nodito> noditos = vector<Nodito>(1);

    SegmentTreePersistente(int tam) {
        n = tam;
    }

    int update(int v, int pos, long long val) {
        vector<int> camino;
        vector<bool> direccion;
        int nodito = raiz[v];
        int l=0;
        int r=n-1;
        camino.push_back(nodito);
        while (l < r) {
            int m = (l+r)/2;
            if (pos <= m) {
                nodito = noditos[nodito].izq;
                r= m;
                direccion.push_back(true);
            } else {
                nodito = noditos[nodito].der;
                l = m+1;
                direccion.push_back(false);
            }
            camino.push_back(nodito);
        }

        int h = camino.size()-1;
        int abajo = 0;
        for (int i = h; i >= 0; i--) {
            Nodito aux = noditos[camino[i]];
            if (i == h) {
                aux.suma = val;
            } else {
                if (direccion[i] == true) {
                    aux.izq =abajo;
                } else {
                    aux.der= abajo;
                }
                aux.suma=noditos[aux.izq].suma + noditos[aux.der].suma;
            }
            noditos.push_back(aux);
            abajo = noditos.size()-1;
        }

        raiz.push_back(abajo);
        return raiz.size() - 1;
    }

    long long queryNodito(int nodito, int l, int r, int a, int b) {
        if (nodito == 0 || b < l || r < a) {
            return 0;
        }
        if (a <= l && r <= b) {
            return noditos[nodito].suma;
        }
        int m = (l+r)/2;
        long long izquierda = queryNodito(noditos[nodito].izq, l, m, a, b);
        long long derecha = queryNodito(noditos[nodito].der, m + 1, r, a, b);
        return izquierda + derecha;
    }

    long long query(int v, int a, int b) {
        return queryNodito(raiz[v], 0, n - 1, a, b);
    }
};