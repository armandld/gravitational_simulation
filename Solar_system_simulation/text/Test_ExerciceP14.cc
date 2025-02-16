#include <iostream>
#include <memory>
#include <sstream>
#include "Systeme.h"
#include "Astre.h"
#include "Textviewer.h"


using namespace std;

int main() {

    TextViewer ecran(cout);

    Systeme s(1);

    Systeme& systeme(s);
    ostringstream oss;
    oss << "Le système est à l'état suivant : "<<endl;
    ecran.dessine(oss.str());
    oss.str("");
    systeme.dessine_sur(ecran);
    oss<<endl;
    ecran.dessine(oss.str());

    for(int i(0);i<15;++i){
        systeme.evolue(1,ecran);
        systeme.dessine_sur(ecran);
        oss.str("");
        oss<<endl<<"--------------------------------------------"<<endl;
        ecran.dessine(oss.str());
    }
    systeme.supprimeParticules();
    oss.str("");
    oss << "Après vidage, le système contient "
         << "les particules suivantes :" << endl;
    ecran.dessine(oss.str());
    systeme.dessine_sur(ecran);

    return 0;
}
