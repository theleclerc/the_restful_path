#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "creationtroncon.h"
#include "convertion.h"
#include <iostream>


void trouver_pred(int sommet, int sdeb, std::vector<int>* cheminfinal, std::vector<extremite*> ttlesextremites, std::vector<int> predecesseur){};

class Energie{
public:
    double valeur;
    bool isinf;
    Energie () : valeur(0), isinf(true) {};
    Energie (double v) {if (v<0) {isinf = true; valeur = 0;} else {isinf = false; valeur = v;}};
    Energie (double v, bool infini) : isinf(infini) {if (infini or v<0) {valeur = 0;} else {valeur = v;}}
    //Energie operator+=(Energie a) {return Energie(a.valeur + valeur, a.isinf and isinf);};
};

class Distance{
public:
    double valeur;
    bool isinf;
    Distance () : valeur(0), isinf(true) {};
    Distance (double v) {if (v<0) {isinf = true; valeur = 0;} else {isinf = false; valeur = v;}};
    Distance (double v, bool infini) : isinf(infini) {if (infini or v<0) {valeur = 0;} else {valeur = v;}}
    //Distance operator+=(Distance a) {return Distance(a.valeur + valeur, a.isinf and isinf);};
};

Energie operator+(Energie a, Energie b) {return Energie(a.valeur + b.valeur, a.isinf and b.isinf);}
bool operator<(Energie a, Energie b) {
    if (a.isinf) {return false;}
    else if (b.isinf) {return true;}
    else {return a.valeur < b.valeur;};
};

Distance operator+(Distance a, Distance b) {return Distance(a.valeur + b.valeur, a.isinf and b.isinf);}
bool operator<(Distance a,Distance b) {
    if (a.isinf) {return false;}
    else if (b.isinf) {return true;}
    else {return a.valeur < b.valeur;};
};


int sommet_to_int(extremite* sommet, std::vector<extremite*> ttlesextremites) {
    for(int i = 0; i < ttlesextremites.size(); i++) {
        if (ttlesextremites[i] == sommet) {return i;}
    };
};
int find(int s, std::vector<int> Pc) {
    for(int i = 0; i<Pc.size();i++) {
        if (Pc[i] == s) {return i;}
    }
};

#endif