#include "creationtroncon.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <math.h>
#include "energie.h"
using namespace std;
using namespace sf;

point::point(double x, double y,double altitude) : lat(x), lon(y), alti(altitude){}



extremite::extremite(double x, double y,double altitude) : point(x,y,altitude) {
    //if (!mytext.loadFromFile(filePath)) // Si le chargement a �chou�
    //{
    //    cout << "Error during import " << filePath << endl; // On affiche l'erreur
    //}
    //else // Si le chargement de l'image a r�ussi
    //{
    //    //extrem.setTexture(mytext);
    //    //extrem.setTextureRect(subRect); // Sous rectangle
    //    //extrem.setPosition(position);
    //}
    forme.setOrigin(5, 5);
    forme.setPosition(lat, lon);
    forme.setOutlineColor(Color(0,0,0));
    forme.setFillColor(Color(255, 255, 255));
    forme.setOutlineThickness(2);
    clique = false;
}

CircleShape extremite::afficher() {
    return forme;
}
void extremite::changercouleur() {
    if (forme.getFillColor() == Color(255, 255, 255)) {
        forme.setFillColor(Color(0, 0, 0));
        clique = true;
    }
    else {
        forme.setFillColor(Color(255, 255, 255));
        clique = false;
    }
}
FloatRect extremite::getGlobalBounds() {
    return forme.getGlobalBounds();
}

point_milieu::point_milieu(double x, double y,double altitude) : point(x,y,altitude){}

troncon::troncon(extremite * deb, extremite * fin) :debut(deb), fin(fin) {
    contenu.push_back(*debut);
}

void troncon::ajoutpoint(point* nvp) {
    contenu.push_back(*nvp);
}


VertexArray troncon::afficher() {
    return trace;
}


void troncon::creerforme() {
    contenu.push_back(*fin);
    trace = VertexArray(LineStrip, contenu.size());
    for (size_t i = 0; i < contenu.size(); i++) {
        trace[i].position = Vector2f(contenu[i].lat, contenu[i].lon);
        trace[i].color = Color(255, 0, 0);
    }
}

void troncon::testaffichage() {
    if (((*debut).clique) and ((*fin).clique)) {
        for (size_t f = 0; f < contenu.size(); f++) {
            
            trace[f].color = Color(0, 255, 0);
        }
    }
    else {
        for (size_t f = 0; f < contenu.size(); f++) {

            trace[f].color = Color(255, 0, 0);
        }
    }
}

double troncon::longueur() {
    double longueur = 0;
    for (int i = 0;i<contenu.size()-1; i++) {
        int a = i + 1;
        longueur = longueur + sqrt(pow(contenu[a].lat - contenu[i].lat, 2) + pow(contenu[a].lon - contenu[i].lon, 2));
    }
    return longueur;
}

double* troncon::energie_mont(double W = 80, double Cx = 0.15, double f = 1, double F = 2.4) {
    double E_temps [2];
    std::vector<point>::iterator sommet;
    for(sommet = contenu.begin(); sommet != contenu.end() - 1; sommet++){
        double d = sqrt(pow(sommet->lat - (sommet + 1)->lat, 2) + pow(sommet->lon - (sommet + 1)->lon, 2));
        double* energie_temps = energie_montee(d, sommet->altit(), (sommet+1)->altit(), W, Cx, f, F);
        E_temps[0] += energie_temps[0];
        E_temps[1] += energie_temps[1];
    }
    return E_temps;
}

double* troncon::energie_mont(double W = 80, double Cx = 0.15, double f = 1, double F = 2.4) {
    double E_temps [2];
    std::vector<point>::iterator sommet;
    for(sommet = contenu.begin(); sommet != contenu.end() - 1; sommet++){
        double d = sqrt(pow(sommet->lat - (sommet + 1)->lat, 2) + pow(sommet->lon - (sommet + 1)->lon, 2));
        double* energie_temps = energie_descente(d, sommet->altit(), (sommet+1)->altit(), W, Cx, f, F);
        E_temps[0] += energie_temps[0];
        E_temps[1] += energie_temps[1];
    }
    return E_temps;
}