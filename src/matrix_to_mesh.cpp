#include"../include/matrice.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Enregistre matrice des hauteurs en fichier de maillage
void matriceToMesh(const string &fichier, const Matrice &M)
{
	ofstream mesh(fichier);
	mesh << endl;
	mesh << "MeshVersionFormatted" << endl;
	mesh << "1" << endl;
	mesh << endl;
	mesh << "Dimension" << endl;
	mesh << 3 << endl;
	mesh << endl;
	mesh << "Vertices" << endl;
	mesh << (M.n)*(M.m) << endl;

	for (int j=0; j<M.m; j++)
	{
		for (int i=0; i<M.n; i++)
		{
			mesh << i << " " << j << " " << M.val[i][j] << " " << 0 << endl;
		}
	}
	mesh << endl;
	mesh << "Quadrilaterals" << endl;
	mesh << (M.m-1)*(M.n-1) << endl;

	for (int j=0; j<M.m-1; j++)
	{
		for (int i=0; i<M.n-1; i++)
		{
			mesh << j*M.n + i + 1 << " "<< j*M.n + i + 2 << " " << (j+1)*M.n + i + 2 << " " << (j+1)*M.n + i + 1 << " " << 0 << endl;
		}
	}


};
