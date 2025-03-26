
#ifndef _GRAPHE
#define _GRAPHE

#include "graphe.h"
#include "pixel.h"
#include <string>


class Graphe {
    public:
    Graphe(std::string nom_fichier);
    ~Graphe();

    int calc_indice(int i, int j);
    void calc_coordonne(int p, int& pi, int& pj);
    void liste_de_graphe(int* p);

    int voisin(int p, int d);
    
    void affichage();
    void sauvegarder(std::string nom_fichier);
    void Dijkstra(int ind, int* d, int* p);

    int projection(int ind);

    void union_distances(int* d1, int* d2, int* d_union);

    Pixel* matrice;
    int L;
    int C;
};

#endif
