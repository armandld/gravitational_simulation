#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <list>
#include "Vecteur3D.h"
#include "Dessinable.h"
#include "GenerateurAleatoire.h"
#include "SupportADessin.h"

struct champ{
    Vecteur3D pos;
    double mass;
};

const double G(0.01);

class Astre : public Dessinable{

    private:

    protected:

        //Attributs
        Vecteur3D pos;
        Vecteur3D v;
        const double m;
        const double rayon;
        Vecteur3D couleur;
        Vecteur3D a;
        double degre;
        double rotV;

        std::list<Vecteur3D> memoire;

        //Attributs de classe
        static bool affichageTrace;

        static bool affichageCouleur;

        static constexpr size_t taille_trace = 10000000;

        std::string affiche_nom() const;

    public:

        //Constructeurs, constructeur de copie, destructeur et méthode init (tirage des position et vitesses)
        Astre(Vecteur3D pos, Vecteur3D v, const double m, double rayon, Vecteur3D couleur,double degre,double rotV);

        Astre(Vecteur3D pos, Vecteur3D v, const double m,double rayon,Vecteur3D couleur);

        Astre(Vecteur3D pos, Vecteur3D v, const double m);

        Astre(Vecteur3D pos, Vecteur3D v);

        Astre(const double m,const double rayon);

        Astre();

        Astre(Astre const& autre);

        //Getters
        const Vecteur3D& getPos() const {return pos;}

        const Vecteur3D& getV() const {return v;}

        const Vecteur3D& getA() const {return a;}

        double getM() const {return m;}

        double getR() const{return rayon;}

        double getDegre() const{return degre;}

        double getRotV() const{return rotV;}

        Vecteur3D getCo()const{return couleur;}

        bool getCouleur() const {return affichageCouleur;}

        bool getTrace() const {return affichageTrace;}


        //Méthodes pour modifier l'affichage des particules dans OpenGL
        void changeCouleur(){affichageCouleur = !affichageCouleur;}

        void changeTrace(){affichageTrace = !affichageTrace;}

        virtual std::list<Vecteur3D> getMemoire() const{return memoire;}


        //Test de proximité entre deux particules
        bool proximite(Astre const& autre, double pas_espace) const;


        //Méthodes d'affichage

        void dessine_sur(SupportADessin& support) const override
        { support.dessine(*this); }



        //Méthodes de l'évolution de la particule
        virtual void evolue(double);

        void Newton(std::vector<champ> const& s);

        virtual std::unique_ptr<Astre> copie() const{
            return std::unique_ptr<Astre>(new Astre(*this));
        }

        void sat(Astre const& p, double dist,GenerateurAleatoire& tirage);

};
