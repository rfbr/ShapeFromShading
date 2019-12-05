#ifndef __MATRICE__
#define __MATRICE__
#include <string>

using namespace std;
template<typename T>
class Vecteur;
class Matrice
{
  public:
	int n, m;	// Nombre de lignes, colonnes
	double **val; // Tableau de valeurs

	// Constructeurs
	Matrice();								 // Constructeur par défaut
	Matrice(int n_l, int n_c);				 // Constructeur avec dimension, initialisation à 0
	Matrice(int n_l, int n_c, double valeur); // Constructeur avec dimension + une valeur
	Matrice(const Matrice &M);				 // Constructeur par copie
	Matrice(int n, const string &id);		 // Contructeur matrice identité
	// Destructeur
	~Matrice();

	// Opérateurs

	Matrice &operator=(const Matrice &M);
	double &operator()(int i, int j) const;

	Matrice operator+(const Matrice &M) const;
	Matrice operator-(const Matrice &M) const;
	Matrice operator*(const Matrice &M) const;
	Vecteur<double> operator*(const Vecteur<double> &V) const;

	Matrice operator*(const double nb) const;
	Matrice operator/(const double nb) const;

	Matrice &operator/=(const double nb);
	Matrice &operator*=(const double nb);

	Matrice &operator+=(const Matrice &M);
	Matrice &operator-=(const Matrice &M);

	double norm();
	// Opérateurs d'affichage

	void print();
	friend ostream &operator<<(ostream &, const Matrice &M);
};

Matrice transpose(const Matrice &M);
Vecteur<double> toVecteur(const Matrice &M);



class Matrice_diag
{ // classe pour les matrices carrées diagonales
public:
  int n; //taille de la matrice carrée
  double *val; //tableau des valeurs (diagonale uniquement)

  Matrice_diag();								 // Constructeur par défaut
	Matrice_diag(int n_l, double valeur); // Constructeur avec dimension + une valeur

  // Destructeur
  ~Matrice_diag();

  friend ostream &operator<<(ostream &, const Matrice_diag &M);
  Matrice_diag &operator=(const Matrice_diag &M);
  Matrice_diag operator*(const double nb) const;
  Vecteur<double> operator*(const Vecteur<double> &V) const;
};

#endif
