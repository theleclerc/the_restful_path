#ifndef CONVERTION_H
#define CONVERTION_H




#include <string>
#include <vector>

using namespace std;

void pixelx(double& coord,int x);
void pixely(double& coord,int y);

vector<vector<double>> convertion_initiale(string& ligne,int x, int y);
vector<vector<double>> convertion(string& ligne, int x, int y);
bool operator==(extremite& a, extremite& b);
vector<vector<vector<double>>> creation_initiale(int x,int y,string & fichier);
vector<vector<vector<double>>> creation(int x, int y, string& fichier);
vector<double> convertion_alti_initiale(string ligne, int x, int y);
vector<double> convertion_alti(string ligne, int x, int y);
vector<vector<double>> creation_altitude_initiale(int x, int y, string & fichier);
vector<vector<double>> creation_altitude(int x, int y, string& fichier);
void reecriture(vector<troncon*>& liste, int taille, vector<altitude*>& alti);
void reecriture_final(vector<troncon*>& liste, int taille);
void reecriture_tri(vector<troncon*>& liste);
void test(vector<extremite*>& liste, extremite*& atester);
double disance(point* dep, point* fin);
void attribuer_alti(vector<troncon*>& liste, vector<altitude*>& alti, vector<extremite*>& extremit);
vector<altitude*> rassembler4(vector<altitude*>& liste1, vector<altitude*>& liste2, vector<altitude*>& liste3, vector<altitude*>& liste4);
vector<altitude*> rassembler6(vector<altitude*>& liste1, vector<altitude*>& liste2, vector<altitude*>& liste3, vector<altitude*>& liste4, vector<altitude*>& liste5, vector<altitude*>& liste6);
vector<altitude*> rassembler9(vector<altitude*>& liste1, vector<altitude*>& liste2, vector<altitude*>& liste3, vector<altitude*>& liste4, vector<altitude*>& liste5, vector<altitude*>& liste6, vector<altitude*>& liste7, vector<altitude*>& liste8, vector<altitude*>& liste9);

#endif