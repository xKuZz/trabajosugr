#ifndef _OBJETOS_H
#define _OBJETOS_H
//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <array>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <ctime>
#include "file_ply_stl.h"
#include "transform_helpers.h"
#include "textura.h"
#include "rgb.h"

using namespace std;

// Modos de pintar
enum class DrawMode { Aristas, Puntos, Solido, Ajedrez, ShowSeleccion, Seleccion, Colores,
                      Normales, Plana, Suave, PlanaTex, SuaveTex};

// Objetos a pintar
enum class DrawObject { Ply, Rota, Jerarquico, Escena, Escena5 };

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);
void    vertice_en(unsigned pos, float x, float y, float z);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void    draw(DrawMode mode, float r1, float g1, float b1, float r2, float g2,
             float b2, int grosor, Texture* tex = nullptr);
void    draw_caras_colores_distintos();
void    draw_iluminacion_plana();
void    draw_iluminacion_suave();
void    draw_iluminacion_plana_tex(Texture* tex = nullptr);
void    draw_iluminacion_suave_tex(Texture* tex = nullptr);
void    draw_normales();
void    inicializar_colores();
void    calcularNormalesVertices();
void    calcularNormalesCaras();
void    calcularTexels();
void    cara_en(unsigned pos, int x, int y, int z);
array<float, 4> getPlanoS() const;
array<float, 4> getPlanoT() const;

/**    PRÁCTICA 5    **/
static unsigned currentName;
void   draw_select();
void   draw_selected_color(const RGBColor &selected, const RGBColor &notSelected);
static std::vector<bool> selections;
static void adjustToFitSelections();

/** **************** **/

protected:
vector<_vertex3i> caras;
vector<_vertex3f> color;
vector<_vertex3f> normalesVertices;
vector<_vertex3f> normalesCaras;
vector<Texel> texels;
array<float, 4> planoS { {1.0, 0.0, 0.0, 0.0} };
array<float, 4> planoT { {0.0, 1.0, 0.0, 0.0} };

};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
    // Modificación
    _cubo(float tam, int desp_x, int desp_y, int desp_z);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase para objetos ply
//*************************************************************************

class _objeto_ply: public _triangulos3D {
public:
    _objeto_ply();

void parametros(char* archivo);
double maxX, maxY, minX, minY;
};

//*************************************************************************
// clase para objetos por revolución
//*************************************************************************

class _rotacion: public _triangulos3D {
public:
    _rotacion();
    void parametros(const vector<_vertex3f>& perfil1, unsigned num1, bool tapaSuperior = true, bool tapaInferior = true);
    void read(const char *rute, unsigned n_rotations, bool tapaSuperior = true, bool tapaInferior = true);
vector<_vertex3f> perfil;
unsigned n_rotaciones;


};

//*************************************************************************
// clases para el modelo jerárquico
//*************************************************************************
class _cilindro: public _rotacion {
public:
    double anchura, altura;

    _cilindro(double anchura, double altura, bool tapaSuperior = true, bool tapaInferior = true);

    void crearPerfil();
};

class _prisma_4: public _triangulos3D {
public:
  double ancho, alto, largo;

  double rotacion;
  _prisma_4(double ancho,double alto, double largo);
};

//*************************************************************************
// clases rotación con texturas
//*************************************************************************
class _rota_tex: public _triangulos3D {
public:
    void parametros(const vector<_vertex3f>& perfil1, unsigned num1, bool tapaSuperior = true, bool tapaInferior = true);
    void read(const char *rute, unsigned n_rotations, bool tapaSuperior = true, bool tapaInferior = true);
    void adjustPlanes();
private:
    vector<_vertex3f> perfil;
    unsigned n_rotaciones;
};

#endif // _OBJETOS_H

