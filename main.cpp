
#include "pixel.h"
#include "graphe.h"
#include <cstdio> 
#include <iostream>
#include <fstream>
#include <climits>
#include <string>

using namespace std;

void afficherListe(int* l, int L, int C) {
    for (int i = 0; i < C; i ++){
      for (int j = 0; j < L; j ++){
        cout << l[i*L+j] << " ";
      }
      cout << "\n";
    }
}


int main(){
	string fichier;
    cout << "Entrer nom fichier .pgm : ";
	cin >> fichier;
    Graphe foo(fichier);

	cout << "Enter nom fichier où sauvegarder : ";
	cin >> fichier;
	foo.sauvegarder(fichier);

	int p;
	cout << "Pixel à projeter : ";
	cin >> p;

	cout << "Pixel coloré le plus proche : " << foo.projection(p) << "\n";

	string fichier1, fichier2;
	
	cout << "Premiere image de distance à unir: ";
	cin >> fichier1;
	Graphe foo1(fichier1);

	cout << "Seconde image de distance à unir: ";
	cin >> fichier2;
	Graphe foo2(fichier2);

	int* d = new int[foo1.L*foo1.C];
	int* d1 = new int[foo1.L*foo1.C];
	int* d2 = new int[foo1.L*foo1.C];

	foo1.liste_de_graphe(d1);
	foo2.liste_de_graphe(d2);
	foo.union_distances(d1, d2, d);

	afficherListe(d, foo1.L, foo1.C);

    return 0;
}

