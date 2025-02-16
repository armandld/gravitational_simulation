#include <QApplication>
#include "glwidget.h"

Astre Mercure({0,0,0},{0,0,0},3*pow(10,3),2,Vecteur3D(0.7,0,0));
Astre Venus({0,0,0},{0,0,0},4*pow(10,3),2.5,Vecteur3D(0.6,0.6,0));
Astre Terre({0,0,0},{0,0,0},6*pow(10,3),4,Vecteur3D(0.5,1,0.8));
Astre Mars({0,0,0},{0,0,0},5*pow(10,3),3,Vecteur3D(0.9,0,0));
Astre Jupiter({0,0,0},{0,0,0},12*pow(10,3),6,Vecteur3D(0.9,0.8,0.7));
Astre Saturne({0,0,0},{0,0,0},9*pow(10,3),5,Vecteur3D(1,1,0.2));
Astre Uranus({0,0,0},{0,0,0},6*pow(10,3),4.5,Vecteur3D(1,0.2,1));
Astre Neptune({0,0,0},{0,0,0},7*pow(10,3),4.5,Vecteur3D(0.5,0.5,0.8));

Astre Soleil({0,0,0},{0,0,0},pow(10,6),10,Vecteur3D(1,1,0));

Astre Lune({0,0,0},{0,0,0},30,1,Vecteur3D(1,1,1));

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  // Création du widget OpenGL
  GLWidget w(0.5);
  w.ajouteAstre(Soleil);
  w.ajouteSatellite(Mercure,Soleil,5*pow(10,2));
  w.ajouteSatellite(Venus,Soleil,7*pow(10,2));
  w.ajouteSatellite(Terre,Soleil,9*pow(10,2));
  w.ajouteSatellite(Mars,Soleil,11*pow(10,2));
  w.ajouteSatellite(Jupiter,Soleil,15*pow(10,2));
  w.ajouteSatellite(Saturne,Soleil,17.5*pow(10,2));
  w.ajouteSatellite(Uranus,Soleil,20*pow(10,2));
  w.ajouteSatellite(Neptune,Soleil,25*pow(10,2));
  w.ajouteSatellite(Lune,Terre,30);


  w.show();
  return a.exec();
}
