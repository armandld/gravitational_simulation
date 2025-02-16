#pragma once
#include <iostream>
#include <string>

//On pré déclare les classes essentielles au code ici, pour éviter
//les dépendances cycliques
class Astre;

class Systeme;

class SupportADessin {

	public:

        //Constructeur, Destructeur et Constructeur de copie
        SupportADessin() = default;

        //On empêche toute copie...
        SupportADessin(SupportADessin const&) = delete;
        SupportADessin& operator=(SupportADessin const&) = delete;
        SupportADessin(SupportADessin&&) = delete;
        SupportADessin& operator=(SupportADessin&&) = delete;

        // on suppose ici que les supports ne seront ni copiés ni déplacés
	
        virtual void dessine(Astre const&) = 0;
        virtual void dessine(std::string) = 0;
	
};
