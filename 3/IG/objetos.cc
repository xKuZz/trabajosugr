#include "objetos.h"

// Aplica la función pasada al principio a todos los argumentos
template <class F, class... Args>
void for_each_argument(F f, Args&&... args) {
    [](...){}((f(std::forward<Args>(args)), 0)...);
}

// Constructor vacío
_puntos3D::_puntos3D() {}

// Dibujar los puntos 3D, Entrada colores y tamaño

void _puntos3D::draw_puntos(float r, float g, float b, int grosor) {
    glPointSize(grosor);
    glColor3f(r,g,b);
    glBegin(GL_POINTS);

    for (unsigned i = 0; i < vertices.size(); ++i)
        glVertex3fv((GLfloat*) &vertices[i]);

    glEnd();

}

void _puntos3D::vertice_en(unsigned pos, float x, float y, float z)
{
    vertices[pos].x = x;
    vertices[pos].y = y;
    vertices[pos].z = z;
}



_triangulos3D::_triangulos3D() {}

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(grosor);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();


}

void _triangulos3D::draw_solido(float r, float g, float b)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();

}

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        if (i % 2 == 0)
            glColor3f(r1,g1,b1);
        else
            glColor3f(r2,g2,b2);
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();
}

void _triangulos3D::draw(DrawMode mode, float r1, float g1, float b1, float r2, float g2, float b2, int grosor, Texture *tex)
{
    RGBColor firstColor(r1,g1,b1);
    RGBColor secondColor(r2,g2,b2);
    switch (mode) {
    case DrawMode::Aristas:
        draw_aristas(r1,g1,b1,grosor);
        break;
    case DrawMode::Puntos:
        draw_puntos(r1,g1,b1,grosor);
        break;
    case DrawMode::Solido:
        draw_solido(r1,g1,b1);
        break;
    case DrawMode::Ajedrez:
        draw_solido_ajedrez(r1,g1,b1,r2,g2,b2);
        break;
    case DrawMode::Colores:
        draw_caras_colores_distintos();
        break;
    case DrawMode::Plana:
        draw_iluminacion_plana();
        break;
    case DrawMode::Suave:
        draw_iluminacion_suave();
        break;
    case DrawMode::PlanaTex:
        draw_iluminacion_plana_tex(tex);
        break;
    case DrawMode::SuaveTex:
        draw_iluminacion_suave_tex(tex);
        break;
    case DrawMode::Normales:
        draw_normales();
        break;

    case DrawMode::Seleccion: // Práctica 5
        draw_select();
        break;
    case DrawMode::ShowSeleccion:
        draw_selected_color(firstColor, secondColor);
        break;
    default:
        cerr << "Tipo desconocido\n";
        break;
    }
}

void _triangulos3D::draw_caras_colores_distintos()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        glColor3f(color[i].x, color[i].y, color[i].z);
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();

}

void _triangulos3D::draw_iluminacion_plana()
{
    if (normalesCaras.empty())
        calcularNormalesCaras();

    glShadeModel(GL_FLAT);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for (unsigned i = 0; i < caras.size(); ++i) {
        glNormal3fv((GLfloat*) &normalesCaras[i]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }

    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
}

void _triangulos3D::draw_iluminacion_suave()
{
    if (normalesVertices.empty())
        calcularNormalesVertices();

    glEnable(GL_LIGHTING);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for (const auto& cara: caras) {
        glNormal3fv((GLfloat*) &normalesVertices[cara._0]);
        glVertex3fv((GLfloat*)         &vertices[cara._0]);
        glNormal3fv((GLfloat*) &normalesVertices[cara._1]);
        glVertex3fv((GLfloat*)         &vertices[cara._1]);
        glNormal3fv((GLfloat*) &normalesVertices[cara._2]);
        glVertex3fv((GLfloat*)         &vertices[cara._2]);
    }

    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);

}

