#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int valor = 0;
    int izq = 0;
    int der = 0;
};

struct HeapBinarioPersistente {
    vector<Nodito> noditos = vector<Nodito>(1);
    vector<int> raiz = vector<int>(1, 0);
    vector<int> tam = vector<int>(1, 0);

    int copiar(int nodito) {
        Nodito aux = noditos[nodito];
        noditos.push_back(aux);
        return noditos.size()-1;
    }

        vector<bool> caminito(int pos) {
        vector<bool> bits;
        while (pos > 1) {
            if (pos % 2 == 1) {
                bits.push_back(true);
            } else {
                bits.push_back(false);
            }
            pos = pos / 2;
        }
        vector<bool> reversa;
        for (int i = bits.size() - 1; i >= 0; i--) {
            reversa.push_back(bits[i]);
        }
        return reversa;
    }

    int nuevaVersion(int r, int t) {
        raiz.push_back(r);
        tam.push_back(t);
        return raiz.size() - 1;
    }

    int insert(int v, int x) {
        int n = tam[v] + 1;
        if (n == 1) {
            Nodito aux;
            aux.valor = x;
            noditos.push_back(aux);
            return nuevaVersion(noditos.size() - 1, 1);
        }
        vector<bool> bits = caminito(n);
        vector<int> camino;
        int actual = copiar(raiz[v]);
        camino.push_back(actual);
        for (int i = 0; i < bits.size(); i++) {
            int siguiente;
            if (i == bits.size() - 1) {
                Nodito aux;
                aux.valor = x;
                noditos.push_back(aux);
                siguiente = noditos.size() - 1;
            } else if (bits[i] == false) {
                siguiente = copiar(noditos[actual].izq);
            } else {
                siguiente = copiar(noditos[actual].der);
            }
            if (bits[i] == false) {
                noditos[actual].izq = siguiente;
            } else {
                noditos[actual].der = siguiente;
            }
            actual = siguiente;
            camino.push_back(actual);
        }

        for (int i = camino.size() - 1; i > 0; i--) {
            int hijo = camino[i];
            int padre = camino[i - 1];
            if (noditos[hijo].valor < noditos[padre].valor) {
                int temp = noditos[hijo].valor;
                noditos[hijo].valor = noditos[padre].valor;
                noditos[padre].valor = temp;
            } else {
                break;
            }
        }
        return nuevaVersion(camino[0], n);
    }

    int getMin(int v) {
        return noditos[raiz[v]].valor;
    }

    bool empty(int v) {
        if (tam[v] == 0) {
            return true;
        }
        return false;
    }

    int extractMin(int v) {
        int n = tam[v];
        if (n <= 1) {
            return nuevaVersion(0, 0);
        }
        vector<bool> bits = caminito(n);
        int nuevaRaiz = copiar(raiz[v]);
        int actual = nuevaRaiz;
        int ultimo = 0;
        for (int i = 0; i < bits.size(); i++) {
            if (i == bits.size() - 1) {
                int hoja;
                if (bits[i] == false) {
                    hoja = noditos[actual].izq;
                    noditos[actual].izq = 0;
                } else {
                    hoja = noditos[actual].der;
                    noditos[actual].der = 0;
                }
                ultimo = noditos[hoja].valor;
            } else {
                int siguiente;
                if (bits[i] == false) {
                    siguiente = copiar(noditos[actual].izq);
                    noditos[actual].izq = siguiente;
                } else {
                    siguiente = copiar(noditos[actual].der);
                    noditos[actual].der = siguiente;
                }
                actual = siguiente;
            }
        }
        noditos[nuevaRaiz].valor = ultimo;
        actual = nuevaRaiz;
        while (true) {
            int izq = noditos[actual].izq;
            int der = noditos[actual].der;
            int menor = 0;
            bool esIzq = true;
            if (izq != 0) {
                menor = izq;
            }
            if (der != 0 && noditos[der].valor < noditos[menor].valor) {
                menor = der;
                esIzq = false;
            }
            if (menor == 0 || noditos[menor].valor >= noditos[actual].valor) {
                break;
            }
            int copia = copiar(menor);
            if (esIzq == true) {
                noditos[actual].izq = copia;
            } else {
                noditos[actual].der = copia;
            }
            int temp = noditos[actual].valor;
            noditos[actual].valor = noditos[copia].valor;
            noditos[copia].valor = temp;
            actual = copia;
        }
        return nuevaVersion(nuevaRaiz, n - 1);
    }
};