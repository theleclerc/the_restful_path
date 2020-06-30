#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdlib>
#include <iostream>
#include "creationtroncon.h"
#include "convertion.h"
#include <math.h>
#include "graph_distance.h"
#include "graph_energy.h"
using namespace sf;
using namespace std;


bool shape_contains_cursor(extremite * bout, Vector2f const& cursor_position) {
    return (*bout).getGlobalBounds().contains(cursor_position.x, cursor_position.y);
}

bool shape_contains_cursor2(altitude* bout, Vector2f const& cursor_position) {
    return (*bout).getglobalbounds().contains(cursor_position.x, cursor_position.y);
}

void chargement_troncon(int x, int y, string & fichier, vector<troncon*>& ttlestroncon, vector<extremite*> & ttlesextremite) {
    
    std::cout << "creation liste" << endl;
    vector<vector<vector<double>>> liste_troncon = creation(x, y, fichier);
    std::cout << "fin de la liste" << endl;
    
    for (size_t a = 0; a < liste_troncon.size(); a++) {
        int taille = liste_troncon[a].size();
        extremite* debutext = new extremite(liste_troncon[a][0][0], liste_troncon[a][0][1], liste_troncon[a][0][2]);
        extremite* finext = new extremite(liste_troncon[a][taille - 1][0], liste_troncon[a][taille - 1][1], liste_troncon[a][0][2]);
        
        test(ttlesextremite, debutext);
        test(ttlesextremite, finext);
        troncon* nvtroncon = new troncon(debutext, finext);
        
        debutext->ajout_troncon(ttlestroncon.size());
        finext->ajout_troncon(ttlestroncon.size());
        for (int v = 1; v < taille - 1; v++) {
            point* nvp = new point(liste_troncon[a][v][0], liste_troncon[a][v][1], liste_troncon[a][v][2]);
            (*nvtroncon).ajoutpoint(nvp);
        }
        (*nvtroncon).creerforme();
        ttlestroncon.push_back(nvtroncon);
    }
    std::cout << "fin chargrement troncon" << endl;

}

void chargement_alti(int x, int y, string & fichier, vector<altitude*>& ttlesalti) {
    std::cout << "debut chargement alti" << endl;
    vector<vector<double>> liste_alti;
    liste_alti = creation_altitude_initiale(x, y, fichier);
    std::cout << "fin nouvel liste" << endl;
    for (size_t a = 0; a < liste_alti.size(); a++) {
        altitude* nvalti = new altitude(liste_alti[a][0], liste_alti[a][1], liste_alti[a][2]);
        ttlesalti.push_back(nvalti);
        
    }
    std::cout << "fin chargement alti" << endl;
}

