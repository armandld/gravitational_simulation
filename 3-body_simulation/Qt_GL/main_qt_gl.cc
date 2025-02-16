#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  // Création du widget OpenGL
  GLWidget w(2.0, 2.0, 2.0, 0.5, 3, 1);
  int i(0);
  while (i<1){
    w.ajouteParticule(Particule_spe<Argon>());
    w.ajouteParticule(Particule_spe<Helium>());
    w.ajouteParticule(Particule_spe<Neon>());
    ++i;
  }
  w.show();
  return a.exec();
}
