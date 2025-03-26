
#include "pixel.h"
#include "graphe.h"

#include <cstdio> 
#include <iostream>
#include <fstream>
#include <climits>
#include <string>


using namespace std;


Graphe::Graphe(string nom_fichier){
    ifstream fichier (nom_fichier);
    if(!fichier.good()) exit(1);

    string tmp;
    fichier >> tmp;
    fichier >> L;
    fichier >> C;
    fichier >> tmp;
    matrice = new Pixel[L*C];
    for (int i = 0; i < L*C; i ++){
        int valeur;
        fichier >> valeur;
        Pixel p(valeur);
        matrice[i] = p;
    }
    fichier.close();
}

Graphe::~Graphe(){
  delete matrice;
}

void Graphe::sauvegarder(string nom_fichier){
    ofstream fichier(nom_fichier);
    fichier << "P2\n";
    fichier << L << " " << C << "\n";
    fichier << 15 << "\n";
    for (int i = 0; i < L * C; i++) {
        int a_afficher = (int)matrice[i].nivGris;
        std::string espace;
        if (a_afficher < 10) // Si le niveau de gris est inférieur a 10, on sépare de deux espaces
            espace = "  ";
        else // Sinon, le niveau de gris comporte 2 caractères et on ne met donc qu'un seul espace
            espace = " ";
        fichier << a_afficher << espace;
        if (i % L == L - 1)
            fichier << "\n";  // Saut de ligne après chaque ligne de pixels
    }
    fichier.close();
}

int Graphe::calc_indice(int i, int j){ // Calcule l'indice dans le tableau associé aux coordonnées i, j
    return i*L + j;
}

void Graphe::calc_coordonne(int p, int& pi, int& pj){ // Calcule les coordonnées associé a l'indice p du tableau
    pi = p % C;
    pj = p / C;
}

void Graphe::liste_de_graphe(int* p){
  for (int i = 0; i < L*C; i ++){
    p[i] = matrice[i].nivGris;
  }
}

int Graphe::voisin(int p, int d){
    int i[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    int j[8] = {1, 1, 0, -1, -1, -1, 0, 1};
    int pi, pj;
    calc_coordonne(p, pi, pj);
    if ((pi + i[d] < 0) || (pj + j[d] < 0)){
        return -1;
    }
    int v = calc_indice(pi + i[d], pj + j[d]);
    if (v < 0 || v >= L*C)
        return -1;
    else
        return v;
}

void Graphe::affichage(){
    cout << C << "\n";
    cout << L << "\n";
    for (int i = 0; i < L*C; i ++){
        cout << (int)matrice[i].nivGris << " ";
    }
}

void Graphe::Dijkstra(int ind, int* d, int* p) {
    // Initialisation de toutes les distances à l'infini
    int* c = new int[L*C];
    int poids, nbG = 0, min, nmin;
    for (int i = 0; i < L * C; i++) {
        d[i] = INT_MAX;  // Distance initiale très grande
        p[i] = 0;
        c[i] = 0; // 0 -> blanc, 1 -> gris, 2 -> noir
    }
    for (int dir = 0; dir < 8; dir++) {
      int v = voisin(ind, dir);
      if (v != -1){
          if (dir%2 == 0) {  // Ouest, Nord, Est, Sud
                  poids = 2;
              }
              else {  // Diagonales : Sud-Est, Nord-Est, Nord-Ouest, Sud-Ouest
                  poids = 3;
              }
          d[v] = poids;
          p[v] = ind;
          c[v] = 1;
          nbG++;
      }
    }
    d[ind] = 0;
    c[ind] = 2;
    while(nbG > 1) {
        min = INT_MAX;
        for(int i = 0; i < L * C; i++) {
            if (c[i] == 1 && d[i] < min) {
                min = d[i];
                nmin = i;
            }
        }
        for (int dir = 0; dir < 8; dir++) {
            int v = voisin(nmin, dir);
            if (v != -1 && c[v] != 2 ) {
                if(c[v] == 0) {
                    c[v] = 1;
                    nbG ++;
                }
                if (dir%2 == 0) {  // Ouest, Nord, Est, Sud
                        poids = 2;
                    }
                    else {  // Diagonales : Sud-Est, Nord-Est, Nord-Ouest, Sud-Ouest
                        poids = 3;
                    }
                if((d[nmin] + poids) < d[v]) {
                    d[v] = d[nmin] + poids;
                    p[v] = nmin;
                }
            }
        }
        if (c[nmin] == 1){
            c[nmin] = 2;
            nbG --; 
        }
        else
            c[nmin] = 2;
    }
}


int Graphe::projection(int ind){
    int* p = new int[C*L];
    int* d = new int[C*L];
    Dijkstra(ind, d, p);
    int mini = INT_MAX;
    int j = 0;
    for (int i = 0; i < L*C; i ++){
        if (((matrice[i]).nivGris != 0) && (d[i] < mini)){
            mini = d[i];
            j = i;
        }
    }
    return j;
}

void Graphe::union_distances(int* d1, int* d2, int* d_union) {
    for (int i = 0; i < L * C; ++i) {
        d_union[i] = max(d1[i], d2[i]);
    }
}

int find_min(int*d, int*p, int L, int C){
    int mini = d[0];
    int j = p[0];
    for (int i = 0; i < L * C; i++){
        if (d[i] < mini){
            mini = d[i];
            j = p[i];
        }
    }
    return j;
}