void decoupage(vector<vector<troncon*>>& nouvelle_liste, vector<vector<extremite*>>& nouvelle_extre, vector<vector<altitude*>>& nouvelle_alti, vector<troncon*>& ttlestroncon, vector<extremite*>& ttlesextremite, vector<altitude*>& ttlesalti) {
    vector<troncon*> test1;
    for (int i = 0; i < 56; i++) {
        nouvelle_liste.push_back(test1);
    }
    std::cout << nouvelle_liste.size() << endl;
    vector<int> controle;
    for (int b = 0; b < ttlestroncon.size(); b++) {
        controle.push_back(0);
    }
    std::cout << (*(*ttlestroncon[0]).debut).getlat() << endl;
    double xmin = 2.22621;
    double xmax = 2.46976;
    double ymin = 48.8156;
    double ymax = 48.9021;
    double hvert = 0.013157;
    double hhori = 0.030556;
    for (int v = 0; v < ttlestroncon.size(); v++) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                int c = j + 1;
                int d = i + 1;
                if (((*(*ttlestroncon[v]).debut).getlat() >= (xmin + i * hhori)) and ((*(*ttlestroncon[v]).debut).getlat() < (xmin + (d)*hhori)) and ((*(*ttlestroncon[v]).debut).getlon() <= (ymax - j * hvert)) and ((*(*ttlestroncon[v]).debut).getlon() > (ymax - (c)*hvert)) and (controle[v] == 0)) {
                    int w = i + 8 * j;
                    nouvelle_liste[w].push_back(ttlestroncon[v]);
                    controle[v] = 1;

                }

            }
        }
    }
    std::cout << nouvelle_liste[0].size() << endl;
    std::cout << controle[1] << endl;
    vector<extremite*> test3;
    for (int i = 0; i < 56; i++) {
        nouvelle_extre.push_back(test3);
    }
    for (int v = 0; v < ttlesextremite.size(); v++) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                int c = j + 1;
                int d = i + 1;
                if (((*ttlesextremite[v]).getlat() >= (xmin + i * hhori)) and ((*ttlesextremite[v]).getlat() < (xmin + (d)*hhori)) and ((*ttlesextremite[v]).getlon() <= (ymax - j * hvert)) and ((*ttlesextremite[v]).getlon() > (ymax - (c)*hvert))) {
                    int w = i + 8 * j;
                    nouvelle_extre[w].push_back(ttlesextremite[v]);

                }

            }
        }
    }
    vector<altitude*> test2;
    for (int i = 0; i < 56; i++) {
        nouvelle_alti.push_back(test2);
    }

    for (int v = 0; v < ttlesalti.size(); v++) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 7; j++) {
                int c = j + 1;
                int d = i + 1;
                if (((*ttlesalti[v]).getlat() >= (xmin + i * hhori)) and ((*ttlesalti[v]).getlat() < (xmin + (d)*hhori)) and ((*ttlesalti[v]).getlon() <= (ymax - j * hvert)) and ((*ttlesalti[v]).getlon() > (ymax - (c)*hvert))) {
                    int w = i + 8 * j;
                    nouvelle_alti[w].push_back(ttlesalti[v]);

                }

            }
        }
    }
    std::cout << controle.size() << endl;
    int somme = 0;
    for (int j = 0; j < controle.size(); j++) {
        somme = somme + controle[j];
    }
    std::cout << somme << endl;
}

void decalage(vector<troncon*>& ttlestroncontri, troncon*& nv, int a, int b) {
    for (int i = a; i > b; i--) {
        ttlestroncontri[i] = ttlestroncontri[i - 1];
    }
    ttlestroncontri[b] = nv;
}

void tri(vector<troncon*>& ttlestroncon, vector<troncon*>& ttlestroncontri) {
    ttlestroncontri[0] = ttlestroncon[0];
    for (int i = 1; i < ttlestroncon.size(); i++) {
        if (ttlestroncon[i]->debut->getlat() < ttlestroncontri[0]->debut->getlat()) {
            decalage(ttlestroncontri, ttlestroncon[i],i,0);
        }
        else if (ttlestroncon[i]->debut->getlat() >= ttlestroncontri[i - 1]->debut->getlat()) {
            ttlestroncontri[i] = ttlestroncon[i];
        }
        else {
            for (int e = 1; e < i; e++) {
                if (ttlestroncontri[e]->debut->getlat() > ttlestroncon[i]->debut->getlat() >= ttlestroncontri[e - 1]->debut->getlat()) {
                    e = i;
                    decalage(ttlestroncontri, ttlestroncon[i], i, e);
                }
            }
        }
    }
}

string inttostr(float a) {
    return std::to_string(a);
}

