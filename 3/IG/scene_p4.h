        #ifndef SCENE_P4_H
    #define SCENE_P4_H
    #include "objetos.h"
    #include "textura.h"
    #include "material.h"
    #include "luz.h"
    #include<memory>
    #include <vector>

    /** @brief Clase que contiene todos los elementos de la escena a representar en la P4.
     */
    class Scene_p4
    {
    public:
        Scene_p4();
        void initialize();
        void drawMe();
        void drawNormales();
        void modifyAlpha(float value);
        void modifyBeta(float value);
        bool empty();
    private:
        bool initialized = false;
        /** FUENTES DE LUZ **/
        std::vector<std::unique_ptr<LightSource>> lights;
        /** LATA **/
        // Cuello de la lata
        _rota_tex lata_pcue;
        std::unique_ptr<Texture> lata_pcue_tex;
        Material lata_pcue_mat;
        // Parte superior de la lata
        Material lata_tapas_mat;
        _rotacion lata_sup;
        // Parte inferior de la lata
        _rotacion lata_inf;

        /** PEONES **/
        std::vector<_vertex3f> perfil_peon { {1.0, -1.4, 0.0},
                                   {1.0, -1.1, 0.0},
                                   {0.5, -0.7, 0.0},
                                   {0.4, -0.4, 0.0},
                                   {0.4, 0.5, 0.0},
                                   {0.5, 0.6, 0.0},
                                   {0.3, 0.6, 0.0},
                                   {0.5, 0.8, 0.0},
                                   {0.55, 1.0, 0.0},
                                   {0.5,  1.2, 0.0},
                                   {0.3,  1.4, 0.0}
                                 };

        // Peón de madera
        _rota_tex peon_wood;
        std::unique_ptr<Texture> wood;
        Material peon_wood_mat;

        // Peones blanco y negro
        _rotacion peon_color;
        Material peon_white;
        Material peon_black;
        Material default_mat;

    };

    #endif // SCENE_P4_H
