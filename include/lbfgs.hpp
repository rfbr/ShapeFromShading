#ifndef __LBFGS__
#define __LBFGS__
#include "matrice.hpp"

Vecteur<double> gradientFonctionnelle(const Vecteur<double> &x, const Matrice &image);
double fonctionnelle(const Vecteur<double> &x, const Matrice &image);
Vecteur<double> LBFGS(Vecteur<double> &x, double (*fonction)(const Vecteur<double> &, const Matrice &), Vecteur<double> (*fonctionGradient)(const Vecteur<double> &, const Matrice &), const Matrice &image, double eps);
Vecteur<double> gradientHauteur(const Vecteur<double> &x, const Matrice &h);
double fonctionnelleHauteur(const Vecteur<double> &x, const Matrice &hauteur);
void matriceToMesh(const string &fichier, const Matrice &M);
#endif
