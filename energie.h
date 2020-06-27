#ifndef ENERGIE_H
#define ENERGIE_H
#include<vector>
#include<math.h>

double* energie(double d, double p, double W = 80, double Cx = 0.15, double f = 1, double F = 2.4){
    double energie_temps [2];
    double V;
    if(p<-4) {V = 8;} //en descente vitesse de 29 km/h
    else if (p <= 4) {V = 5;} //sur le plat vitesse de 18km/h
    else {V = 3;}; //en montée vitesse de 12 km/h
    //Pour garder une force musculaire constante
    //V = sqrt(11664/250/Cx(F-3.6*((f+p)*W/36)));
    double puissance = ( f + p )*W*V/36 + 250*Cx*V*V*V/11664;
    double T = d/V;
    energie_temps[0] = T*puissance;
    energie_temps[1] = T;
    return energie_temps;
};

double* energie_montee(double d, double altitude_depart, double altitude_arrivee, double W = 80, double Cx = 0.15, double f = 1, double F = 2.4){
    if (d == 0) {double en [2]; en[0]=0;en[1]=0;return en;}
    else {
        double p = (altitude_arrivee - altitude_depart)/d;
        return energie(d, p, W, Cx, f, F);};
};

double* energie_descente(double d, double altitude_depart, double altitude_arrivee, double W = 80, double Cx = 0.15, double f = 1, double F = 2.4){
    return energie_montee(d,altitude_arrivee, altitude_depart, W, Cx, f, F);
};


double* energie(std::vector<double> distances, std::vector<double> pentes, double W = 80, double Cx = 0.15, double f = 1, double F = 2.4){
    double E_temps [2];
    for(int i = 0; i != distances.size(); i++) {
        double* energie_temps = energie(distances[i], pentes[i], W, Cx, f,F);
        E_temps[0] += energie_temps[0];
        E_temps[1] += energie_temps[1];
    };
    return E_temps;
};
#endif