int main() {
    Image image;
    Texture text_carte;
    Sprite carte;
    Vector2u a;
    int x;
    int y;
    if (not(image.loadFromFile("Capture2.png"))) // Si le chargement du fichier a échoué
    {
        std::cout << "Erreur durant le chargement de l'image" << endl;
        return EXIT_FAILURE; // On ferme le programme
    }
    else {
        text_carte.loadFromImage(image);
        a = text_carte.getSize();
        x = a.x;
        y = a.y;
        carte = Sprite(text_carte);
        carte.setPosition(0, 0);
    }

    RenderWindow app(VideoMode(1.25 * x, y, 32), "Le quartier latin"); //pas sur que l'argument en float passe. 
    vector<troncon*> ttlestroncon;
    vector<extremite*> ttlesextremite;
    vector<altitude*> ttlesalti;
    string fichier = "liste_troncon.txt";
    string plan = "Plan";
    string txt = ".txt";
    string nbr;
    string fichier_alti = "liste_altitude.txt";

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "erreur de chargement de la police" << endl;
    }

    Text text;
    text.setFont(font);
    text.setString("Réinitialiser");
    text.setCharacterSize(24);
    text.setFillColor(Color::Black);
    text.setStyle(Text::Bold | Text::Underlined);
    text.setPosition(1.15 * x, 0.33 * y); // avant c'était text.setPosition(100.f ,100.f), mais je sais pas ce que c'est ".f"

    extremite boutonreboot = extremite(1.05 * x, 0.33 * y, 0);
    boutonreboot.reboot();

    sf::RectangleShape rectangle(sf::Vector2f(0.25 * x, y));
    rectangle.setFillColor(sf::Color(255, 255, 255));
    rectangle.setPosition( x, 0);

    sf::RectangleShape affichage(sf::Vector2f(0.18 * x, 0.24 * y));
    affichage.setFillColor(sf::Color(255,255,255));
    affichage.setOutlineColor(Color(11, 187, 11));
    affichage.setOutlineThickness(2);
    affichage.setPosition(1.10 * x, 0.66 * y);

    Text txt_distance;
    txt_distance.setFont(font);
    txt_distance.setString("Distance");
    txt_distance.setCharacterSize(18);
    txt_distance.setFillColor(Color::Blue);
    txt_distance.setStyle(Text::Bold);
    txt_distance.setPosition(1.13 * x, 0.70 * y);

    Text txt_temps;
    txt_temps.setFont(font);
    txt_temps.setString("Temps");
    txt_temps.setCharacterSize(18);
    txt_temps.setFillColor(Color::Blue);
    txt_temps.setStyle(Text::Bold);
    txt_temps.setPosition(1.13 * x, 0.78 * y);

    Text txt_energie;
    txt_energie.setFont(font);
    txt_energie.setString("Énergie");
    txt_energie.setCharacterSize(18);
    txt_energie.setFillColor(Color::Blue);
    txt_energie.setStyle(Text::Bold);
    txt_energie.setPosition(1.13 * x, 0.86 * y);


    //Création du changement de mode.
    extremite boutonenergie = extremite(1.05 * x, 0.44 * y, 0);
    boutonenergie.reboot2();
    extremite boutondistance = extremite(1.05 * x, 0.55 * y, 0);
    boutondistance.reboot3();
    
    Text txt1;
    txt1.setFont(font);
    txt1.setString("Energie");
    txt1.setCharacterSize(24);
    txt1.setPosition(1.13 * x, 0.44 * y);
    txt1.setFillColor(Color::Black);
    Text txt2;
    txt2.setFont(font);
    txt2.setString("Distance");
    txt2.setCharacterSize(24);
    txt2.setPosition(1.13 * x, 0.55 * y);
    txt2.setFillColor(Color::Black);
    bool version;
    version = true; //mode distance enclenché
    /*chargement_troncon(x, y, fichier, ttlestroncon, ttlesextremite);
    std::cout << "finchargement troncon" << endl;
    chargement_alti(x, y, fichier_alti, ttlesalti);
    std::cout << "fin chargement alti" << endl;
    std::cout << "Début découpage" << endl;
    vector<vector<troncon*>> nouvelle_liste;
    vector<vector<extremite*>> nouvelle_extre;
    vector<vector<altitude*>> nouvelle_alti;
    decoupage(nouvelle_liste, nouvelle_extre, nouvelle_alti, ttlestroncon, ttlesextremite, ttlesalti);
    std::cout << "fin découpage" << endl;
    for (int p = 0; p < nouvelle_liste.size(); p++) {
        reecriture(nouvelle_liste[p], p, nouvelle_alti[p]);
    }*/
    for (int i = 2; i < 6; i++) {
        std::cout << "ok" << endl;
        for (int j = 2; j < 6; j++) {
            nbr = to_string(i + 8 * j);
            fichier = plan + nbr + txt;
            chargement_troncon(x, y, fichier, ttlestroncon, ttlesextremite);
        }
    }
    /*string fichier_troncon = "liste_troncon.txt";
    string fichier_alti = "liste_altitude.txt";
    vector<troncon*> ttlestroncon;
    vector<extremite*> ttlesextremite;
    vector<altitude*> ttlesalti;
    std::cout << "debut chragement troncon" << endl;
    chargement_troncon(x, y, fichier_troncon, ttlestroncon, ttlesextremite);
    chargement_alti(x, y, fichier_alti, ttlesalti);
    vector<vector<troncon*>> nouvelle_liste;
    vector<vector<extremite*>> nouvelle_extre;
    vector<vector<altitude*>> nouvelle_alti;
    decoupage(nouvelle_liste, nouvelle_extre, nouvelle_alti, ttlestroncon, ttlesextremite, ttlesalti);
    for (int p = 0; p < nouvelle_liste.size(); p++) {
        reecriture(nouvelle_liste[p], p, nouvelle_alti[p]);
    }*/
    //int p = 55;
    //string fichier_troncon;
    //string fichier_alti;
    //string plan = "Plan";
    //string txt = ".txt";
    //string nb = to_string(p);
    //fichier_troncon = plan + nb + txt;
    //vector<troncon*> ttlestroncon;
    //vector<extremite*> ttlesextremite;
    //vector<altitude*> ttlesalti;
    //std::cout << "debut chragement troncon" << endl;
    //chargement_troncon(x, y, fichier_troncon, ttlestroncon, ttlesextremite);
    //int loop = 0;
    //for (int u = 0; u < 2; u++) {
    //    for (int l = 0; l < 2; l++) {
    //        //std::cout << (loop / (u + l)) << endl;
    //        string text = "Alti";
    //        string text1 = to_string(p-1-8 + u + 8 * l);
    //        string text2 = ".txt";
    //        fichier_alti = text + text1 + text2;
    //        chargement_alti(x, y, fichier_alti, ttlesalti);
    //        loop = loop + 1;
    //    }
    //}
    //attribuer_alti(ttlestroncon, ttlesalti, ttlesextremite);
    //reecriture_final(ttlestroncon, p);

    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            string fichier_alti = "";
            string text = "Alti";
            string text2 = ".txt";
            int f = i + 8 * j;
            string text3 = to_string(f);
            fichier_alti = text + text3 + text2;
            chargement_alti(x, y, fichier_alti, ttlesalti);
        }
    }
    attribuer_alti(ttlestroncon, ttlesalti, ttlesextremite);*/
    app.clear();

    std::cout << "fin" << endl;
    vector <extremite*> trajet;
    vector<extremite*> nvtrajet;
    bool unefois = true;
    bool depart_trouve = false;
    extremite* depart = nullptr;
    extremite* arrivee;
    double* e = new double;
    double* d = new double;
    int* t_p = new int;
    cout << "fin" << endl;
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            // Fen?tre ferm?e : on quitte
            if (event.type == Event::Closed)
                app.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (shape_contains_cursor((&boutonreboot), app.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }))) {
                    if (depart_trouve) {
                        for (int i = 0; i < ttlesextremite.size(); i++) { ttlesextremite[i]->definircouleur(); }
                        depart_trouve = false;
                    }
                    else { continue; }
                }
                if (shape_contains_cursor((&boutondistance), app.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }))) {
                    if (version) { continue; }
                    else {
                        boutondistance.modifiercouleur(187, 11, 11);
                        boutonenergie.modifiercouleur(255,255, 255);
                        version = true;
                    }
                }
                if (shape_contains_cursor((&boutonenergie), app.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }))) {
                    if (version) {
                        boutondistance.modifiercouleur(255, 255, 255);
                        boutonenergie.modifiercouleur(187, 11, 11);
                        version = false;
                    }
                    else { continue; }
                }
                for (int z = 0; z < ttlesextremite.size(); z++) {    
                    if (shape_contains_cursor(ttlesextremite[z], app.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })) and (not((rectangle).getGlobalBounds().contains(app.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }))))) {
                        if (depart_trouve) {   
                            if (version) {
                                arrivee = ttlesextremite[z];
                                arrivee->changercouleur();

                                clock_t temps_initial;
                                clock_t temps_final;
                                temps_initial = clock();
                                std::vector<int> chemin = chemin_min_distance(ttlesextremite, ttlestroncon, depart, arrivee, e, d, t_p);
                                temps_final = clock();
                                clock_t temps_CPU = (temps_initial - temps_final) / CLOCKS_PER_SEC * 1000;
                                txt_temps.setString("Temps"+ inttostr(temps_CPU));
                                //std::cout << "temps de calcul : " << temps_CPU << "ms" << std::endl;
                                std::cout << "chemin calculé" << std::endl;
                                for (int i = 1; i < chemin.size()-1; i++) { ttlesextremite[chemin[i]]->changercouleur(); };
                                }
                            else {
                                arrivee = ttlesextremite[z];
                                arrivee->changercouleur();
                                clock_t temps_initial;
                                clock_t temps_final;
                                temps_initial = clock();
                                std::vector<int> chemin = chemin_min_energie(ttlesextremite, ttlestroncon, depart, arrivee, e, d, t_p);
                                temps_final = clock();
                                clock_t temps_CPU = (temps_initial - temps_final) / CLOCKS_PER_SEC * 1000;
                                txt_temps.setString("Temps"+ inttostr(temps_CPU));
                                //std::cout << "temps de calcul : " << temps_CPU << "ms" << std::endl;
                                std::cout << "chemin calculé" << std::endl;
                                for (int i = 1; i < chemin.size()-1; i++) { ttlesextremite[chemin[i]]->changercouleur(); };
                            }
                        }
                        else { depart = ttlesextremite[z]; depart->changercouleur(); depart_trouve = true; }
                    }
                }
                for (size_t w = 0; w < ttlestroncon.size(); w++) {
                    (*ttlestroncon[w]).testaffichage();
                }
            }
        }

        // Efface l'?cran (remplissage avec du noir)
        app.clear();

        // Affichage de notre carre dans la fen?tre
        app.draw(carte);
        //app.draw(ane2);
        //app.draw(ane3);
        for (int j = 0; j < ttlestroncon.size(); j++) {
            app.draw((*ttlestroncon[j]).afficher());
        }
        for (int s = 0; s < ttlesextremite.size(); s++) {
            app.draw((*ttlesextremite[s]).afficher());
        }

        app.draw(rectangle);
        app.draw(affichage);
        app.draw(boutonreboot.afficher());
        app.draw(boutonenergie.afficher());
        app.draw(boutondistance.afficher());
        app.draw(text);
        app.draw(txt_distance);
        app.draw(txt_temps);
        app.draw(txt_energie);
        app.draw(txt1);
        app.draw(txt2);

        // Affichage du contenu de la fen?tre ? l'?cran
        app.display();

    }
    delete e;
    delete d;
    delete t_p;

    return 0;
}

