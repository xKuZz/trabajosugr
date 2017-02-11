#ifndef TRANSFORM_HELPERS_H
#define TRANSFORM_HELPERS_H
#include <GL/glut.h>
/** Clase auxiliar para almacenar datos y límites de rotación
 */
class transform_rotate
{
private:
    double current = 0;
    double min_angle = -360;
    double max_angle = 360;
    double speed = 1.0;

public:
    /** @brief Inicializa una rotación a 0º con límites [-360, 360].
     */
    transform_rotate() {}

    /** @brief Inicializa una rotación a los grados dados con límites [-360, 360].
     *  @param[in] value Ángulo inicial de la rotación.
     */
    transform_rotate(double value = 0, double min = -360, double max = 360, double speedy = 1.0);

    /** @brief Aumenta en 1 si es posible el ángulo de rotación.
     *  @return Si ha sido posible realizar el incremento del ángulo.
     */
    bool increment();

    /** @brief Disminuye en 1 si es posible el ángulo de rotación.
     *  @return Si ha sido posible realizar la disminución del ángulo.
     */
    bool decrement();

    /** @brief Nos permite establecer los límites [min,max] para el ángulo de rotación.
     *  @param[in] min Límite inferior.
     *  @param[in] max Límite superior.
     */
    void setBound(double min, double max);

    /** @brief Nos devuelve el ángulo de rotación actual.
     *  @param Ángulo de rotación actual.
     */
    double getAngle();

    /** @brief Configura a la velocidad a la que varía al aumentar o disminuir el ángulo
     *  @value Valor a aumentar/modificar del ángulo cada vez que se llama a increment/decrement
     */
    void setSpeed(double value);

    /** @brief Hace que se a la hora de modificar un ángulo haya diferencias mayores
     *  @pre value
     *  @param[in] value Valor a aumentar (se multiplica por la velocidad actual)
     */
    void faster(double value = 1.2);

    /** @brief Hace que se a la hora de modificar un ángulo haya diferencias menores
     *  @param[in] value Valor a disminuir (se divide por la velocidad actual
     */

    void slower(double value = 1.2);
};

class _transform_scale {
private:
    double x,y,z;
public:
    _transform_scale(double x = 1, double y =1, double z = 1) : x(x), y(y), z(z) {}
    void applyScale();
    double getX() const;
    double getY() const;
    double getZ() const;
};

#endif // TRANSFORM_HELPERS_H
