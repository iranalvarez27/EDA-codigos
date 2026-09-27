#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int valor=0;
    int abajo= 0;
    int cantElementos =0;
};

struct QueuePersistenteParcial {
    vector<int> entrada = vector<int>(1, 0);
    vector<int> salida = vector<int>(1, 0);
    vector<Nodito> noditos = vector<Nodito>(1);

    int ultimaVersion() {
        int ultima_version = entrada.size()-1;
        return ultima_version;
    }

    int pushNodito(int abajo, int x) {
        Nodito aux;
        aux.valor = x;
        aux.abajo = abajo;
        aux.cantElementos = noditos[abajo].cantElementos+ 1;
        noditos.push_back(aux);
        return noditos.size()-1;
    }

    int enqueue(int x) {
        int v = ultimaVersion();
        if (salida[v] == 0) {
            entrada.push_back(entrada[v]);
            salida.push_back(pushNodito(0, x));
        } else {
            entrada.push_back(pushNodito(entrada[v], x));
            salida.push_back(salida[v]);
        }
        return ultimaVersion();
    }

    int dequeue() {
        int v=ultimaVersion();
        if (empty(v) == true) {
            entrada.push_back(entrada[v]);
            salida.push_back(salida[v]);
            return ultimaVersion();
        }
        int nuevaSalida = noditos[salida[v]].abajo;
        int nuevaEntrada = entrada[v];
        if (nuevaSalida == 0) {
            while (nuevaEntrada != 0) {
                nuevaSalida = pushNodito(nuevaSalida, noditos[nuevaEntrada].valor);
                nuevaEntrada = noditos[nuevaEntrada].abajo;
            }
        }
        entrada.push_back(nuevaEntrada);
        salida.push_back(nuevaSalida);
        return ultimaVersion();
    }

    int front(int v) {
        int nodito = salida[v];
        return noditos[nodito].valor;
    }

    int size(int v) {
        int total = noditos[entrada[v]].cantElementos + noditos[salida[v]].cantElementos;
        return total;
    }

    bool empty(int v) {
        if (salida[v]== 0) {
            return true;
        }
        return false;
    }
};