void _triangulos3D::draw_iluminacion_plana_tex(Texture* tex)
{
    if (normalesCaras.empty())
        calcularNormalesCaras();

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
    glEnable(GL_NORMALIZE);
    if (tex) {
        tex->setPlanes(planoS, planoT);
        tex->enable();
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    if (glIsEnabled(GL_TEXTURE_GEN_S))
        for (unsigned i = 0; i < caras.size(); ++i) {
            glNormal3fv((GLfloat*) &normalesCaras[i]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
            glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
        }

    else
        for (unsigned i = 0; i < caras.size(); ++i) {
          glNormal3fv((GLfloat*) &normalesCaras[i]);

          glTexCoord2f(texels[caras[i]._0].s,texels[caras[i]._0].t);
          glVertex3fv((GLfloat*) &vertices[caras[i]._0]);

          glTexCoord2f(texels[caras[i]._1].s,texels[caras[i]._1].t);
          glVertex3fv((GLfloat*) &vertices[caras[i]._1]);

          glTexCoord2f(texels[caras[i]._2].s,texels[caras[i]._2].t);
          glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
        }


    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void _triangulos3D::draw_iluminacion_suave_tex(Texture* tex)
{
    if (normalesVertices.empty())
        calcularNormalesVertices();

    if (tex) {
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        tex->setPlanes(planoS, planoT);
        tex->enable();
    }

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    if (glIsEnabled(GL_TEXTURE_GEN_S))
      for (const auto& cara: caras) {
        glNormal3fv((GLfloat*) &normalesVertices[cara._0]);
        glVertex3fv((GLfloat*)         &vertices[cara._0]);
        glNormal3fv((GLfloat*) &normalesVertices[cara._1]);
        glVertex3fv((GLfloat*)         &vertices[cara._1]);
        glNormal3fv((GLfloat*) &normalesVertices[cara._2]);
        glVertex3fv((GLfloat*)         &vertices[cara._2]);
      }
    else
        for (auto& cara: caras) {
          glTexCoord2f(texels[cara._0].s,texels[cara._0].t);
          glNormal3fv((GLfloat*) &normalesVertices[cara._0]);
          glVertex3fv((GLfloat*)         &vertices[cara._0]);

          glTexCoord2f(texels[cara._1].s,texels[cara._1].t);
          glNormal3fv((GLfloat*) &normalesVertices[cara._1]);
          glVertex3fv((GLfloat*)         &vertices[cara._1]);

          glTexCoord2f(texels[cara._2].s,texels[cara._2].t);
          glNormal3fv((GLfloat*) &normalesVertices[cara._2]);
          glVertex3fv((GLfloat*)         &vertices[cara._2]);
        }

    glEnd();

    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void _triangulos3D::draw_normales()
{
    if (normalesVertices.empty())
        calcularNormalesVertices();
    auto t = 0.1f;

    RGBColor color(0,1,0);

    color.applyColor();

    glPointSize(1);
    glBegin(GL_LINES);

    for (auto i = 0u; i < vertices.size(); ++i) {
        _vertex3f actual = vertices[i];
        _vertex3f parametrico;

        parametrico.x = actual.x + normalesVertices[i].x * t;
        parametrico.y = actual.y + normalesVertices[i].y * t;
        parametrico.z = actual.z + normalesVertices[i].z * t;

        glVertex3fv((GLfloat*) &actual);
        glVertex3fv((GLfloat*) &parametrico);
    }

    glEnd();
}

void _triangulos3D::inicializar_colores()
{
        color.resize(caras.size());

        for (unsigned i= 0; i < color.size(); ++i) {
          bool repetido = true;

          while (repetido) {
            repetido = false;
            float color1 = (float) rand() / (float) RAND_MAX;
            float color2 = (float) rand() / (float) RAND_MAX;
            float color3 = (float) rand() / (float) RAND_MAX;

            color[i].x  = color1;
            color[i].y  = color2;
            color[i].z  = color3;

            for (unsigned j = 0; j < i && !repetido; ++j)
                if (color[i] == color[j])
                    repetido = true;
          }
        }

}

void _triangulos3D::calcularNormalesVertices()
{
    if (normalesCaras.empty())
        calcularNormalesCaras();

    normalesVertices.resize(vertices.size());
    for (auto iCara = 0u; iCara < caras.size(); ++ iCara) {
        auto A = caras[iCara]._0;
        auto B = caras[iCara]._1;
        auto C = caras[iCara]._2;

        normalesVertices[A] += normalesCaras[iCara];
        normalesVertices[B] += normalesCaras[iCara];
        normalesVertices[C] += normalesCaras[iCara];
    }
}

void _triangulos3D::calcularNormalesCaras()
{
    for (const auto& cara: caras) {
        auto p = vertices[cara._0];
        auto q = vertices[cara._1];
        auto r = vertices[cara._2];
        auto a = q - p;
        auto b = r - p;
        normalesCaras.emplace_back(a.cross_product(b).normalize());
    }
}



void _triangulos3D::cara_en(unsigned pos, int x, int y, int z)
{
    caras[pos]._0 = x;
    caras[pos]._1 = y;
    caras[pos]._2 = z;
}

array<float, 4> _triangulos3D::getPlanoS() const
{
    return planoS;
}

array<float, 4> _triangulos3D::getPlanoT() const
{
    return planoT;
}

void _triangulos3D::draw_selected_color(const RGBColor &selected, const RGBColor &notSelected)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned i = 0; i < caras.size(); ++i, ++currentName) {
        if (selections.empty() || !selections[currentName])
            notSelected.applyColor();
        else
            selected.applyColor();

        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }
    glEnd();
}

void _triangulos3D::draw_select()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    for (unsigned i = 0; i < caras.size(); ++i, ++currentName) {
        glLoadName(currentName);
        glBegin(GL_TRIANGLES);
        glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
        glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
        glEnd();
    }
}



void _triangulos3D::adjustToFitSelections()
{
    if (currentName != selections.size()) {
        std::cout << "Reajustando vector de selección\n";
        selections.clear();
        selections.shrink_to_fit();
        selections.resize(currentName, false);
    }
}

_piramide::_piramide(float tam, float al)
{
    vertices.resize(5);
    vertice_en(0, -tam,  0,  tam);
    vertice_en(1,  tam,  0,  tam);
    vertice_en(2,  tam,  0, -tam);
    vertice_en(3, -tam,  0, -tam);
    vertice_en(4,    0, al,    0);


    caras.resize(6);
    cara_en(0,  0,1,4);
    cara_en(1,  1,2,4);
    cara_en(2,  2,3,4);
    cara_en(3,  3,0,4);
    cara_en(4,  3,0,2);
    cara_en(5,  2,1,0);

    inicializar_colores();
}

_cubo::_cubo(float tam)
{
   vertices.resize(8);

   vertice_en(0,  tam,     0,  tam);
   vertice_en(1,  tam, 2*tam,  tam);
   vertice_en(2, -tam, 2*tam,  tam);
   vertice_en(3, -tam,     0,  tam);

   vertice_en(4,  tam,     0, -tam);
   vertice_en(5,  tam, 2*tam, -tam);
   vertice_en(6, -tam, 2*tam, -tam);
   vertice_en(7, -tam,     0, -tam);

   caras.resize(12);

   // Frontal
   cara_en(0,  0,2,3);
   cara_en(1,  0,1,2);

   // Derecha
   cara_en(2,  0,4,1);
   cara_en(3,  4,5,1);

   // Trasera
   cara_en(4,  7,5,4);
   cara_en(5,  6,5,7);

   // Izquierda
   cara_en(6,  3,6,7);
   cara_en(7,  3,2,6);

   // Superior
   cara_en(8,  2,1,6);
   cara_en(9,  1,5,6);

   // Inferior
   cara_en(10, 3,7,4);
   cara_en(11, 0,3,4);

   inicializar_colores();





}

// Modificación: Cubo con desplazamiento
_cubo::_cubo(float tam, int desp_x, int desp_y, int desp_z)
{

    vertices.resize(8);

    vertice_en(0,  tam + desp_x,     0 + desp_y,  tam + desp_z);
    vertice_en(1,  tam + desp_x, 2*tam + desp_y,  tam + desp_z);
    vertice_en(2, -tam + desp_x, 2*tam + desp_y,  tam + desp_z);
    vertice_en(3, -tam + desp_x,     0 + desp_y,  tam + desp_z);

    vertice_en(4,  tam + desp_x,     0 + desp_y, -tam + desp_z);
    vertice_en(5,  tam + desp_x, 2*tam + desp_y, -tam + desp_z);
    vertice_en(6, -tam + desp_x, 2*tam + desp_y, -tam + desp_z);
    vertice_en(7, -tam + desp_x,     0 + desp_y, -tam + desp_z);

    caras.resize(12);

    // Frontal
    cara_en(0,  0,2,3);
    cara_en(1,  0,1,2);

    // Derecha
    cara_en(2,  0,4,1);
    cara_en(3,  4,5,1);

    // Trasera
    cara_en(4,  7,5,4);
    cara_en(5,  6,5,7);

    // Izquierda
    cara_en(6,  3,6,7);
    cara_en(7,  3,2,6);

    // Superior
    cara_en(8,  2,1,6);
    cara_en(9,  1,5,6);

    // Inferior
    cara_en(10, 3,7,4);
    cara_en(11, 0,3,4);

    inicializar_colores();



}

_objeto_ply::_objeto_ply()
{

}

void _objeto_ply::parametros(char *archivo)
{
    _file_ply p;
    vector<float> ver_ply;
    vector<int>   car_ply;

    p.open(archivo);          // Abrimos el archivo con el lector proporcionado
    p.read(ver_ply, car_ply); // Al leerlo obtenemos un vector con puntos de vértices y otra con números para las caras

    for (auto i = 0u; i < ver_ply.size(); i+=3) // Cada 3 puntos forman un vértice que creamos y añadimos al vector de vértices
        vertices.emplace_back(ver_ply[i], ver_ply[i+1], ver_ply[i+2]);

    for (auto i = 0u; i < car_ply.size(); i+=3) // Cada 3 números se forma una cara que añadios al vector de caras
        caras.emplace_back(car_ply[i], car_ply[i+1], car_ply[i+2]);

    p.close();
    inicializar_colores();
    maxX = minX = vertices.front().x;
    maxY = minY = vertices.front().y;
    for (const auto& vertice: vertices) {
        if (maxX < vertice.x)
            maxX = vertice.x;
        if (maxY < vertice.y)
            maxY = vertice.y;
        if (minX > vertice.x)
            minX = vertice.x;
        if (minY > vertice.y)
            minY = vertice.y;
    }

    planoS[0] /= maxX - minX;
    planoT[1] /= maxY - minY;
}
_rotacion::_rotacion()
{

}

void _rotacion::parametros(const vector<_vertex3f>& perfil1, unsigned num1, bool tapaSuperior, bool tapaInferior)
{

    perfil = perfil1;
    n_rotaciones = num1;

   // TRATAMIENTO DE LOS VÉRTICES (Aplicamos la cuenta de la matriz para la rotación sobre el eje Y)
   for (auto i = 0u; i < n_rotaciones; ++i)
       for (auto& vertex: perfil)
           vertices.emplace_back(vertex.x*cos(2.0*M_PI*i/ (1.0*n_rotaciones) )+
                                 vertex.z*sin(2.0*M_PI*i/ (1.0*n_rotaciones) ),

                                 vertex.y,

                                 vertex.x*sin(2.0*M_PI*i/ (1.0*n_rotaciones) ) +
                                 vertex.z*cos(2.0*M_PI*i/ (1.0*n_rotaciones) ) );

// TRATAMIENTO DE LAS CARAS

   // Lambdas auxiliares (pa que se entienda mejor)
   // Devuelve el vértice anterior
    auto anterior = [](int actual) {
       return actual - 1;
    };
   // Devuelve la posición en el vector de vértices de el vértice actual en el siguiente perfil
    auto sig_perfil = [this] (int actual) {
       return actual + perfil.size();
    };


    _vertex3f color_par(0,0,1);
    _vertex3f color_impar(0,1,0);
    _vertex3f color_tapa_sup(1,0,0);
    _vertex3f color_tapa_inf(0,0,0);

    for (auto n_perfil = 0u; n_perfil < n_rotaciones -1; ++n_perfil)

        for (auto n_vertice = 1u; n_vertice < perfil.size(); ++n_vertice) {
            auto   actual       = n_perfil*perfil.size() + n_vertice;
            if (n_perfil % 2 == 0) {
                color.emplace_back(color_par);
                color.emplace_back(color_par);
            }
            else {
                color.emplace_back(color_impar);
                color.emplace_back(color_impar);
            }

            caras.emplace_back(actual, sig_perfil(anterior(actual)), anterior(actual) );
            caras.emplace_back(actual, sig_perfil(actual), sig_perfil(anterior(actual)));
        }

    for (auto n_vertice = 1u; n_vertice < perfil.size(); ++ n_vertice) {
        auto actual = (n_rotaciones-1)*perfil.size() + n_vertice;
        auto sig_perfil = n_vertice;

        if ((n_rotaciones - 1) % 2 == 0) {
            color.push_back(color_par);
            color.push_back(color_par);
        }
        else {
            color.push_back(color_impar);
            color.push_back(color_impar);
        }
        caras.emplace_back(actual, anterior(sig_perfil), anterior(actual));
        caras.emplace_back(actual, sig_perfil, anterior(sig_perfil) );
    }

    // Proyectar sobre el eje Y supone dejar a 0 X, Z
    auto proyeccion_y = [](const _vertex3f& v) {
        return _vertex3f(0, v.y, 0);
    };

    if (tapaInferior) {
    // TAPA INFERIOR
        vertices.emplace_back(proyeccion_y(vertices.front()));

    for (auto n_perfil = 0u; n_perfil < n_rotaciones - 1; ++n_perfil) {
        auto centro_tapa = vertices.size()-1;
        auto actual      = n_perfil * perfil.size();
        color.push_back(color_tapa_inf);
        caras.emplace_back(centro_tapa, actual, sig_perfil(actual));
    }

    // El último triángulo a mano
    color.push_back(color_tapa_inf);
    caras.emplace_back(vertices.size()-1,(n_rotaciones-1)* perfil.size(), 0);

   }

   if (tapaSuperior) {
// TAPA SUPERIOR
    vertices.emplace_back(proyeccion_y( vertices[ perfil.size() - 1 ]) );

    for (auto n_perfil = 0u; n_perfil < n_rotaciones - 1; ++ n_perfil) {
        auto centro_tapa = vertices.size()-1;
        auto actual      = n_perfil * perfil.size() + (perfil.size()-1);
        color.push_back(color_tapa_sup);
        caras.emplace_back(centro_tapa, sig_perfil(actual), actual);
    }


    color.push_back(color_tapa_sup);
    caras.emplace_back(vertices.size()-1, perfil.size()-1, n_rotaciones * perfil.size() - 1);
   }
}
/******************************************************************************************
 * CILINDRO
 ******************************************************************************************/

_cilindro::_cilindro(double anchura, double altura, bool tapaSuperior, bool tapaInferior) : anchura(anchura),
    altura(altura) {
    crearPerfil();
    parametros(perfil, 40, tapaSuperior, tapaInferior);
}

void _cilindro::crearPerfil() {
    perfil.emplace_back(anchura, 0);
    perfil.emplace_back(anchura, altura);
}

/******************************************************************************************
 * PRISMA CUADRANGULAR
 ******************************************************************************************/
_prisma_4::_prisma_4(double ancho, double alto, double largo) : ancho(ancho), alto(alto), largo(largo) {
    double x = ancho/2; double y = alto/2; double z = largo/2;

    vertices.emplace_back(x, 0, z);
    vertices.emplace_back(x, y, z);
    vertices.emplace_back(-x, y, z);
    vertices.emplace_back(-x, 0, z);
    vertices.emplace_back(x, 0, -z);
    vertices.emplace_back(x, y, -z);
    vertices.emplace_back(-x, y, -z);
    vertices.emplace_back(-x, 0, -z);

    caras.emplace_back(0,1,2);
    caras.emplace_back(2,3,0);
    caras.emplace_back(1,4,5);
    caras.emplace_back(1,0,4);
    caras.emplace_back(5,4,7);
    caras.emplace_back(5,7,6);
    caras.emplace_back(6,7,3);
    caras.emplace_back(2,6,3);
    caras.emplace_back(1,5,6);
    caras.emplace_back(2,1,6);
    caras.emplace_back(0,3,4);
    caras.emplace_back(4,7,3);

    inicializar_colores();
}

void _rota_tex::parametros(const vector<_vertex3f> &perfil1, unsigned num1, bool tapaSuperior, bool tapaInferior)
{
    perfil = perfil1;
    n_rotaciones = num1;

   // TRATAMIENTO DE LOS VÉRTICES (Aplicamos la cuenta de la matriz para la rotación sobre el eje Y)
   for (auto i = 0u; i < n_rotaciones; ++i)
       for (auto& vertex: perfil)
           vertices.emplace_back(vertex.x*cos(2.0*M_PI*i/ (1.0*n_rotaciones) )+
                                 vertex.z*sin(2.0*M_PI*i/ (1.0*n_rotaciones) ),

                                 vertex.y,

                                 vertex.x*sin(2.0*M_PI*i/ (1.0*n_rotaciones) ) +
                                 vertex.z*cos(2.0*M_PI*i/ (1.0*n_rotaciones) ) );

// TRATAMIENTO DE LAS CARAS

   // Lambdas auxiliares (pa que se entienda mejor)
   // Devuelve el vértice anterior
    auto anterior = [](int actual) {
       return actual - 1;
    };
   // Devuelve la posición en el vector de vértices de el vértice actual en el siguiente perfil
    auto sig_perfil = [this] (int actual) {
       return actual + perfil.size();
    };

    for (auto& vertex: perfil)
        vertices.emplace_back(vertex.x*cos(2.0*M_PI*0/ (1.0*n_rotaciones) )+
                              vertex.z*sin(2.0*M_PI*0/ (1.0*n_rotaciones) ),

                              vertex.y,

                              vertex.x*sin(2.0*M_PI*0/ (1.0*n_rotaciones) ) +
                              vertex.z*cos(2.0*M_PI*0/ (1.0*n_rotaciones) ) );

    for (auto n_perfil = 0u; n_perfil < n_rotaciones; ++n_perfil)
        for (auto n_vertice = 1u; n_vertice < perfil.size(); ++n_vertice) {
            auto   actual       = n_perfil*perfil.size() + n_vertice;
            caras.emplace_back(actual, sig_perfil(anterior(actual)), anterior(actual) );
            caras.emplace_back(actual, sig_perfil(actual), sig_perfil(anterior(actual)));
        }

    // Proyectar sobre el eje Y supone dejar a 0 X, Z
    auto proyeccion_y = [](const _vertex3f& v) {
        return _vertex3f(0, v.y, 0);
    };

    if (tapaInferior) {
    // TAPA INFERIOR
        vertices.emplace_back(proyeccion_y(vertices.front()));

    for (auto n_perfil = 0u; n_perfil < n_rotaciones - 1; ++n_perfil) {
        auto centro_tapa = vertices.size()-1;
        auto actual      = n_perfil * perfil.size();
        caras.emplace_back(centro_tapa, actual, sig_perfil(actual));
    }

    // El último triángulo a mano
    caras.emplace_back(vertices.size()-1,(n_rotaciones-1)* perfil.size(), 0);

   }

   if (tapaSuperior) {
// TAPA SUPERIOR
    vertices.emplace_back(proyeccion_y( vertices[ perfil.size() - 1 ]) );

    for (auto n_perfil = 0u; n_perfil < n_rotaciones - 1; ++ n_perfil) {
        auto centro_tapa = vertices.size()-1;
        auto actual      = n_perfil * perfil.size() + (perfil.size()-1);
        caras.emplace_back(centro_tapa, sig_perfil(actual), actual);
    }
    caras.emplace_back(vertices.size()-1, perfil.size()-1, n_rotaciones * perfil.size() - 1);
   }

    // MAPEAMOS LA TEXTURA
    vector<double> distancias(perfil.size());
    auto distancia = [](const _vertex3f& v1, const _vertex3f& v2) {
        return sqrt( pow(v1.x-v2.x,2) + pow(v1.y-v2.y,2) + pow(v1.z-v2.z,2));
    };

    // 1- Calculamos las distancias desde el vértice de origen a cada vértice del perfil inicial
    double distancia_total = 0.0;
    distancias[0] = 0.0;

    for (auto i = 1u; i < perfil.size(); ++i)
        distancias[i] = distancia_total += distancia(vertices[i-1], vertices[i]);

    for (auto& dist: distancias)
        dist /= distancia_total;


    // 2 - Asignamos la posición del Texel en coordenadas s, t. (0,0) en esquina superior izquierda
    for (auto i = 0u; i <= n_rotaciones; ++i)
        for (auto j = 0u; j < perfil.size(); ++j)
            texels.emplace_back(i*1.0/(1.0*n_rotaciones), distancias[j]);


    inicializar_colores(); // Modo colores aleatorios
}

void _rota_tex::read(const char *rute, unsigned n_rotations, bool tapaSuperior, bool tapaInferior)
{

    _file_ply p;
    vector<float> ver_ply;
    vector<int>   car_ply;
    vector<_vertex3f>   read_perfil;

    p.open(rute);          // Abrimos el archivo con el lector proporcionado
    p.read(ver_ply, car_ply); // Al leerlo obtenemos un vector con puntos de vértices y otra con números para las caras

    for (auto i = 0u; i < ver_ply.size(); i+=3) // Cada 3 puntos forman un vértice que creamos y añadimos al vector de vértices
        read_perfil.emplace_back(ver_ply[i], ver_ply[i+1], ver_ply[i+2]);

    p.close();

    parametros(read_perfil, n_rotations, tapaSuperior, tapaInferior);
}

void _rota_tex::adjustPlanes()
{
    double maxX, minX, maxY, minY;
    maxX = minX = vertices.front().x;
    maxY = minY = vertices.front().y;
    for (const auto& vertice: vertices) {
        if (maxX < vertice.x)
            maxX = vertice.x;
        if (maxY < vertice.y)
            maxY = vertice.y;
        if (minX > vertice.x)
            minX = vertice.x;
        if (minY > vertice.y)
            minY = vertice.y;
    }

    planoS[0] /= maxX - minX;
    planoT[1] /= maxY - minY;
}

void _rotacion::read(const char *rute, unsigned n_rotations, bool tapaSuperior, bool tapaInferior)
{

    _file_ply p;
    vector<float> ver_ply;
    vector<int>   car_ply;
    vector<_vertex3f>   read_perfil;

    p.open(rute);          // Abrimos el archivo con el lector proporcionado
    p.read(ver_ply, car_ply); // Al leerlo obtenemos un vector con puntos de vértices y otra con números para las caras

    for (auto i = 0u; i < ver_ply.size(); i+=3) // Cada 3 puntos forman un vértice que creamos y añadimos al vector de vértices
        read_perfil.emplace_back(ver_ply[i], ver_ply[i+1], ver_ply[i+2]);

    p.close();

    parametros(read_perfil, n_rotations, tapaSuperior, tapaInferior);
}
