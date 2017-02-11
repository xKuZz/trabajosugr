#include "scene_p4.h"

Scene_p4::Scene_p4()
{

}

void Scene_p4::initialize()
{
    // FUENTES DE LUZ
    lights.emplace_back( new PositionalLightSource(GL_LIGHT0, {0,0,0}, {1,1,1}, {1,1,1}, {7, 7, 0}) );
    lights.emplace_back( new DirectionalLightSource(GL_LIGHT1, {0,0,0}, {1,1,1}, {1,1,1}, {0,0,1}, 0, 0));
    // 1. LATA
    // 1.1 Cuello
    initialized = true;
    lata_pcue.read("lata-pcue.ply", 50, false, false);
    lata_pcue_tex = std::make_unique<Texture>("text-lata-1.jpg", false);
    lata_pcue_mat = Material({0.2, 0.2, 0.2}, {1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}, 0.4, lata_pcue_tex.get());
    lata_sup.read("lata-psup.ply", 40, false, false);

    // 1.2 Parte superior de la lata
    lata_tapas_mat = Material({0.19225, 0.19225, 0.19225}, {0.50754, 0.50754, 0.50754}, {0.508273, 0.508273, 0.508273}, 0.4);

    // 1.3 Parte inferior de la lata
    lata_inf.read("lata-pinf.ply", 40, false, false);

    // 2. Peones
    peon_wood.parametros(perfil_peon, 20);
    peon_color.parametros(perfil_peon, 20);

    // 2.1 Peón de madera
    peon_wood.adjustPlanes();
    wood = std::make_unique<Texture>("text-madera.jpg", true);
    wood->setPlanes(peon_wood.getPlanoS(), peon_wood.getPlanoT());
    peon_wood_mat = Material({0.2, 0.2, 0.2}, {1.0,1.0,1.0}, {1.0, 1.0, 1.0}, 1.0, wood.get());

    // 2.2 Peón blanco
    peon_white = Material({0.2,0.2,0.2}, {1.0,1.0,1.0},{0.0,0.0,0.0}, 0);

    // 2.3 Peón negro
    peon_black = Material({0.2,0.2,0.2}, {0.01,0.01,0.01}, {1.0, 1.0, 1.0}, 1.0);


    // Fin. Valores por defecto de material
    default_mat = Material({0.2, 0.2, 0.2}, {0.8, 0.8, 0.8}, {0.0, 0.0, 0.0}, 0.0);

}

void Scene_p4::drawMe()
{
    glMatrixMode(GL_MODELVIEW);
    for (auto& light: lights)
        light->enable();
    glPushMatrix();
        glScaled(4,4,4);
        // Pintamos lata
        lata_pcue_mat.enable();
        lata_pcue.draw_iluminacion_suave_tex();
        lata_tapas_mat.enable();
        lata_sup.draw_iluminacion_plana();
        lata_inf.draw_iluminacion_plana();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 0, 3);
        peon_wood_mat.enable();
        peon_wood.draw_iluminacion_suave_tex();
        glTranslated(2,0,-1);
        peon_white.enable();
        peon_color.draw_iluminacion_suave();
        peon_black.enable();
        glTranslated(2,0,-1);
        peon_color.draw_iluminacion_suave();
    glPopMatrix();

    // Desactivamos fuentes de luz
    for (auto& light: lights)
        light->disable();

    default_mat.enable();
    glDisable(GL_LIGHTING);

}

void Scene_p4::drawNormales()
{
    glPushMatrix();
        glScaled(4,4,4);
        // Pintamos lata
        lata_pcue.draw_normales();
        lata_sup.draw_normales();
        lata_inf.draw_normales();
    glPopMatrix();
    glPushMatrix();
        glTranslated(0, 0, 3);
        peon_wood.draw_normales();
        glTranslated(2,0,-1);
        peon_color.draw_normales();
        glTranslated(2,0,-1);
        peon_color.draw_normales();
    glPopMatrix();
}

void Scene_p4::modifyAlpha(float value)
{
    static_cast<DirectionalLightSource*>(lights[1].get())->modifyAlpha(value);
}

void Scene_p4::modifyBeta(float value)
{
    static_cast<DirectionalLightSource*>(lights[1].get())->modifyBeta(value);
}

bool Scene_p4::empty()
{
    return !initialized;
}
