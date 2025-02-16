#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs


// ======================================================================
QMatrix4x4 VueOpenGL::dessine_partie1(){

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // passe la sphère en mode "plein"
    QMatrix4x4 matrice;
    matrice.setToIdentity();

    return matrice;
}

void VueOpenGL::dessineTracable(QMatrix4x4 const& point_de_vue, Astre const& t)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINE_STRIP);
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
    for (auto const& point : t.getMemoire()) {
    glVertex3f(point&vectx, point&vecty, point&vectz);
    }
    glEnd();
}

void VueOpenGL::dessine(Astre const& t)
{
    QMatrix4x4 matrice(dessine_partie1());

    if(t.getTrace()) dessineTracable(matrice,t);

    matrice.translate((t.getPos())&vectx, (t.getPos())&vecty, (t.getPos())&vectz);
    matrice.scale(t.getR());
    if (t.getCouleur()) {
      dessineSphere(matrice,t.getCo()&vectx,t.getCo()&vecty,t.getCo()&vectz);
    }else{
      dessineSphere(matrice,1.0,1-pow(t.getV().norme(),3)/1000,0.0);
    }

}

void VueOpenGL::dessineSphere(QMatrix4x4 const& point_de_vue,
                   double rouge, double vert, double bleu)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
    sphere.draw(prog, SommetId);                           // dessine la sphère
}

void VueOpenGL::dessine(std::string s) {}


// ======================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  sphere.initialize();
  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(-10.0, -10.0, -14.0);
  matrice_vue.rotate(90.0, 0.0, 1.0, 0.0);
}

void VueOpenGL::changeCamera(const Astre& p){
    matrice_vue.setToIdentity();
    QVector3D eye(p.getPos() & vectx  ,
                  p.getPos() & vecty ,
                  p.getPos() & vectz );

    Vecteur3D unit(p.getA().unitaire());

    unit += (p.getV().unitaire()) ^ unit;
    unit *= -5 *p.getR();

    QVector3D vecteur_constant(unit&vectx,
                               unit&vecty,
                               unit&vectz);
    eye += vecteur_constant;

    unit = p.getA().unitaire();

    matrice_vue.lookAt(
        eye,
        QVector3D(p.getPos() & vectx,
                  p.getPos() & vecty,
                  p.getPos() & vectz),
        QVector3D(unit&vectx,unit&vecty,unit&vectz)
    );
    rotate(20.0, -1.0, 0.0, 0.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

void VueOpenGL::memoire(QMatrix4x4 const& m){
    matrice_vue = m * matrice_vue;
}
// ======================================================================
/*void VueOpenGL::dessineEnceinte (QMatrix4x4 const& point_de_vue, Enceinte const& e)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  double h(
              e.getHauteur());
  double l(e.getLargeur());
  double p(e.getProfondeur());
  // Définir les sommets du cube de taille 1x1x1
  GLdouble vertices[][3] = {
      { 0, 0, 0 }, {  h, 0, 0 },
      {  h,  l, 0 }, { 0,  l, 0 },
      { 0, 0,  p }, {  h, 0,  p },
      {  h,  l,  p }, { 0,  l,  p }
  };

  GLubyte indices[] = {
      0, 1, 1, 2, 2, 3, 3, 0, // Bas
      4, 5, 5, 6, 6, 7, 7, 4, // Haut
      0, 4, 1, 5, 2, 6, 3, 7  // Piliers verticaux
  };

  // Dessiner les arêtes du cube
  glBegin(GL_LINES);
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
  for (int i = 0; i < 24; ++i) {
      glVertex3dv(vertices[indices[i]]);
  }
  glEnd();

}
*/

void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}


