#ifndef LUZ_H
#define LUZ_H
#include <array>
#include <cmath>
#include "rgb.h"

/** @brief Clase abstracta para definir una fuente de luz
 */
class LightSource
{
public:
   enum class Type {Positional, Directional};
   /** @brief Habilita en la escena la fuente de luz.
    *  @pre Debe realizarse tras cambiar a GL_MODELVIEW.
    */
   virtual void enable();
   /** @brief Deshabilita el uso de una fuente de luz en la escena
    */
   void disable() const;

   /** @brief Devuelve el tipo de fuente de luz usada.
    *  @return Type::Positional si es posicional o Type::Directional si es direccional
    */
   Type getType() const;

protected:
   LightSource(GLenum id, const RGBAColor &ambiente, const RGBAColor &difuso, const RGBAColor &especular);
   GLenum id;
   RGBAColor ambiente, difuso, especular;
   Type type;
   std::array<float, 4> position;

};

/** @brief Clase para una fuente de luz posicional.
 */
class PositionalLightSource: public LightSource
{
public:
    /** @brief Crea una nueva fuente de luz posicioanl con
     *  @id ID en OpenGL de la luz a usar.
     *  @color Color RGB de la luz.
     *  @pos posición de la luz.
     */
    PositionalLightSource(GLenum id, const RGBAColor& ambiente, const RGBAColor &difuso, const RGBAColor &especular, const std::array<float, 3> &pos);

    /** @brief Activa la luz de esta clase.
     *  @pre Debe realizarse tras cambiar a GL_MODELVIEW
     */
    void enable() override;
private:

};

class DirectionalLightSource : public LightSource
{
public:
    DirectionalLightSource(GLenum id, const RGBAColor& ambiente, const RGBAColor &difuso, const RGBAColor &especular,
                           const std::array<float, 3>& pos, double alpha, double beta);
    void enable() override;
    void modifyAlpha(float value);
    void modifyBeta(float value);
private:

    double alpha;
    double beta;
};

#endif // LUZ_H
