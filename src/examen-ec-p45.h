// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D

#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP
#include "malla-ind.h"
#include "grafo-escena.h"

class Piramide : public MallaInd
{
   public:
      Piramide();
};

class NodoPiramide : public NodoGrafoEscena {
    public:
        NodoPiramide();
};

class Triangulo_N : public MallaInd
{
    private:
        glm::vec3 punto_medio;
    public:
        Triangulo_N(glm::vec3 a, glm::vec3 b, glm::vec3 c);
};

class GrafoTriangulo : public NodoGrafoEscena {
    public:
        GrafoTriangulo(int i, glm::vec3 a,
glm::vec3 b, glm::vec3 c);
    protected:
        virtual bool cuandoClick(const glm::vec3 &centro) override;
};

class GrafoPiramide : public NodoGrafoEscena {
    public:
        GrafoPiramide();
};

#endif