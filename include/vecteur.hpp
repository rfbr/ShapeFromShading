#ifndef __VECTEUR__
#define __VECTEUR__
#include <iostream>
#include <cmath>
#include "./matrice.hpp"
using namespace std;

template <typename T>
class Vecteur
{
  public:
    int dim;
    T *val;
    //Constructeurs
    Vecteur();
    Vecteur(int d, T x = T(0));
    Vecteur(const Vecteur &V);

    //Destructeur
    ~Vecteur();

    //Opérateurs internes
    Vecteur<T> &operator=(const Vecteur<T> &);
    Vecteur<T> &operator*=(const T);
    Vecteur<T> &operator/=(const T);
    Vecteur<T> operator^(const Vecteur<T> &);
    Vecteur<T> operator+(const Vecteur<T> &A);
    Vecteur<T> operator-(const Vecteur<T> &A);
    Vecteur<T> operator*(const T);
    Vecteur<T> concatenate(const Vecteur<T> &A);
    Matrice toMatrice(const int i, const int j) const;
    T operator*(const Vecteur<T> &);
    T &operator()(int) const;
    Vecteur<T> operator()(int, int) const;
    //Opérateur print
    template <typename type>
    friend ostream &operator<<(ostream &, const Vecteur<type> &);
    //Norme
    double norm();
};
//Opérateurs externes
//Definition des methodes

//Constructeurs
template <typename T>
Vecteur<T>::Vecteur() : dim(0), val(0){};

template <typename T>
Vecteur<T>::Vecteur(int d, T v)
{
    dim = d;
    val = new T[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = v;
    }
};

template <typename T>
Vecteur<T>::Vecteur(const Vecteur<T> &V)
{
    dim = V.dim;
    val = NULL;
    if(dim<=0) return;
    val = new T[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = V.val[i];
    }
};

//Destructeur
template <typename T>
Vecteur<T>::~Vecteur()
{
    if (val != 0)
        delete[] val;
};

//Opérations internes
template <typename T>
Vecteur<T> &Vecteur<T>::operator=(const Vecteur<T> &V)
{
    dim = V.dim;
    if (val != 0)
        delete[] val;
    val = new T[dim];
    for (int i = 0; i < dim; i++)
    {
        val[i] = V.val[i];
    }
    return *this;
};

template <typename T>
Vecteur<T> &Vecteur<T>::operator*=(const T f)
{
    for (int i = 0; i < dim; i++)
    {
        val[i] *= f;
    }
    return *this;
};

template <typename T>
Vecteur<T> &Vecteur<T>::operator/=(const T f)
{
    if (f == 0)
    {
        cout << "Erreur division par 0";
        exit(1);
    }
    for (int i = 0; i < dim; i++)
    {
        val[i] /= f;
    }
    return *this;
};

template <typename T>
T &Vecteur<T>::operator()(int i) const
{
    return val[i - 1];
};

template <typename T>
Vecteur<T> Vecteur<T>::operator()(int i, int j) const
{
    if (i >= j)
    {
        cout << "i doit 6etre strictement inférieur à j \n";
        exit(1);
    }
    int dim = j - i + 1;
    Vecteur temp(dim);
    for (int k = 0; k < dim; k++)
    {
        temp.val[k] = val[i + k];
    }
    return temp;
}
template <typename T>
Vecteur<T> Vecteur<T>::operator+(const Vecteur<T> &A)
{
    if (A.dim != this->dim)
    {
        cout << "Les vecteurs n'ont pas la même dimension. \n";
        exit(1);
    }
    Vecteur<T> C = *this;
    for (int i = 0; i < A.dim; i++)
    {
        C.val[i] += A.val[i];
    }
    return C;
};
template <typename T>
Vecteur<T> Vecteur<T>::operator-(const Vecteur<T> &A)
{
    if (A.dim != this->dim)
    {
        cout << "Les vecteurs n'ont pas la même dimension. \n";
        exit(1);
    }
    Vecteur<T> C = *this;
    for (int i = 0; i < A.dim; i++)
    {
        C.val[i] -= A.val[i];
    }
    return C;
};

template <typename T>
Vecteur<T> Vecteur<T>::operator*(const T a)
{
    Vecteur V = *this;
    for (int i = 0; i < dim; i++)
    {
        V.val[i] *= a;
    }
    return V;
};

template <typename T>
Vecteur<T> Vecteur<T>::concatenate(const Vecteur<T> &A)
{
    Vecteur C(A.dim + this->dim);
    for (int i = 0; i < this->dim; i++)
    {
        C.val[i] = this->val[i];
    }
    for (int j = 0; j < A.dim; j++)
    {
        C.val[j + this->dim] = A.val[j];
    }
    return C;
};

template <typename T>
Matrice Vecteur<T>::toMatrice(const int i, const int j)const
{
    if (i * j != dim)
    {
        cout << "Erreur de dimension \n";
        exit(1);
    }
    Matrice temp(i, j);
    for (int k = 0; k < i; k++)
    {
        for (int l = 0; l < j; l++)
        {
            temp.val[k][l] = val[l+k*j];
        }
    }
    return temp;
}

//Produit vectoriel en dimension 3
template <typename T>
Vecteur<T> Vecteur<T>::operator^(const Vecteur<T> &V)
{
    if ((dim != V.dim) || (dim > 3))
    {
        cout << "Les dimensions sont supérieures à 3 ou ne sont pas égales.\n";
        exit(1);
    }
    Vecteur<T> result(3);

    result(1) = val[1] * V(3) - val[2] * V(2);
    result(2) = val[2] * V(1) - val[0] * V(3);
    result(3) = val[0] * V(2) - val[1] * V(1);
    return result;
}

//Produit scalaire
template <typename T>
T Vecteur<T>::operator*(const Vecteur<T> &V)
{
    T result = T(0);
    for (int i = 0; i < dim; i++)
    {
        result += val[i] * V.val[i];
    }
    return result;
}

//Opérateur print
template <typename T>
ostream &operator<<(ostream &out, const Vecteur<T> &V)
{
    out << "( ";
    for (int i = 0; i < V.dim; i++)
    {
        out << V.val[i] << " ";
    }
    out << ")\n";
    return out;
};

//Norme
template <typename T>
double Vecteur<T>::norm()
{
    return sqrt(((*this) * (*this)));
};

#endif
