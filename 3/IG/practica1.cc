//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************
#define DEBUG_IG_ON
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <array>
#include <ctype.h>
#include <map>
#include <vector>

#include "objetos.h"
#include "scene_p4.h"
#include "scene_p5.h"

using namespace std;

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;
Texture *tex1;
vector<_vertex3f> perfil { {1.0, 0.0, 0},
                           {0.9, 0.1, 0},
                           {1.0, 0.2, 0},
                           {0.9, 0.3, 0},
                           {1.0, 0.4, 0},
                           {0.9, 0.5, 0},
                           {1.0, 0.6, 0},
                           {0.9, 0.7, 0},
                           {1.0, 0.8, 0},
                           {0.9, 0.9, 0},
                           {1.0, 1.0, 0},
                           {0.9, 1.1, 0},
                           {1.0, 1.2, 0},
                           {0.9, 1.3, 0},
                           {1.0, 1.4, 0},
                           {0.9, 1.5, 0},
                           {1.0, 1.6, 0},
                           {0.9, 1.7, 0},
                           {1.0, 1.8, 0},
                           {0.9, 1.9, 0},
                           {1.0, 2.0, 0},
                           {0.9, 2.1, 0},
                           {1.0, 2.2, 0},
                           {0.9, 2.3, 0},
                           {1.0, 2.4, 0},
                           {0.9, 2.5, 0},
                           {1.0, 2.6, 0},
                           {0.9, 2.7, 0},
                           {1.0, 2.8, 0},
                           {0.9, 2.9, 0},
                           {1.0, 3.0, 0},
                           {0.93, 3.4, 0},
                           {0.76, 3.6, 0},
                           {0.59, 3.7, 0},
                           {0.32, 3.75, 0},
                           {0.25, 3.75, 0},
                           {0.25, 4.1,  0}
                         };



_objeto_ply ply;
_rota_tex rota;
Scene_p4 scene;

// Objeto a pintar
_triangulos3D* toDraw;
bool normales = false;

// Variables Práctica 5
Scene_p5 scene_p5;
DrawMode draw_mode = DrawMode::ShowSeleccion;
DrawObject draw_object = DrawObject::Escena5;
  // Estáticas
  unsigned _triangulos3D::currentName = 0;
  std::vector<bool> _triangulos3D::selections;
//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
if (draw_object == DrawObject::Escena5)
    scene_p5.getCurrentCamera()->applyProjection();
else
    glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

  if (draw_object == DrawObject::Escena5)
    scene_p5.getCurrentCamera()->setViewer();
  else {
    glTranslatef(0,0,-Observer_distance);
    glRotatef(Observer_angle_x,1,0,0);
    glRotatef(Observer_angle_y,0,1,0);
  }
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************
// Jerárquico
_cilindro cilindro(1,1);
_cilindro tubo(1, 1, false, false);
_prisma_4 brazo(5,2,1.5);

double split = 0.2;

/** ESCALAS **/
// RELATIVAS A TUBO
_transform_scale soporte(0.8,4,0.8);
_transform_scale tubito(0.3,0.7,0.3);

// RELATIVAS A CILINDRO
_transform_scale base(2.5,0.4,2.5);
_transform_scale horiz(brazo.largo/2,3,brazo.largo/2);
_transform_scale conecta(brazo.largo/2, brazo.alto/2 + split, brazo.largo/2);
_transform_scale inicio_gancho(brazo.largo*0.75, brazo.alto/2 + split, brazo.largo*0.75);
_transform_scale sujeta_pinzas(tubito.getX()*2.1,1, tubito.getX()*2.1);

// RELATIVAS AL PRISMA BRAZO
// cuadrado es la parte gordita del brazo que se queda abajo si lo levantas.
_transform_scale cuadrado(0.5,1.4,1.4);
_transform_scale alarga_brazo1(0.5,1,1);
_transform_scale brazo2_s(0.5,1,1);
_transform_scale alarga_brazo2(0.75,1,1);
_transform_scale pinza(0.02, 1.15,0.46);
//_prisma_4 pinza(0.1,sujeta_pinzas.getY()*2.3,0.7);

/** ROTACIONES DE PUNTOS DE ARTICULACIÓN **/
transform_rotate brazo1(0,-55,0);
transform_rotate brazo2(0,0,55);
transform_rotate pinzas(180, 180, 225);

