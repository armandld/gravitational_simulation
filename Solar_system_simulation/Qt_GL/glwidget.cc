#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

// ======================================================================
GLWidget::GLWidget(double epsilon, QWidget* parent)
    : QOpenGLWidget(parent), AfficheCamera(0), vitesse_simulation(10),memoire_vue(QMatrix4x4()),s(epsilon)
{ chronometre.restart();}

void GLWidget::ajouteAstre(Astre const& p){
    s.ajouteParticule(p);
}

void GLWidget::ajouteSatellite(Astre& u,Astre const& t,double dist){
    s.ajouteSat(t,u,dist);
}
// ======================================================================
void GLWidget::initializeGL()
{
  vue.init();
  timerId = startTimer(20);
}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{
  /* On commance par dire sur quelle partie de la 
   * fenêtre OpenGL doit dessiner.
   * Ici on lui demande de dessiner sur toute la fenêtre.
   */
  glViewport(0, 0, width, height);

  /* Puis on modifie la matrice de projection du shader.
   * Pour ce faire on crée une matrice identité (constructeur 
   * par défaut), on la multiplie par la droite par une matrice
   * de perspective.
   * Plus de détail sur cette matrice
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Puis on upload la matrice sur le shader à l'aide de la
   * méthode de la classe VueOpenGL
   */
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        try{
            if(AfficheCamera !=0){

                vue.changeCamera(*(s.getComposant(AfficheCamera)));
                vue.memoire(memoire_vue);
            }

        }
        catch(Erreur const& e){
            if(e.code != 006) throw(Erreur{007,"Invocation de la caméra incorrecte"});
            else AfficheCamera = 0;
        }
        s.dessine_sur(vue);
    }

// ======================================================================

void GLWidget::actualise_memoire(double dir_x,double dir_y,double dir_z,double angle){
    QMatrix4x4 action_supplementaire;
    if(angle ==0){
        action_supplementaire.translate(dir_x, dir_y, dir_z);
        memoire_vue = action_supplementaire * memoire_vue;
    }
    else{
        action_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
        memoire_vue = action_supplementaire * memoire_vue;
    }
}
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(50.0);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    actualise_memoire(0.0, -1.0, 0.0,petit_angle);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    actualise_memoire(0.0, +1.0, 0.0,petit_angle);

    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    actualise_memoire(-1.0, 0.0, 0.0 ,petit_angle);

    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    actualise_memoire(+1.0, 0.0, 0.0 ,petit_angle);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    actualise_memoire(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    actualise_memoire(0.0, 0.0,  -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    actualise_memoire(petit_pas, 0.0,  0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    actualise_memoire(-petit_pas, 0.0,  0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    actualise_memoire(0.0, -petit_pas,  0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    actualise_memoire(0.0, petit_pas,  0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    actualise_memoire(0.0, 0.0, -1.0 ,petit_angle);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    actualise_memoire(0.0, 0.0, 1.0 ,petit_angle);
    break;

  case Qt::Key_Home:
    vue.initializePosition();
    break;

  case Qt::Key_C:
      s.changeCouleur();
      break;

  case Qt::Key_T:
      s.changeTrace();
      break;

  case Qt::Key_I:
      affichageInfos = !affichageInfos;
      break;

  case Qt::Key_X:
      if(AfficheCamera == 0) AfficheCamera = 1;
      else AfficheCamera = 0;
      break;

  case Qt::Key_M:
    if(s.getComposant(AfficheCamera+1)==nullptr){ AfficheCamera = 1;}
    else{ ++AfficheCamera;}
    break;

  case Qt::Key_P:
      memoire_vue.setToIdentity();
      break;

  case Qt::Key_Space:
	pause();
	break;

  case Qt::Key_1:
      vitesse_simulation = 1;
      break;

  case Qt::Key_2:
      vitesse_simulation = 2;
      break;

  case Qt::Key_3:
      vitesse_simulation = 4;
      break;

  case Qt::Key_4:
      vitesse_simulation = 10;
      break;

  case Qt::Key_5:
      vitesse_simulation = 20;
      break;

  case Qt::Key_6:
      vitesse_simulation = 40;
      break;

  case Qt::Key_7:
      vitesse_simulation = 100;
      break;

  case Qt::Key_8:
      vitesse_simulation = 200;
      break;

  case Qt::Key_9:
      vitesse_simulation = 500;
      break;
  };

  update(); // redessine
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);

    // Temps réel écoulé depuis le dernier appel, en secondes
    const double real_dt = chronometre.elapsed() / 10000.0;

    // Redémarrer le chronomètre pour le prochain appel
    chronometre.restart();

    // Calculer le temps simulé total pour cet intervalle
    const double total_simulated_dt = real_dt * vitesse_simulation;

    // Diviser en plusieurs sous-intervalles si la simulation est accélérée
    const int substeps = vitesse_simulation; // Par exemple, diviser en 10 sous-intervalles
    const double sub_dt = total_simulated_dt / substeps;

    // Exécuter la simulation pour chaque sous-intervalle
    for (int i = 0; i < substeps; ++i) {
        s.evolue(sub_dt, vue);
    }

    // Mettre à jour l'affichage
    update();
}
// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
	// dans ce cas le timer ne tourne pas alors on le lance
	timerId = startTimer(20);
	chronometre.restart();
  } else {
	// le timer tourne alors on l'arrête
	killTimer(timerId);
	timerId = 0;
  }
}
