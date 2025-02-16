#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <sstream>
#include "Systeme.h"
#include "Dessinable.h"
#include "Astre.h"
#include "GenerateurAleatoire.h"
#include "SupportADessin.h"

using namespace std;

//****************************   SYSTEME   ****************************


//Constructeurs---------------------------------------------------------

Systeme::Systeme(double epsilon):
epsilon(epsilon),tirage(0){}


//Méthodes d'ajout/suppression de particules du système-----------------

void Systeme::ajouteParticule(Astre const& p){

    composants.push_back(p.copie());

}

void Systeme::ajouteSat(Astre const& astre,Astre& sat,double dist){
    sat.sat(astre,dist,tirage);
    composants.push_back(sat.copie());
}

//Méthodes d'évolution ------------------------------------------------



//Méthodes d'affichage--------------------------------------------------

void Systeme::dessine_sur(SupportADessin& support) const {

    if (composants.size()>0) {
    for (auto const& comp:composants) {
        comp->dessine_sur(support);
        }
    }else{
        ostringstream oss;
        oss<<"Le système est vide."<<endl;
        support.dessine(oss.str());
    }
}


//Méthode publique uniquement dédiée au changement de caméra
const std::unique_ptr<Astre>&  Systeme::getComposant(int u) const{
    static const std::unique_ptr<Astre> nullPtr = nullptr;
    if(u-1>=composants.size()) return nullPtr;
    else return composants[u-1];
}

//************************************************************************************************



vector<champ> Systeme::moy() const{
    vector<champ> res;
    for(auto const& el:composants){
        res.push_back({el->getPos(),el->getM()});
    }
    return res;
}



void Systeme::evolue(double dt,SupportADessin& ecran){
    vector<Tableau> all_candida;

    vector<champ> attraction_point(moy());

   for(size_t i(0);i<composants.size();++i){

        composants[i]->Newton(attraction_point);

        composants[i]->evolue(dt);

    }
}
