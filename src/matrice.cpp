#include "../include/matrice.hpp"
#include "../include/vecteur.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//Définition de la classe des matrices

// Constructeurs
Matrice::Matrice()
{
	n = 0;
	m = 0;
	val = 0;
};

Matrice::Matrice(int n_l, int n_c)
{
	n = n_l;
	m = n_c;
	val = new double *[n];

	for (int i = 0; i < n; i++)
	{
		val[i] = new double[m];

		for (int j = 0; j < m; j++)
		{
			val[i][j] = 0;
		}
	}
};

Matrice::Matrice(int n_l, int n_c, double valeur)
{
	n = n_l;
	m = n_c;
	val = new double *[n];

	for (int i = 0; i < n; i++)
	{
		val[i] = new double[m];

		for (int j = 0; j < m; j++)
		{
			val[i][j] = valeur;
		}
	}
};

Matrice::Matrice(const Matrice &M)
{
	n = M.n;
	m = M.m;
	val = new double *[n];

	for (int i = 0; i < n; i++)
	{
		val[i] = new double[m];

		for (int j = 0; j < m; j++)
		{
			val[i][j] = M.val[i][j];
		}
	}
};

Matrice::Matrice(int dim, const string &id)
{
	if (id != "Id")
	{
		cout << "Cet argument n'est pas pris en compte.\n";
		exit(1);
	}
	n = dim;
	m = dim;
	val = new double *[dim];
	for (int i = 0; i < dim; i++)
	{
		val[i] = new double[dim];
		for (int j = 0; j < dim; j++)
		{
			if (i == j)
			{
				val[i][j] = 1;
			}
			else
			{
				val[i][j] = 0;
			}
		}
	}
};

// Destructeur

Matrice::~Matrice()
{
	if (val != 0)
	{
		for (int i = 0; i < n; i++)
		{
			delete[] val[i];
		}
		delete[] val;
		n = 0;
		m = 0;
	}
};

// Opérateurs

Matrice &Matrice::operator=(const Matrice &M)
{
	if (this != &M) //assignation M = M impossible
	{
		if (M.n != n || M.m != m) // si tailles pas compatibles
		{
			for (int i = 0; i < n; i++)
			{
				delete[] val[i];
			}
			delete[] val;
			n = M.n;
			m = M.m;
			val = new double *[n];
		}
	}

	for (int i = 0; i < n; i++)
	{
		val[i] = new double[m];
		for (int j = 0; j < m; j++)
		{
			val[i][j] = M.val[i][j];
		}
	}
	return *this;
};

double &Matrice::operator()(int i, int j) const
{
	if (i > n || j > m) // si out of range
	{
		cout << "Erreur: les indices sont trop grands. \n";
		exit(1);
	}
	return val[i - 1][j - 1];
};

Matrice Matrice::operator+(const Matrice &M) const
{
	Matrice tmp(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp.val[i][j] = val[i][j] + M.val[i][j];

	return tmp;
};

Matrice Matrice::operator-(const Matrice &M) const
{
	Matrice tmp(n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			tmp.val[i][j] = val[i][j] - M.val[i][j];
		}
	}
	return tmp;
};

Matrice Matrice::operator*(const Matrice &M) const
{
	Matrice tmp(n, M.m, 0);
	if (m == M.n)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < M.m; j++)
			{
				for (int k = 0; k < m; k++)
					tmp.val[i][j] += val[i][k] * M.val[k][j];
			}
	}
	else
	{
		cout << "Erreur, wallah c'est pas les bonnes tailles \n";
		exit(1);
	}
	return tmp;
};

Vecteur<double> Matrice::operator*(const Vecteur<double> &V) const
{
	if (m != V.dim)
	{
		cout << "Les dimensions ne correspondent pas. \n";
		exit(1);
	}
	Vecteur<double> temp(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			temp.val[i] += val[i][j] * V.val[j];
		}
	}
	return temp;
};

