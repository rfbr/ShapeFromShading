#include "../include/matrice.hpp"
#include "../include/vecteur.hpp"
#include "../include/globals.hpp"

//Définition du gradient de la hauteur
Vecteur<double> gradientHauteur(const Vecteur<double> &h, const Matrice &x)
{
	int nb_l = x.n / 2;
	int nb_c = x.m;
	Matrice hauteur = h.toMatrice(nb_l, nb_c);
	Matrice gradient(nb_l, nb_c, 0);

	for (int i = 1; i < nb_l + 1; i++)
	{
		for (int j = 1; j < nb_c + 1; j++)
		{
			if (i != 1 && j != 1 && i != nb_l && j != nb_c)
			{
				gradient(i, j) = 4 * hauteur(i, j) - hauteur(i - 1, j) - pas * x(i - 1, j) - hauteur(i + 1, j) + pas * x(i, j) - hauteur(i, j - 1) - pas * x(i + nb_l, j - 1) - hauteur(i, j + 1) + pas * x(i + nb_l, j);
			}
		}
	}
	return toVecteur(gradient * 2);
}
