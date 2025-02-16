#pragma once
#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "glsphere.h"
#include "SupportADessin.h"
#include "Astre.h"


class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)

    void dessine(Astre const&) override;

    void dessine(std::string s) override;

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();
  void changeCamera(Astre const&);

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);
  void memoire(QMatrix4x4 const&);
  
  // méthode utilitaire offerte pour simplifier
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineSphere(QMatrix4x4 const& point_de_vue,
                     double rouge = 1.0, double vert = 1.0, double bleu = 1.0);

  void dessineTracable(QMatrix4x4 const& point_de_vue = QMatrix4x4(), Astre const& t=Astre() );
  void dessineVitesse(QMatrix4x4);


 private:

  QMatrix4x4 dessine_partie1();
  void dessine_partie2(QMatrix4x4&, Astre const&, double, double, double);

  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;

  // Caméra
  QMatrix4x4 matrice_vue;
};
