#ifndef GRAPH2_H
#define GRAPH2_H
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "creationtroncon.h"
#include "convertion.h"
#include <iostream>

void trouver_pred(int sommet, int sdeb, std::vector<int>* cheminfinal, std::vector<extremite*> ttlesextremites, std::vector<int> predecesseur){};

class Distance{
public:
    double valeur;
    bool isinf;
    Distance () : valeur(0), isinf(true) {};
    Distance (double v) {if (v<0) {isinf = true; valeur = 0;} else {isinf = false; valeur = v;}};
    Distance (double v, bool infini) : isinf(infini) {if (infini or v<0) {valeur = 0;} else {valeur = v;}}
    //Distance operator+=(Distance a) {return Distance(a.valeur + valeur, a.isinf and isinf);};
};

Distance operator+(Distance a, Distance b) {return Distance(a.valeur + b.valeur, a.isinf and b.isinf);}
bool operator<(Distance a, Distance b) {
    if (a.isinf) {return false;}
    else if (b.isinf) {return true;}
    else {return a.valeur < b.valeur;};
};


int min_distance(std::vector<int> Pc, Distance* distances) {
    Distance min(-1);
    int s = -1;
    for(int i = 0; i < Pc.size(); i++) {
        if(distances[Pc[i]] < min) {
            min = distances[Pc[i]];
            s = Pc[i];
        };
    };
    return s;
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
}

void mise_a_jour_sommet(int s, std::vector<extremite*> ttlesextremites, Distance* distances, std::vector<troncon*> ttlestroncons, std::vector<int> &predecesseurs) {
    std::vector<troncon*>::iterator ita;
    for(ita = ttlestroncons.begin(); ita != ttlestroncons.end(); ita++){
        if((*ita)->debut == ttlesextremites[s]) {
            int b = sommet_to_int((*ita)->fin, ttlesextremites);
            Distance ds = distances[s];
            ds.valeur += (*ita)->longueur();
            Distance db = distances[b];
            if (ds < db) { distances[b] = ds; predecesseurs[b] = s;};
        }
        if((*ita)->fin == ttlesextremites[s]) {
            int b = sommet_to_int((*ita)->debut, ttlesextremites);
            Distance ds = distances[s];
            ds.valeur += (*ita)->longueur();
            Distance db = distances[b];
            if (ds < db) { distances[b] = ds; predecesseurs[b] = s;};
        }
    }
};

std::vector<int> chemin_plus_court(std::vector<extremite*> ttlesextremites, std::vector<troncon*> ttlestroncons, extremite* depart, extremite* arrivee) {
    const int N_sommets = ttlesextremites.size();
    const int N_aretes = ttlestroncons.size();
    int sdeb = sommet_to_int(depart, ttlesextremites);
    int sfin = sommet_to_int(arrivee, ttlesextremites);
    Distance* distances = new Distance[N_sommets];
    std::vector<int> P;
    std::vector<int> Pc;
    distances[sdeb] = Distance(0,false);
    std::vector<int> predecesseurs;
    for(int i = 0; i < ttlesextremites.size(); i++) {Pc.push_back(i);predecesseurs.push_back(0);};

    while (P.size()<N_sommets) {
        int s = min_distance(Pc, distances);
        P.push_back(s);
        mise_a_jour_sommet(s,ttlesextremites,distances,ttlestroncons,predecesseurs);
        int s_Pc = find(s, Pc);
        Pc.erase(Pc.begin() + s_Pc);
    }
    std::vector<int> chemin_final;
    int sommet = sfin;
    
    while(sommet != sdeb) {
        chemin_final.push_back(sommet);
        sommet = predecesseurs[sommet];
    }
    std::cout << "Distance totale : " << distances[sfin].valeur << std::endl;
    chemin_final.push_back(sdeb);
    delete[] distances;
    return chemin_final;
    };
#endif