#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int n = 26;

struct Nodito {
    int hijo[n] = {};
    int cantPrefijo = 0;
    int cantPalabra = 0;
};

struct TriePersistente {
    vector<int> raiz = vector<int>(1, 0);
    vector<Nodito> noditos = vector<Nodito>(1);

    int buscarNodito(int v, string s) {
        int nodito = raiz[v];
        for (int i = 0; i < s.size(); i++) {
            nodito = noditos[nodito].hijo[s[i] - 'a'];
        }
        return nodito;
    }

    int update(int v, string s, int val) {
        int L = s.size();
        vector<int> camino;
        int nodito = raiz[v];
        camino.push_back(nodito);
        for (int i = 0; i < L; i++) {
            nodito = noditos[nodito].hijo[s[i] - 'a'];
            camino.push_back(nodito);
        }

        int abajo = 0;
        for (int i = L; i >= 0; i--) {
            Nodito aux = noditos[camino[i]];
            aux.cantPrefijo=aux.cantPrefijo+val;
            if (i == L) {
                aux.cantPalabra=aux.cantPalabra+val;
            } else {
                aux.hijo[s[i] - 'a'] = abajo;
            }
            noditos.push_back(aux);
            abajo = noditos.size() - 1;
        }

        raiz.push_back(abajo);
        return raiz.size()-1;
    }

    int insert(int v,string s) {
        return update(v, s, 1);
    }

    int remove(int v,string s) {
        if (search(v, s) == false) {
            raiz.push_back(raiz[v]);
            return raiz.size()- 1;
        }
        return update(v,s,-1);
    }

    bool search(int v, string s) {
        int nodito=buscarNodito(v, s);
        if (noditos[nodito].cantPalabra >   0) {
              return true;
        }
        return false;
    }

    int countPrefix(int v, string s) {
        int nodito=buscarNodito(v,s);
        return noditos[nodito].cantPrefijo;
    }
};