#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <math.h>
#include "creationtroncon.h"
#pragma warning(disable : 4996)
using namespace std;

void pixelx(double &coord,int x) {
	coord = (x / (2.367687 - 2.337131)) * (coord - 2.337131);
}
void pixely(double& coord,int y) {
	coord = (y / (48.838197 - 48.851354)) * (coord - 48.851354);
}

vector<vector<double>> convertion_initiale(string & ligne,int x, int y) {
	size_t i = 1;
	char mot = ']';
	char mot2 = ',';
	char mot3 = ' ';
	string nbre = "";
	vector<double> coord(3, 0.0);
	vector<vector<double>> liste;
	while (i < ligne.size()) {
		nbre = "";
		while (ligne[i] != mot2) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int n = nbre.length() + 1;
		char* numb = new char[n];
		strcpy(numb, nbre.c_str());
		coord[0] = atof(numb);
		//pixelx(coord[0],x);
		i = i + 2;
		nbre = "";
		while (ligne[i] != mot) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int m = nbre.length() + 1;
		char* num = new char[m];
		strcpy(num, nbre.c_str());
		coord[1] = atof(num);
		//pixely(coord[1],y);
		i = i + 4;
		nbre = "";
		/*while (ligne[i] != mot3) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int o = nbre.length() + 1;
		char* num1 = new char[o];
		strcpy(num1, nbre.c_str());
		coord[2] = atof(num1);
		i = i + 2;*/
		liste.push_back(coord);
	}

	return liste;
}

vector<vector<double>> convertion(string& ligne, int x, int y) {
	size_t i = 1;
	char mot = ']';
	char mot2 = ',';
	char mot3 = ' ';
	string nbre = "";
	vector<double> coord(3, 0.0);
	vector<vector<double>> liste;
	while (i < ligne.size()) {
		nbre = "";
		while (ligne[i] != mot2) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int n = nbre.length() + 1;
		char* numb = new char[n];
		strcpy(numb, nbre.c_str());
		coord[0] = atof(numb);
		pixelx(coord[0],x);
		i = i + 2;
		nbre = "";
		while (ligne[i] != mot) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int m = nbre.length() + 1;
		char* num = new char[m];
		strcpy(num, nbre.c_str());
		coord[1] = atof(num);
		pixely(coord[1],y);
		i = i + 2;
		nbre = "";
		while (ligne[i] != mot3) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int o = nbre.length() + 1;
		char* num1 = new char[o];
		strcpy(num1, nbre.c_str());
		coord[2] = atof(num1);
		i = i + 2;
		liste.push_back(coord);
	}
	return liste;
}

bool operator==(extremite& a, extremite& b)
{
	return ((a.getlat() == b.getlat()) and (a.getlon() == b.getlon()));
}

vector<vector<vector<double>>> creation_initiale(int x, int y,string & fichier) {
	ifstream monFlux(fichier.c_str());
	string ligne;
	vector<vector<vector<double>>> liste_troncon;
	if (not(monFlux)) {
		std::cout << "Il y a un probleme lors de l'ouverture de : " << fichier << endl;
	}
	while (getline(monFlux, ligne)) {
		liste_troncon.push_back(convertion_initiale(ligne,x,y));
	}
	cout << liste_troncon[0][0][0] << endl;
	return liste_troncon;
}

vector<vector<vector<double>>> creation(int x, int y, string& fichier) {
	ifstream monFlux(fichier.c_str());
	string ligne;
	vector<vector<vector<double>>> liste_troncon;
	if (not(monFlux)) {
		std::cout << "Il y a un probleme lors de l'ouverture de : " << fichier << endl;
	}
	while (getline(monFlux, ligne)) {
		liste_troncon.push_back(convertion(ligne, x, y));
	}
	cout << liste_troncon[0][0][0] << endl;
	return liste_troncon;
}

vector<double> convertion_alti_initiale (string ligne, int x, int y) {
	size_t i = 0;
	char mot = ',';
	char mot2 = ' ';
	char mot3 = ']';
	string nbre;
	vector<double> liste(3, 0.0);
	while (i < ligne.size()) {
		nbre = "";
		while (ligne[i] != mot2) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int n = nbre.length() + 1;
		char* numb = new char[n];
		strcpy(numb, nbre.c_str());
		liste[2] = atof(numb);
		
		i = i + 2;
		nbre = "";
		while (ligne[i] != mot) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int m = nbre.length() + 1;
		char* num = new char[m];
		strcpy(num, nbre.c_str());
		liste[0] = atof(num);
		//pixelx(liste[1], x);
		i = i + 2;
		nbre = "";
		while (ligne[i] != mot3) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int k = nbre.length() + 1;
		char* num1 = new char[k];
		strcpy(num1, nbre.c_str());
		liste[1] = atof(num1);
		//pixely(liste[2], y);
		i = i + 4;
	}
	return liste;
}