//#include <SFML/Graphics.hpp>
//#include <cstdlib>
//#include <iostream>
//#include "creationtroncon.h"
//#include "convertion.h"
//#include "graph.h"
//using namespace sf;
//using namespace std;
//
//bool operator==(extremite& a, extremite& b) {
//    return ((a.getlat() == b.getlat()) and (a.getlon() == b.getlon()));
//};
//
//bool shape_contains_cursor(extremite* bout, Vector2f const& cursor_position) {
//    return (*bout).getGlobalBounds().contains(cursor_position.x, cursor_position.y);
//};
//
//extremite* test(vector<extremite*>& liste, extremite* atester) {
//    bool dedans = false;
//    for (int p = 0; p < liste.size(); p++) {
//        if ((*atester) == (*liste[p])) {
//            dedans = true;
//            return liste[p];
//        }
//    }
//    if (not(dedans)) {
//        liste.push_back(atester);
//    }
//    return atester;
//};
//
//int main() {
//
//    Image image;
//    Texture text_carte;
//    Sprite carte;
//    Vector2u a;
//    int x;
//    int y;
//    if (not(image.loadFromFile("Capture2.png"))) // Si le chargement du fichier a échoué
//    {
//        cout << "Erreur durant le chargement de l'image" << endl;
//        return EXIT_FAILURE; // On ferme le programme
//    }
//    else {
//        text_carte.loadFromImage(image);
//        a = text_carte.getSize();
//        x = a.x;
//        y = a.y;
//        carte = Sprite(text_carte);
//        carte.setPosition(0, 0);
//    }
//    RenderWindow app(VideoMode(x, y, 32), "Le quartier latin");
//    vector<vector<vector<double>>> liste_troncon;
//    liste_troncon = creation(x, y);
//    /* for (int k = 0; k < 50; k++) {
//
//     }*/
//    vector<vector<vector<double>>> liste_troncon_final;
//    vector<troncon*> ttlestroncon;
//    vector<extremite*> ttlesextremite;
//    bool dans_le_plan = true;
//    for (size_t a = 0; a < liste_troncon.size(); a++) {
//        dans_le_plan = true;
//        for (size_t b = 0; b < liste_troncon[a].size(); b++) {
//            if ((liste_troncon[a][b][0] <= 0.0) or (liste_troncon[a][b][0] >= x) or (liste_troncon[a][b][1] <= 0.0) or (liste_troncon[a][b][1] >= y)) {
//                dans_le_plan = false;
//            }
//        }
//        if (dans_le_plan) {
//            cout << "+1" << endl;
//            liste_troncon_final.push_back(liste_troncon[a]);
//            int taille = liste_troncon[a].size();
//            extremite* debutext = new extremite(liste_troncon[a][0][0], liste_troncon[a][0][1]);
//            extremite* finext = new extremite(liste_troncon[a][taille - 1][0], liste_troncon[a][taille - 1][1]);
//            debutext = test(ttlesextremite, debutext);
//            finext = test(ttlesextremite, finext);
//            troncon* nvtroncon = new troncon(debutext, finext);
//            debutext->ajout_troncon(ttlestroncon.size());
//            finext->ajout_troncon(ttlestroncon.size());
//            for (int v = 1; v < taille - 1; v++) {
//                point* nvp = new point(liste_troncon[a][v][0], liste_troncon[a][v][1]);
//                (*nvtroncon).ajoutpoint(*nvp);
//            }
//            (*nvtroncon).creerforme();
//            ttlestroncon.push_back(nvtroncon);
//        }
//    }
//    /*for (int k = 0; k <liste_troncon_final.size(); k++) {
//        cout << liste_troncon_final[k][0][0] << endl;
//    }*/
//
//    app.clear();
//
//    // Affichage de notre carre dans la fenêtre
//
//    cout << "fin" << endl;
//    bool depart_trouve = false;
//    extremite* depart = nullptr;
//    extremite* arrivee;
//    cout << (*ttlestroncon[0]).longueur() << endl;
//    while (app.isOpen())
//    {
//        
//        Event event;
//        while (app.pollEvent(event))
//        {
//            // Fenêtre fermée : on quitte
//            if (event.type == Event::Closed)
//                app.close();
//            else if (event.type == sf::Event::MouseButtonPressed) {
//                for (int z = 0; z < ttlesextremite.size(); z++) {
//
//                    if (shape_contains_cursor(ttlesextremite[z], app.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }))) {
//                        if (not(depart_trouve)) {
//                            depart = ttlesextremite[z];
//                            depart->changercouleur();
//                            depart_trouve = true;
//                        }
//                        else
//                        {
//                            arrivee = ttlesextremite[z];
//                            arrivee->changercouleur();
//                            cout << "debut de recherche du chemin" << endl;
//                            std::vector<int> chemin = chemin_plus_court(ttlesextremite, ttlestroncon, depart, arrivee);
//                            cout << "fin de recherche du chemin" << endl;
//                            for (int i = 0; i < chemin.size(); i++) { ttlesextremite[chemin[i]]->changercouleur(); };
//                            depart_trouve = false;
//                        }
//                    }
//                }
//                for (size_t w = 0; w < ttlestroncon.size(); w++) {
//                    (*ttlestroncon[w]).testaffichage();
//                }
//            }
//        }
//
//        // Efface l'écran (remplissage avec du noir)
//        app.clear();
//
//        // Affichage de notre carre dans la fenêtre
//        app.draw(carte);
//        //app.draw(ane2);
//        //app.draw(ane3);
//        for (int j = 0; j < ttlestroncon.size(); j++) {
//            app.draw((*ttlestroncon[j]).afficher());
//        }
//        for (int s = 0; s < ttlesextremite.size(); s++) {
//            app.draw((*ttlesextremite[s]).afficher());
//        }
//        // Affichage du contenu de la fenêtre à l'écran
//        app.display();
//
//    }
//
//
//    return 0;
//};