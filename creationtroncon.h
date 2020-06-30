#ifndef CREATIONTRONCON_H
#define CREATIONTRONCON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace sf;
class point {
friend class troncon;
public:
	point(double x, double y, double altitu);
	void ajoutalt(double altitu) {
		alti = altitu;
	}
	double getlat() {
		return lat;
	}
	double getlon() {
		return lon;
	}
	double altit() {
		return alti;
	}
protected:
	double alti = 0;
	double lat;
	double lon;
};

class extremite : public point {
friend class troncon;
private:
	
	Texture mytext;
	bool clique = false;
	std::vector<int> liste_tron;
	CircleShape forme = CircleShape(5);

public:
	
	extremite(double x, double y,double altitude);
	FloatRect getGlobalBounds();
	CircleShape afficher();
	void reboot();
	void reboot2();
	void reboot3();
	void changercouleur();
	
	void ajout_troncon(int nv_etre) {
		liste_tron.push_back(nv_etre);
	}
	void definircouleur() {
		if (forme.getFillColor() == Color(0, 0, 0)) {
			forme.setFillColor(Color(255, 255, 255));
			clique = false;
		}
	}
	void modifiercouleur(int coul, int coul2, int coul3) {
		forme.setFillColor(Color(coul, coul2, coul3));
	}
	
};
class point_milieu : public point {
public :
	point_milieu(double x, double y,double altitude);

};
class troncon {

private:
	
	
	VertexArray trace;
public:
	std::vector<point> contenu;
	extremite * debut;
	extremite * fin;
	troncon(extremite * deb, extremite * fin);
	void ajoutpoint(point*);
	VertexArray afficher();
	double longueur();
	void creerforme();
	void testaffichage();
	std::vector<double> energie_mont(double W = 80, double Cx = 0.15, double f = 1, double F = 2.4);
	std::vector<double> energie_desc(double W = 80, double Cx = 0.15, double f = 1, double F = 2.4);

};

class altitude : public point {
private :
	RectangleShape forme = RectangleShape(Vector2f(5,5));
	Texture mytext;
public :
	altitude( double x, double y,double alti) : point(x,y,alti) { 
		forme.setOrigin(5, 5);
		forme.setPosition(x, y);
		forme.setOutlineColor(Color(0, 0, 0));
		forme.setFillColor(Color((alti*255)/61.26, 0, 0));
		forme.setOutlineThickness(2);
	}
	RectangleShape afficher() {
		return forme;
	}
	FloatRect getglobalbounds() {
		return forme.getGlobalBounds();
	}
	double afficheralti() {
		return alti;
	}
	void grandir() {
		forme.setSize(forme.getSize() + Vector2f(0.1,0.1));
	}
	void annuler() {
		forme.setSize(forme.getSize() - Vector2f(0.1, 0.1));
	}
};


#endif