vector<double> convertion_alti(string ligne, int x, int y) {
	size_t i = 1;
	char mot = ',';
	char mot2 = ' ';
	char mot3 = ']';
	string nbre;
	vector<double> liste(3, 0.0);
	while (i < ligne.size()) {
		nbre = "";
		while (ligne[i] != mot) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int n = nbre.length() + 1;
		char* numb = new char[n];
		strcpy(numb, nbre.c_str());
		liste[0] = atof(numb);

		i = i + 2;
		nbre = "";
		while (ligne[i] != mot3) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int m = nbre.length() + 1;
		char* num = new char[m];
		strcpy(num, nbre.c_str());
		liste[1] = atof(num);
		//pixelx(liste[1], x);
		i = i + 2;
		nbre = "";
		while (ligne[i] != mot2) {
			nbre = nbre + ligne[i];
			i = i + 1;
		}
		int k = nbre.length() + 1;
		char* num1 = new char[k];
		strcpy(num1, nbre.c_str());
		liste[2] = atof(num1);
		//pixely(liste[2], y);
		i = i + 4;
	}
	return liste;
}

vector<vector<double>> creation_altitude_initiale(int x,int y,string & fichier) {
	ifstream monFlux(fichier.c_str());
	string ligne;
	vector<vector<double>> liste_alti;
	while (getline(monFlux, ligne)) {
		liste_alti.push_back(convertion_alti_initiale(ligne, x, y));

	}
	return liste_alti;
}

vector<vector<double>> creation_altitude(int x, int y, string& fichier) {
	ifstream monFlux(fichier.c_str());
	string ligne;
	vector<vector<double>> liste_alti;
	while (getline(monFlux, ligne)) {
		liste_alti.push_back(convertion_alti(ligne, x, y));

	}
	return liste_alti;
}

void reecriture(vector<troncon*>& liste, int taille, vector<altitude*> & alti) {
	string texte = to_string(taille);
	string debut = "Plan";
	string fin = ".txt";
	string debut2 = "Alti";
	string titre = debut + texte + fin;
	ofstream monFlux(titre.c_str());
	if (monFlux) {
		for (int a = 0; a < liste.size(); a++) {
			
			monFlux << fixed << setprecision(15) << "[" << liste[a]->debut->getlat() << ", " << liste[a]->debut->getlon() << "] " << liste[a]->debut->altit() << " [";
			for (int b = 1; b < (*liste[a]).contenu.size() - 1; b++) {
				monFlux << fixed << setprecision(15) << (*liste[a]).contenu[b].getlat() << ", " << (*liste[a]).contenu[b].getlon() << "] " << (*liste[a]).contenu[b].altit() << " [";
			}
			monFlux << fixed << setprecision(15) << liste[a]->fin->getlat() << ", " << liste[a]->fin->getlon() << "] " << liste[a]->fin->altit() << " " << endl;
		}
	}
	string titre2 = debut2 + texte + fin;
	ofstream monFlux2(titre2.c_str());
	if (monFlux) {
		for (int q = 0; q < alti.size(); q++) {
			monFlux2 << fixed << setprecision(15) << "[" << alti[q]->getlat() << ", " << alti[q]->getlon() << "] " << alti[q]->altit() << " " << endl;
		}
	}
}

void reecriture_final(vector<troncon*>& liste, int taille) {
	string texte = to_string(taille);
	string debut = "PlanFinal";
	string fin = ".txt";
	string debut2 = "Alti";
	string titre = debut + texte + fin;
	ofstream monFlux(titre.c_str());
	if (monFlux) {
		for (int a = 0; a < liste.size(); a++) {

			monFlux << "[" << to_string(liste[a]->debut->getlat()) << ", " << to_string(liste[a]->debut->getlon()) << "] " << to_string(liste[a]->debut->altit()) << " [";
			for (int b = 1; b < (*liste[a]).contenu.size() - 1; b++) {
				monFlux << to_string((*liste[a]).contenu[b].getlat()) << ", " << to_string((*liste[a]).contenu[b].getlon()) << "] " << to_string((*liste[a]).contenu[b].altit()) << " [";
			}
			monFlux << to_string(liste[a]->debut->getlat()) << ", " << to_string(liste[a]->debut->getlon()) << "] " << to_string(liste[a]->debut->altit()) << " " << endl;
		}
	}
}