void draw_objects()
{

if (draw_mode < DrawMode::Plana || draw_object == DrawObject::Escena) {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT7);
}
else {
    glEnable(GL_LIGHTING);
    std::array<float, 4> ambient { 1.0, 1.0, 1.0, 1.0};
    std::array<float, 4> diffuse { 1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT7, GL_AMBIENT, ambient.data());
    glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse.data());
    glEnable(GL_LIGHT7);
}

// Colores para pintar
float r1 = 0; float g1 = 1; float b1 = 0;
float r2 = 0.3; float g2 = 0.3; float b2 = 0.3;
int grosor = 2;

if (draw_object == DrawObject::Jerarquico || draw_object == DrawObject::Escena5) {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    base.applyScale();
    cilindro.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
    if (normales)
        cilindro.draw_normales();
  glPopMatrix();
  glTranslated(0,base.getY(),0);
  glPushMatrix();
    soporte.applyScale();
    tubo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
    if (normales)
        tubo.draw_normales();
  glPopMatrix();

  glTranslated(0,soporte.getY(),0);
  glPushMatrix();
    glRotated(-90,1,0,0);
    glTranslated(0,-1,0);
    glPushMatrix();
        horiz.applyScale();
        cilindro.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
        if (normales)
            cilindro.draw_normales();
    glPopMatrix();

    // Vamos a colocar el primer brazo. No quitamos la rotación anterior para seguir en posición
    // independientemente de los cambios.
    glTranslated(0,-brazo.alto/2,0);

    glRotated(brazo1.getAngle(),0,1,0);
    brazo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
    glPushMatrix();
      glTranslated(-brazo.ancho/2,(brazo.largo*(1-cuadrado.getY()))/2,0);
      cuadrado.applyScale();
      brazo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
      if (normales)
          brazo.draw_normales();
    glPopMatrix();
    // Una vez tenemos el eje de rotación listo alargamos el brazo
    glTranslated(brazo.ancho/2+brazo.ancho*alarga_brazo1.getX()/2,0,0);
    glPushMatrix();
        alarga_brazo1.applyScale();
        brazo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
        if (normales)
            brazo.draw_normales();
    glPopMatrix();
    glTranslated(0,-split/2,0);
    glPushMatrix();
      conecta.applyScale();
      cilindro.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
      if (normales)
          cilindro.draw_normales();
    glPopMatrix();
    glTranslated(0,1,0);

    // Segundo brazo
    glTranslated(0,split,0);
    glRotated(brazo2.getAngle(),0,1,0);

    glPushMatrix();
        brazo2_s.applyScale();
        brazo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
        if (normales)
            brazo.draw_normales();
    glPopMatrix();

    glTranslated(brazo.ancho*(brazo2_s.getX() + alarga_brazo2.getX())/2,0,0);
    glPushMatrix();
        alarga_brazo2.applyScale();
        brazo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
        if (normales)
            brazo.draw_normales();
    glPopMatrix();

    // Iniciamos el soporte de las pinzas
    glTranslated(brazo.ancho*alarga_brazo2.getX()/2,-split/2,0);
    glPushMatrix();
        inicio_gancho.applyScale();
        cilindro.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
        if (normales)
            cilindro.draw_normales();
    glPopMatrix();

    glRotated(90,1,0,0);

    glRotated(brazo2.getAngle(),0,0,1);
    glTranslated(0,-inicio_gancho.getX()-tubito.getY(),-inicio_gancho.getY()/2);
    glPushMatrix();
        tubito.applyScale();
        tubo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glTranslated(0, -sujeta_pinzas.getY(),0);

    glPushMatrix();
        sujeta_pinzas.applyScale();
        cilindro.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
        if (normales)
            cilindro.draw_normales();
    glPopMatrix();


    // Pinzas

   // glTranslated(0, -pinza.alto/4,0);
    glPushMatrix();
      glRotated(90,0,1,0);
      glTranslated(-0.1, 0, 0);
      glRotated(-pinzas.getAngle(),0,0,1);
      pinza.applyScale();
      brazo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
      if (normales)
          brazo.draw_normales();
    glPopMatrix();

    glRotated(90,0,1,0);
    glTranslated(0.1, 0, 0);
    glRotated(pinzas.getAngle(),0,0,1);
    pinza.applyScale();
    brazo.draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor);
    if (normales)
        brazo.draw_normales();

  glPopMatrix();

}
else if (draw_object == DrawObject::Escena) {
    if (scene.empty())
        scene.initialize();
    scene.drawMe();
    if (normales)
      scene.drawNormales();
}
else {
    toDraw->draw(draw_mode, r1, g1, b1, r2, g2, b2, grosor, tex1);
    if (normales)
        toDraw->draw_normales();
}



}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
_triangulos3D::currentName = 1;
clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
std::ignore = x = y;
switch(Tecla1) {
case 'q': exit(0); break;
case '1': draw_object=DrawObject::Ply; toDraw = &ply; break;
case '2': draw_object=DrawObject::Rota; toDraw = &rota; break;
case '3': draw_object=DrawObject::Jerarquico; break;
case '4': draw_object=DrawObject::Escena; break;
case '5': draw_object=DrawObject::Escena5; break;
}
if (draw_object == DrawObject::Escena) switch(tolower(Tecla1)) {
    case 'a': scene.modifyBeta(1.0); break;
    case 'z': scene.modifyBeta(-1.0); break;
    case 'x': scene.modifyAlpha(1.0); break;
    case 'c': scene.modifyAlpha(-1.0); break;
}
else if (draw_object != DrawObject::Escena5) switch(Tecla1) {
    case 'p': draw_mode = DrawMode::Puntos; break;
    case 'l': draw_mode = DrawMode::Aristas; break;
    case 's': draw_mode = DrawMode::Solido; break;
    case 'a': draw_mode = DrawMode::Ajedrez; break;
    case 'r': draw_mode = DrawMode::Colores; break;
}

