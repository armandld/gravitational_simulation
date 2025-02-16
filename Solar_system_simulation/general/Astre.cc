#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <memory>
#include <list>
#include "Vecteur3D.h"
#include "Astre.h"
#include "GenerateurAleatoire.h"
#include "SupportADessin.h"

using namespace std;

//***************************   ASTRE   ***************************

// Initialisation des attributs de classe
bool Astre::affichageCouleur = true;
bool Astre::affichageTrace = false;

// Constructeurs --------------------------------------------------------
Astre::Astre(Vecteur3D pos, Vecteur3D v, const double m, double rayon, Vecteur3D couleur,double degre,double rotV):
    pos(pos), v(v), m(m), rayon(rayon),couleur(couleur),a({0,0,0}),degre(degre),rotV(rotV){}

Astre::Astre(Vecteur3D pos, Vecteur3D v, const double m, double rayon, Vecteur3D couleur)
    : pos(pos), v(v), m(m), rayon(rayon),couleur(couleur),a({0,0,0}),degre(0),rotV(0) {}

Astre::Astre(Vecteur3D pos, Vecteur3D v, const double m)
    : Astre(pos, v, m, 5,{1,0,0}) {}

Astre::Astre(Vecteur3D pos, Vecteur3D v)
    : Astre(pos, v, 20, 10,{1,0,0}) {}

Astre::Astre(const double m, const double rayon)
    : Astre({0, 0, 0}, {0, 0, 0}) {}

Astre::Astre()
    : Astre(Vecteur3D(0, 0, 0), Vecteur3D(1, 1, 1), 1) {}

// Constructeur de copie ------------------------------------------------
Astre::Astre(Astre const& autre)
    : pos(autre.pos), v(autre.v), m(autre.m), rayon(autre.rayon),couleur(autre.couleur) {}

// Méthodes d'évolution --------------------------------------------------
void Astre::evolue(double dt) {
    v+=a*dt;
    pos += dt * v;
    if (memoire.size() == taille_trace) {  // La taille de cette trace est limitée
        memoire.pop_front();
    }
    memoire.push_back(pos);
}

void Astre::Newton(std::vector<champ> const& s){
    for(auto const& el:s){
        if(el.pos != pos){
            a += ((el.mass)/((el.pos-pos).norme2()))*((el.pos-pos).unitaire());
        }
     }
    a *=G;
}

// Test de proximité entre deux astres ------------------------------
bool Astre::proximite(Astre const& autre, double pas_espace) const {
    return (pos * (1 / pas_espace)).floor() == (autre.pos * (1 / pas_espace)).floor();
}

// Méthode pour ajuster la position
void Astre::sat(Astre const& p, double dist,GenerateurAleatoire& tirage) {
    pos = p.pos + (dist + rayon) * Vecteur3D(1, 0, 0);  // Exemple avec vecteur (1,0,0)
    double t(tirage.uniforme(0,1));
    v = sqrt(G*p.getM()/dist) * Vecteur3D(0,t,sqrt(1-t*t)) + p.getV();
}
