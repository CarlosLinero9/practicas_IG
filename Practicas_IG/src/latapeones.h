// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D

#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "grafo-escena.h"

using namespace std;

class LataPeones : public NodoGrafoEscena {
    public:
        LataPeones();
};

class Lata : public NodoGrafoEscena {
    public:
        Lata(const string & nombre_archivo);
};

class Peon : public NodoGrafoEscena {
    public:
        Peon();
        bool cuandoClick(const glm::vec3 & centro_wc) override;
    
    protected:
        glm::mat4* pm_tras = nullptr;
};

class VariasLatasPeones : public NodoGrafoEscena {
    public:
        VariasLatasPeones();
};

#endif
