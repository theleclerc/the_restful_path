#ifndef GRAPH_DISTANCE_H
#define GRAPH_DISTANCE_H
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "creationtroncon.h"
#include "convertion.h"
#include <iostream>
#include "utilitaires.h"




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


void mise_a_jour_sommet_distance(int s, std::vector<extremite*> ttlesextremites, Energie* energies, Distance* distances, double* temps, std::vector<troncon*> ttlestroncons, std::vector<int> &predecesseurs) {
    std::vector<troncon*>::iterator ita;
    for(ita = ttlestroncons.begin(); ita != ttlestroncons.end(); ita++){
        if((*ita)->debut == ttlesextremites[s]) {
            int b = sommet_to_int((*ita)->fin, ttlesextremites);
            Distance dists = distances[s];
            dists.valeur += (*ita)->longueur();
            Distance distb = distances[b];
            if (dists < distb) { 
                distances[b] = dists;
                predecesseurs[b] = s;
                std::vector<double> energie_temps = (*ita)->energie_mont();
                Energie es = energies[s];
                es.valeur += energie_temps[0];
                energies[b] = es;
                temps[b] = temps[s] + energie_temps[1];
                };
        }
        if((*ita)->fin == ttlesextremites[s]) {
            int b = sommet_to_int((*ita)->debut, ttlesextremites);
            Distance dists = distances[s];
            dists.valeur += (*ita)->longueur();
            Distance distb = distances[b];
            if (dists < distb) { 
                distances[b] = dists;
                predecesseurs[b] = s;
                std::vector<double> energie_temps = (*ita)->energie_mont();
                Energie es = energies[s];
                es.valeur += energie_temps[0];
                energies[b] = es;
                temps[b] = temps[s] + energie_temps[1];
                };
        }
    }
};

std::vector<int> chemin_min_distance(std::vector<extremite*> ttlesextremites, std::vector<troncon*> ttlestroncons, extremite* depart, extremite* arrivee, double* e, double* d, int* t_p) {
    const int N_sommets = ttlesextremites.size();
    const int N_aretes = ttlestroncons.size();
    int sdeb = sommet_to_int(depart, ttlesextremites);
    int sfin = sommet_to_int(arrivee, ttlesextremites);
    Energie* energies = new Energie[N_sommets];
    Distance* distances = new Distance[N_sommets];
    double* temps = new double[N_sommets];
    std::vector<int> P;
    std::vector<int> Pc;
    energies[sdeb] = Energie(0,false);
    distances[sdeb] = Distance(0,false);
    temps[sdeb] = 0;
    std::vector<int> predecesseurs;
    for(int i = 0; i < ttlesextremites.size(); i++) {Pc.push_back(i);predecesseurs.push_back(0);};

    while (P.size()<N_sommets) {
        int s = min_distance(Pc, distances);
        if ((s==-1) || (energies[sfin] < energies[s])) {break;}
        P.push_back(s);
        mise_a_jour_sommet_distance(s,ttlesextremites,energies, distances, temps, ttlestroncons,predecesseurs);
        int s_Pc = find(s, Pc);
        Pc.erase(Pc.begin() + s_Pc);
    }
    std::vector<int> chemin_final;
    int sommet = sfin;
    
    while(sommet != sdeb) {
        chemin_final.push_back(sommet);
        sommet = predecesseurs[sommet];
    }
    (*e) = energies[sfin].valeur;
    (*d) = distances[sfin].valeur;
    (*t_p) = floor(temps[sfin]);
    chemin_final.push_back(sdeb);
    delete[] energies;
    delete[] distances;
    delete[] temps;
    return chemin_final;
    };
#endif