Matrice Matrice::operator*(const double nb) const
{
	Matrice tmp(n, m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			tmp.val[i][j] = val[i][j] * nb;

	return tmp;
};

Matrice Matrice::operator/(const double nb) const
{
	Matrice tmp(n, m);
	if (nb)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				tmp.val[i][j] /= nb;
	}
	else //exception division par 0
	{
		cout << "Division par 0 \n";
		exit(1);
	}
	return tmp;
};

Matrice &Matrice::operator*=(const double nb)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			val[i][j] = val[i][j] * nb;

	return *this;
};

Matrice &Matrice::operator/=(const double nb)
{
	if (nb)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				val[i][j] /= nb;
	}
	else
	{
		cout << "Division par 0 \n";
		exit(1);
	}
	return *this;
};

Matrice &Matrice::operator+=(const Matrice &M)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			val[i][j] += M.val[i][j];

	return *this;
};

Matrice &Matrice::operator-=(const Matrice &M)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			val[i][j] -= M.val[i][j];

	return *this;
};

// Opérateurs d'affichage

void Matrice::print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << val[i][j] << " ";
		}
		cout << "\n";
	}
};

ostream &operator<<(ostream &out, const Matrice &M)
{
	if (M.val == NULL)
	{
		cout << "La matrice ne présente pas de valeur !\n";
		exit(1);
	}
	for (int i = 0; i < M.n; i++)
	{
		for (int j = 0; j < M.m; j++)
		{
			cout << M.val[i][j] << " ";
		}
		cout << "\n";
	}
	return out;
};

// Opérateurs externes

Vecteur<double> toVecteur(const Matrice &M)
{
	int dim_ = M.n * M.m;
	Vecteur<double> V(dim_);
	for (int i = 0; i < M.n; i++)
	{
		for (int j = 0; j < M.m; j++)
		{
			V.val[i * M.m + j] = M.val[i][j];
		}
	}
	return V;
};

Matrice transpose(const Matrice &M)
{
	int a = M.n;
	int b = M.m;

	Matrice T(b, a);

	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < b; j++)
		{
			T.val[j][i] = M.val[i][j];
		}
	}
	return T;
}

double Matrice::norm()
{
	double norme = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			norme += val[i][j] * val[i][j];
		}
	}
	return sqrt(norme);
}

//Matrices carrées diagonales

Matrice_diag::Matrice_diag()
{
	n = 0;
	val = 0;
};

Matrice_diag::Matrice_diag(int n_l, double valeur)
{
	n = n_l;
	val = new double [n];

	for (int i = 0; i < n; i++)
	{
		val[i] = valeur;
	}
};

Matrice_diag::~Matrice_diag()
{
	if (val != 0)
	{
		delete[] val;
		n = 0;
	}
};

ostream &operator<<(ostream &out, const Matrice_diag &M)
{
	if (M.val == NULL)
	{
		cout << "La matrice ne présente pas de valeur !\n";
		exit(1);
	}
	for (int i = 0; i < M.n; i++)
	{
		for (int j = 0; j < M.n; j++)
		{
			if (i==j)
			{
				cout << M.val[i] << " ";
			}
			else
			{
				cout << 0 << " ";
			}
		}
		cout << "\n";
	}
	return out;
}

Matrice_diag &Matrice_diag::operator=(const Matrice_diag &M)
{
	if (this != &M) //assignation M = M impossible
	{
		if (M.n != n) // si tailles pas compatibles
		{
			delete[] val;
			n = M.n;
			val = new double[n];
		}
	}

	for (int i = 0; i < n; i++)
	{
		val[i] = M.val[i];
	}
	return *this;
}

Matrice_diag Matrice_diag::operator*(const double nb) const
{
	Matrice_diag tmp(n, 0);
	for (int i = 0; i < n; i++)
		tmp.val[i] = val[i] * nb;

	return tmp;
};

Vecteur<double> Matrice_diag::operator*(const Vecteur<double> &V) const
{
	if (n != V.dim)
	{
		cout << "Les dimensions ne correspondent pas. \n";
		exit(1);
	}
	Vecteur<double> temp(n);
	for (int i = 0; i < n; i++)
	{
		temp.val[i] += val[i] * V.val[i];
	}
	return temp;
};
