#include <iostream>
#include <vector>
using namespace std;

struct Nodito {
    int valor = 0;
    int abajo = 0;
    int cantElementos = 0;
};

struct StackPersistente {
    vector<int> Top = vector<int>(1, 0);
    vector<Nodito> noditos = vector<Nodito>(1);

    int push(int v, int x) {
        Nodito aux;
        aux.valor = x;
        aux.abajo = Top[v];
        aux.cantElementos = noditos[Top[v]].cantElementos+1;
        noditos.push_back(aux);
        Top.push_back(noditos.size()-1);
        return Top.size() - 1;
    }

    int pop(int v) {
        if (empty(v) == true) {
            Top.push_back(Top[v]);
            return Top.size() - 1;
        }
        int nodito = Top[v];
        Top.push_back(noditos[nodito].abajo);
        return Top.size() - 1;
    }

    int top(int v) {
        int nodito = Top[v];
        return noditos[nodito].valor;
    }

    int size(int v) {
        int nodito = Top[v];
        return noditos[nodito].cantElementos;
    }

    bool empty(int v) {
        if (Top[v] == 0) {
            return true;
        }
        return false;
    }
};
