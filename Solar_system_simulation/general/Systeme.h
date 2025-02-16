#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include "SupportADessin.h"
#include "Astre.h"
#include "GenerateurAleatoire.h"


typedef std::vector<size_t> Tableau;

class Systeme : public Dessinable{
	
	public:
	
        //Constructeurs, Constructeur de copie, Destructeur,...
        Systeme() = default;
	
        Systeme(double epsilon);

        //On empêche toute copie...
        Systeme(Systeme const&) = delete;
        Systeme& operator=(Systeme const&) = delete;
        Systeme(Systeme&&) = delete;
        Systeme& operator=(Systeme&&) = delete;

		//Méthodes d'ajout/suppression de particules du système
        void ajouteParticule(Astre const& p);

        void ajouteSat(Astre const& astre,Astre& sat,double dist = 0);

		void supprimeParticules(){ composants.clear();}
	
	
		//Méthode d'evolution du Système

        std::vector<champ> moy() const;

        void evolue(double,SupportADessin&);
		
		//Méthodes d'affichage
		std::ostream& afficher(std::ostream& sortie) const;
		
		void dessine_sur(SupportADessin& support) const override;

        //Méthode pour modifier l'affichage des particules dans OpenGL
        void changeCouleur(){if(composants.size() != 0) composants[0]->changeCouleur();}

        void changeTrace(){if(composants.size() != 0) composants[0]->changeTrace();}

        //Getter
        const std::unique_ptr<Astre>&  getComposant(int) const;
		
    protected:

		//Méthode intermédiaire à l'évolution du système
		void evolue_bis(std::vector<Tableau> all_candida,
						SupportADessin& ecran);
		

		//Attributs
        std::vector<std::unique_ptr<Astre>> composants;
		
		double epsilon;
		
        GenerateurAleatoire tirage;
		
		
};

std::ostream& operator<<(std::ostream& sortie, Systeme const& s);