if (draw_object == DrawObject::Jerarquico) switch(Tecla1) {
    case 'Z': brazo1.increment(); break;
    case 'z': brazo1.decrement(); break;
    case 'X': brazo2.increment(); break;
    case 'x': brazo2.decrement(); break;
    case 'C': pinzas.increment(); break;
    case 'c': pinzas.decrement(); break;
    case 'B': brazo1.faster(); break;
    case 'b': brazo1.slower(); break;
    case 'N': brazo2.faster(); break;
    case 'n': brazo2.slower(); break;
    case 'M': pinzas.faster(); break;
    case 'm': pinzas.slower(); break;
    }
else if (draw_object == DrawObject::Escena5) switch(tolower(Tecla1)) {
    case 'w': scene_p5.getCurrentCamera()->goForwardViewer();  break;
    case 's': scene_p5.getCurrentCamera()->goBackwardViewer(); break;
    case 'a': scene_p5.getCurrentCamera()->goLeftViewer();     break;
    case 'd': scene_p5.getCurrentCamera()->goRightViewer();    break;
    case 'r': scene_p5.getCurrentCamera()->resetViewer();      break;
}

glutPostRedisplay();

}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************
int pick(int x, int y);
void special_keys(int Tecla1, int x,int y)
{
std::ignore = x = y;
if (draw_object != DrawObject::Escena5) switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
    case GLUT_KEY_F5: normales = ! normales;
}

    if (draw_object != DrawObject::Escena)
        switch(Tecla1) {
        case GLUT_KEY_F6: draw_mode = DrawMode::Plana; break;
        case GLUT_KEY_F7: draw_mode = DrawMode::Suave; break;
        case GLUT_KEY_F8: draw_mode = DrawMode::PlanaTex; break;
        case GLUT_KEY_F9: draw_mode = DrawMode::SuaveTex; break;
        }
    if (draw_object == DrawObject::Escena5) {
        switch(Tecla1) {
            case GLUT_KEY_F1: scene_p5.changeCamera(0); break;
            case GLUT_KEY_F2: scene_p5.changeCamera(1); break;
            case GLUT_KEY_F3: scene_p5.changeCamera(2); break;
        }
        change_projection();
        glFlush();
    }


glutPostRedisplay();
}

bool z = true;
bool x = false;
bool c = false;

//***************************************************************************
// Funcion de animación
//***************************************************************************
void idle() {
    if (draw_object != DrawObject::Jerarquico) return;
    int option = rand() % 3;

    switch (option) {
      case 0:
        z ? z = brazo1.decrement() : z = !brazo1.increment();
        break;
      case 1:
        x ? x = brazo2.decrement() : x = !brazo2.increment();
        break;
      case 2:
        c ? c = pinzas.decrement() : c = !pinzas.increment();
        break;
      default:
        cerr << "Error en random de función idle";
        return;
    }
    glutPostRedisplay();
}

//***************************************************************************
// Funciones de ratón de práctica 5
//***************************************************************************
enum class MouseStatus { FirstPerson, Other };
MouseStatus currentMouseStatus = MouseStatus::Other;
int previousX, previousY;