void reecriture_tri(vector<troncon*>& liste) {
	string titre = "liste_troncon-tri.txt";
	ofstream monFlux(titre.c_str());
	if (monFlux) {
		for (int a = 0; a < liste.size(); a++) {

			monFlux << fixed << setprecision(15) << "["  << liste[a]->debut->getlat() << ", " << liste[a]->debut->getlon() << "] [";
			for (int b = 1; b < (*liste[a]).contenu.size() - 1; b++) {
				monFlux << fixed << setprecision(15) << to_string((*liste[a]).contenu[b].getlat()) << ", " << to_string((*liste[a]).contenu[b].getlon()) << "] [";
			}
			monFlux << fixed << setprecision(15) << to_string(liste[a]->debut->getlat()) << ", " << to_string(liste[a]->debut->getlon()) << "]" << endl;
		}
	}
}

void test(vector<extremite*>& liste, extremite*& atester) {
	bool dedans = false;
	for (int p = 0; p < liste.size(); p++) {
		if ((*atester) == (*liste[p])) {
			dedans = true;
			atester = liste[p];
		}
	}
	if (not(dedans)) {
		liste.push_back(atester);
	}
}

double disance(point* dep, point* fin) {
	double dist = sqrt(pow((*dep).getlat() - fin->getlat(), 2) + pow(dep->getlon() - fin->getlon(), 2));
	return dist;
}

void attribuer_alti(vector<troncon*>& liste, vector<altitude*>& alti, vector<extremite*>& extremit) {
	float lourd = liste.size();
	vector<bool> ttt(10, true);
	for (int a = 0; a < lourd; a++) {
		//std ::cout << "ok1" << endl;
		if (((a / lourd) > 0.1)and(ttt[0])) {
			std::cout << "10%" << endl;
			ttt[0] = false;
		}
		if (((a / lourd) > 0.2)and(ttt[1])) {
			std::cout << "20%" << endl;
			ttt[1] = false;
		}
		if (((a / lourd) > 0.3) and (ttt[2])) {
			std::cout << "30%" << endl;
			ttt[2] = false;
		}
		if (((a / lourd) > 0.4) and (ttt[3])) {
			std::cout << "40%" << endl;
			ttt[3] = false;
		}
		if (((a / lourd) > 0.5) and (ttt[4])) {
			std::cout << "50%" << endl;
			ttt[4] = false;
		}
		if (((a / lourd) > 0.6) and (ttt[5])) {
			std::cout << "60%" << endl;
			ttt[5] = false;
		}
		if (((a / lourd) > 0.7) and (ttt[6])) {
			std::cout << "70%" << endl;
			ttt[6] = false;
		}
		if (((a / lourd) > 0.8) and (ttt[7])) {
			std::cout << "80%" << endl;
			ttt[7] = false;
		}
		if (((a / lourd) > 0.9) and (ttt[8])) {
			std::cout << "90%" << endl;
			ttt[8] = false;
		}
		for (int b = 1; b < (*liste[a]).contenu.size() - 1; b++) {
			//std::cout << "ok2" << endl;
			double dist1 = 10000;
			double dist2 = 10000;
			double dist3 = 10000;
			double alti1 = 0;
			double alti2 = 0;
			double alti3 = 0;
			for (int c = 0; c < alti.size(); c++) {
				//std::cout << "ok3" << endl;
				double d = disance(alti[c], (&(*liste[a]).contenu[b]));
				if (d < dist1) {
					dist3 = dist2;
					alti3 = alti2;
					dist2 = dist1;
					alti2 = alti1;
					dist1 = d;
					alti1 = alti[c]->afficheralti();

				}
				else {
					if (d < dist2) {
						dist3 = dist2;
						alti3 = alti2;
						dist2 = d;
						alti2 = alti[c]->afficheralti();
					}
					else {
						if (d < dist3) {
							dist3 = d;
							alti3 = alti[c]->afficheralti();
						}
					}
				}
			}
			//std::cout << dist1 << " " << dist2 << " " << dist3 << endl;
			//std::cout << alti1 << " " << alti2 << " " << alti3 << endl;
			double f = (((1 / dist1) * alti1) + ((1 / dist2) * alti2) + ((1 / dist3) * alti3)) / ((1 / dist1) + (1 / dist2) + (1 / dist3));
			//std::cout << f  << endl;
			(*liste[a]).contenu[b].ajoutalt(f);

		}
	}
	for (int h = 0; h < extremit.size(); h++) {
		double dist4 = 10000;
		double dist5 = 10000;
		double dist6 = 10000;
		double alti4 = 0;
		double alti5 = 0;
		double alti6 = 0;
		for (int c = 0; c < alti.size(); c++) {
			double d = disance(alti[c], extremit[h]);
			if (d < dist4) {
				dist6 = dist5;
				alti6 = alti5;
				dist5 = dist4;
				alti5 = alti4;
				dist4 = d;
				alti4 = alti[c]->afficheralti();
			}
			else {
				if (d < dist5) {
					dist6 = dist5;
					alti6 = alti5;
					dist4 = d;
					alti4 = alti[c]->afficheralti();
				}
				else {
					if (d < dist6) {
						dist6 = d;
						alti6 = alti[c]->afficheralti();
					}
				}
			}
		}
		double g = ((1 / dist4) * alti4 + (1 / dist5) * alti5 + (1 / dist6) * alti6) / ((1 / dist4) + (1 / dist5) + (1 / dist6));
		(*extremit[h]).ajoutalt(g);

	}
}

