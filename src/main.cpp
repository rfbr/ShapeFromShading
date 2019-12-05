#include "../include/matrice.hpp"
#include "../include/vecteur.hpp"
#include "../include/image_factory.hpp"
#include "../include/lbfgs.hpp"
#include <cmath>
#include <ctime>
int main()
{

	// // maillage -> image 2D
	//
	// ImageFactory mesh("maillages/dragon.mesh");
	// Vecteur<double> source(3, 0); //direction de la source de lumière
	// source(3) = 1;
	// mesh.aplatir(source);
	// Matrice Image = mesh.image;
	// mesh.save2D("images/dragon2.ppm");

	// image 2D -> maillage

	Matrice Image = csvtoMatrix("images/dragon.csv");
	const clock_t begin_time = clock(); //début timer

	// Première optimisation pour récupérer les dérivées directionnelles de la hauteur
	cout << "L-BFGS de la fonctionnelle"
		 << "\n";
	Vecteur<double> x0(2 * Image.n * Image.m, 0.5);
	double eps_grad1 = 100; // condition d'arret sur le gradient de la fonctionnelle
	Vecteur<double> x = LBFGS(x0, fonctionnelle, gradientFonctionnelle, Image, eps_grad1);
	Matrice deriveHauteur = x.toMatrice(2 * Image.n, Image.m);

	// Deuxième optimisation pour calculer la hauteur en chaque pixel
	cout << "L-BFGS de la hauteur"
		 << "\n";
	Vecteur<double> h0(Image.n * Image.m, 0);
	double eps_grad2 = pow(10,-3); // condition d'arret sur le gradient de la hauteur
	Vecteur<double> y = LBFGS(h0, fonctionnelleHauteur, gradientHauteur, deriveHauteur, eps_grad2);
	Matrice rendu = y.toMatrice(Image.n, Image.m);

	// Enregistrement du maillage
	matriceToMesh("maillages/dragon.mesh", rendu);

	//affichage timer
	cout << "Temps d'exécution en seconde : "<<float( clock () - begin_time ) /  CLOCKS_PER_SEC << "\n";

	return 0;
}
