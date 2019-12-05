#include "../include/vecteur.hpp"
#include "../include/matrice.hpp"
#include "../include/globals.hpp"
#include <cmath>

//Définition de la fonctionnelle de la hauteur
double fonctionnelleHauteur(const Vecteur<double> &h, const Matrice &x)
{
	int nb_l = x.n / 2;
	int nb_c = x.m;
	Matrice hauteur = h.toMatrice(nb_l, nb_c);
	double value = 0;
	for (int i = 1; i < nb_l; i++)
	{
		for (int j = 1; j < nb_c; j++)
		{
			value += pow(hauteur(i + 1, j) - hauteur(i, j) - pas * x(i, j), 2) + pow(hauteur(i, j + 1) - hauteur(i, j) - pas * x(i + nb_l, j), 2);
		}
	}
	return value;
}