constexpr GLsizei PickBufferSize = 1044;
int analyzePickBuffer(GLint hits, const std::array<GLuint, PickBufferSize>& buffer) {

    #ifdef DEBUG_IG_ON
      std::cout << "Número de hits recibido: " << hits << '\n';
    #endif
    std::map<GLuint, GLuint> objetos;
    auto it = buffer.begin();
    for (auto i = 0; i < hits; ++i) {
        auto nItems = *it; ++it;
        auto zMin   = *it; ++it;
        auto zMax   = *it; ++it;
        #ifdef DEBUG_IG_ON
          std::cout << "Número de items: " << nItems;
          std::cout << "\t Z Mínima: " << zMin << "\t Z Máxima: " << zMax << '\n';
          std::cout << "IDENTIFICADORES DE NOMBRE: ";
        #endif

        for (auto j = 0u; j < nItems; ++j) {
            auto item = *it; ++it;
            objetos.insert({zMin, item});
            #ifdef DEBUG_IG_ON
              std::cout << item << " ";
            #endif  
        }
        #ifdef DEBUG_IG_ON
            auto cuenta = std::count(_triangulos3D::selections.begin(), _triangulos3D::selections.end(), true);
            std::cout << "Hay " << cuenta << " elementos seleccionados.\n";
            std::cout << '\n';
        #endif
    }

    if (hits == 0)
        return -1;
    else {
        auto item = objetos.begin()->second;
        _triangulos3D::selections[item] = !_triangulos3D::selections[item];
        return item;
    }
}

std::array<GLuint, PickBufferSize> pickBuffer;
int pick(int x, int y) {
  // 2 - Obtenemos los parámetros actuales del viewport
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  // 3 - Ponemos OpenGL en modo selección
  glRenderMode(GL_SELECT);

  // 4 - Fijamos la matriz de proyección para la selección
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPickMatrix(x, viewport[3] - y, 5.0, 5.0, viewport);
  scene_p5.getCurrentCamera()->applyProjection();

  // 5 - Dibujamos la escena con nombres
  glInitNames();
  glPushName(0);
  draw_mode = DrawMode::Seleccion;
  draw_scene();
  _triangulos3D::adjustToFitSelections();

  #ifdef DEBUG_IG_ON
    std::cout << "El número de nombres usados es " << _triangulos3D::currentName << '\n';
  #endif
  draw_mode = DrawMode::ShowSeleccion;

  glFlush();
  // 6 - Ponemos OpenGL en modo render (Devuelve los hits obtenidos)
  GLint hits = glRenderMode(GL_RENDER);


  // 7 - Reestablecemos la transformación de proyección
  change_projection();
  // 8 - Analizamos el buffer de selección y devolvemos el resultado
  return analyzePickBuffer(hits, pickBuffer);

}

void clickRaton(int boton, int estado, int x, int y)
{
  if (draw_object == DrawObject::Escena5)
    if (boton == GLUT_LEFT_BUTTON) {
        if (estado == GLUT_UP)
            pick(x,y);
        currentMouseStatus = MouseStatus::Other;
        glutPostRedisplay();
    }
    if (boton == GLUT_RIGHT_BUTTON)
        if (estado == GLUT_DOWN) {
            previousX = x;
            previousY = y;
            currentMouseStatus = MouseStatus::FirstPerson;
        }
        else
            currentMouseStatus = MouseStatus::Other;
    else
        currentMouseStatus = MouseStatus::Other;

}

void ratonMovido(int x, int y) {
    if (draw_object == DrawObject::Escena5)
    if (currentMouseStatus == MouseStatus::FirstPerson) {
        scene_p5.getCurrentCamera()->turn(x - previousX, previousY - y);
        previousX = x;
        previousY = y;
        glutPostRedisplay();
    }

}

//***************************************************************************
// Funcion de inicializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);
srand(time(NULL));

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 5");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// asignación de función de animación
brazo1.setSpeed(0.25);
brazo2.setSpeed(1.5);
pinzas.setSpeed(0.75);
glutIdleFunc(idle);
//***********************************
ply.parametros(argv[1]);
rota.parametros(perfil, 30, false, false);
toDraw = nullptr;
tex1 = new Texture("text-lata-1.jpg", true);
// funcion de inicialización
initialize();

// asignación de funciones de control del ratón y buffer de selección (Práctica 5)
glutMouseFunc( clickRaton );
glutMotionFunc( ratonMovido );
// 1 - Declaramos el buffer de selección

glSelectBuffer(PickBufferSize, pickBuffer.data());
// inicio del bucle de eventos
glutMainLoop();
return 0;
}
