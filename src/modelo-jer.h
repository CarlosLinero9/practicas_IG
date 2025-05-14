// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

#include "ig-aux.h"
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"
#include "malla-ind.h"
#include "malla-revol.h"

#include <cmath>
#include <glm/gtx/transform.hpp>




class BMO : public NodoGrafoEscena{

    protected:
        glm::mat4 *rotacion_brazo_izqdo = nullptr;
        glm::mat4 *rotacion_brazo_dcho = nullptr;
        glm::mat4 *rotacion_pierna_izqda = nullptr;
        glm::mat4 *rotacion_pierna_dcha = nullptr;
        glm::mat4 *rotacion_antebrazo_izqdo = nullptr;
        glm::mat4 *rotacion_antebrazo_dcho = nullptr;
        glm::mat4 *rotacion_pie_izqdo = nullptr;
        glm::mat4 *rotacion_pie_dcho = nullptr;
        glm::mat4 *rotacion_mareo = nullptr;
        glm::mat4 *traslacion = nullptr;
        const float angular_1 = 3;
        const float angular_2 = 3;
        const float angular_3 = 3;
        const float angular_4 = 3;
        const float angular_5 = 3;
        const float angular_6 = 3;
        const float angular_7 = 3;
        const float angular_8 = 3;
        float velocidad = 5.0f;  // Velocidad 


    public:
        BMO();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);

};

class Cuerpo : public NodoGrafoEscena{
    public:
        Cuerpo();
};

class Brazo_Izqdo : public NodoGrafoEscena{
    public: 
        Brazo_Izqdo();
};

class Brazo_Dcho : public NodoGrafoEscena{
    public: 
        Brazo_Dcho();
};

class Pierna_Izqda : public NodoGrafoEscena{
    public:
        Pierna_Izqda();
};

class Pierna_Dcha : public NodoGrafoEscena{
    public:
        Pierna_Dcha();
};

class Pie : public NodoGrafoEscena{
    public:
        Pie();
};

class Antebrazo : public NodoGrafoEscena{
    public:
        Antebrazo();
};

class Pie_Dcho : public NodoGrafoEscena{
    public:
        Pie_Dcho();
};

class Pie_Izqdo : public NodoGrafoEscena{
    public:
        Pie_Izqdo();
};

class Antebrazo_Dcho : public NodoGrafoEscena{
    public:
        Antebrazo_Dcho();
};

class Antebrazo_Izqdo : public NodoGrafoEscena{
    public:
        Antebrazo_Izqdo();
};

class Pantalla : public NodoGrafoEscena{
    public:
        Pantalla();
};

class Cruceta : public NodoGrafoEscena{
    public:
        Cruceta();
};

class Boton : public NodoGrafoEscena{
    public:
        Boton();
};

class Botones_Redondos : public NodoGrafoEscena{
    public:
        Botones_Redondos();
};

class Boton_Triangular : public NodoGrafoEscena{
    public:
        Boton_Triangular();
};

class Lector : public NodoGrafoEscena{
    public:
        Lector();
};

class Puertos : public NodoGrafoEscena{
    public:
        Puertos();
};

class Rejilla : public NodoGrafoEscena{
    public:
        Rejilla();
};

class Ventilacion : public NodoGrafoEscena{
    public:
        Ventilacion();
};

class Altavoz : public NodoGrafoEscena{
    public:
        Altavoz();
};

class Altavoces : public NodoGrafoEscena{
    public:
        Altavoces();
};

class Pilas : public NodoGrafoEscena{
    public:
        Pilas();
};

class Letras : public NodoGrafoEscena{
    public:
        Letras();
};

class Globos : public NodoGrafoEscena{
    public:
        Globos();
};

#endif