vector<altitude*> rassembler4(vector<altitude*>& liste1, vector<altitude*>& liste2, vector<altitude*>& liste3, vector<altitude*>& liste4) {
	vector<altitude*> liste5;
	for (int a = 0; a < liste1.size(); a++) {
		liste5.push_back(liste1[a]);
	}
	for (int a = 0; a < liste2.size(); a++) {
		liste5.push_back(liste2[a]);
	}
	for (int a = 0; a < liste3.size(); a++) {
		liste5.push_back(liste3[a]);
	}
	for (int a = 0; a < liste4.size(); a++) {
		liste5.push_back(liste4[a]);
	}
	return liste5;
}


vector<altitude*> rassembler6(vector<altitude*>& liste1, vector<altitude*>& liste2, vector<altitude*>& liste3, vector<altitude*>& liste4, vector<altitude*>& liste5, vector<altitude*>& liste6) {
	vector<altitude*> liste0;
	for (int a = 0; a < liste1.size(); a++) {
		liste0.push_back(liste1[a]);
	}
	for (int a = 0; a < liste2.size(); a++) {
		liste0.push_back(liste2[a]);
	}
	for (int a = 0; a < liste3.size(); a++) {
		liste0.push_back(liste3[a]);
	}
	for (int a = 0; a < liste4.size(); a++) {
		liste0.push_back(liste4[a]);
	}
	for (int a = 0; a < liste5.size(); a++) {
		liste0.push_back(liste5[a]);
	}
	for (int a = 0; a < liste6.size(); a++) {
		liste0.push_back(liste6[a]);
	}
	return liste0;
}

vector<altitude*> rassembler9(vector<altitude*>& liste1, vector<altitude*>& liste2, vector<altitude*>& liste3, vector<altitude*>& liste4, vector<altitude*>& liste5, vector<altitude*>& liste6, vector<altitude*>& liste7, vector<altitude*>& liste8, vector<altitude*>& liste9) {
	vector<altitude*> liste0;
	for (int a = 0; a < liste1.size(); a++) {
		liste0.push_back(liste1[a]);
	}
	for (int a = 0; a < liste2.size(); a++) {
		liste0.push_back(liste2[a]);
	}
	for (int a = 0; a < liste3.size(); a++) {
		liste0.push_back(liste3[a]);
	}
	for (int a = 0; a < liste4.size(); a++) {
		liste0.push_back(liste4[a]);
	}
	for (int a = 0; a < liste5.size(); a++) {
		liste0.push_back(liste5[a]);
	}
	for (int a = 0; a < liste6.size(); a++) {
		liste0.push_back(liste6[a]);
	}
	for (int a = 0; a < liste7.size(); a++) {
		liste0.push_back(liste6[a]);
	}
	for (int a = 0; a < liste8.size(); a++) {
		liste0.push_back(liste6[a]);
	}
	for (int a = 0; a < liste9.size(); a++) {
		liste0.push_back(liste6[a]);
	}
	return liste0;
}

