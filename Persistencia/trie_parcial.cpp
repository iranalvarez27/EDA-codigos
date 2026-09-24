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

struct TriePersistenteParcial {
    vector<int> raiz = vector<int>(1, 0);
    vector<Nodito> noditos = vector<Nodito>(1);

    int ultimaVersion() {
        int ultima_version = raiz.size()-1;
        return ultima_version;
    }

    int buscarNodito(int v, string s) {
        int nodito = raiz[v];
        for (int i = 0; i < s.size(); i++) {
            nodito = noditos[nodito].hijo[s[i] - 'a'];
        }
        return nodito;
    }

    int update(string s, int val) {
        int L = s.size();
        int v = ultimaVersion();

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
            aux.cantPrefijo = aux.cantPrefijo + val;
            if (i == L) {
                aux.cantPalabra = aux.cantPalabra + val;
            } else {
                aux.hijo[s[i] - 'a'] = abajo;
            }
            noditos.push_back(aux);
            abajo = noditos.size() - 1;
        }

        raiz.push_back(abajo);
        return ultimaVersion();
    }

    int insert(string s) {
        return update(s, 1);
    }

    int remove(string s) {
        if (search(ultimaVersion(), s)==false) {
            raiz.push_back(raiz[ultimaVersion()]);
            return ultimaVersion();
        }
        return update(s, -1);
    }

    bool search(int v, string s) {
        int nodito = buscarNodito(v, s);
        if (noditos[nodito].cantPalabra > 0) {
            return true;
        }
        return false;
    }

    int countPrefix(int v, string s) {
        int nodito = buscarNodito(v, s);
        return noditos[nodito].cantPrefijo;
    }
};