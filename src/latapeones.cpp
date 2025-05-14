// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D

#include "latapeones.h"

using namespace std;
using namespace glm;

LataPeones::LataPeones() {
    agregar( new Lata("lata-coke.jpg") );
    
    // Pepsi
    NodoGrafoEscena *lataPepsi = new NodoGrafoEscena();
    lataPepsi->agregar(translate(vec3(1.0, 0.0, 0.0)));
    lataPepsi->agregar( new Lata("lata-pepsi.jpg") );

    // Peón de madera
    NodoGrafoEscena *peonMadera = new NodoGrafoEscena();
    Textura *texturaMadera = new Textura("text-madera.jpg");
    Material *materialMadera = new Material(texturaMadera, 0.6, 0.5, 0.4, 60.0);
    peonMadera->agregar(materialMadera);
    peonMadera->agregar( new Peon() );

    // Peón Blanco
    NodoGrafoEscena *peonBlanco = new NodoGrafoEscena();
    Material *materialPeonBlanco = new Material(0.5, 0.5, 0.6, 15.0);
    peonBlanco->agregar(translate(vec3(3.0, 0.0, 0.0)));
    peonBlanco->agregar(materialPeonBlanco);
    peonBlanco->agregar( new Peon() );

    // Peón Negro
    NodoGrafoEscena *peonNegro = new NodoGrafoEscena();
    Material *materialPeonNegro = new Material(0.01, 0.2, 0.5, 60.0);
    peonNegro->agregar(translate(vec3(6.0, 0.0, 0.0)));
    peonNegro->agregar(materialPeonNegro);
    peonNegro->agregar( new Peon() );

    // Peones
    NodoGrafoEscena *peones = new NodoGrafoEscena();
    peones->agregar(translate(vec3(0.0, 0.35, 1.0)));
    peones->agregar(scale(vec3(0.25, 0.25, 0.25)));
    peones->agregar(peonMadera);
    peones->agregar(peonBlanco);
    peones->agregar(peonNegro);


    agregar(lataPepsi);
    agregar(peones);
}

Lata::Lata(const string & nombre_archivo) {
    NodoGrafoEscena *lata = new NodoGrafoEscena();

    Textura* cocacola = new Textura(nombre_archivo);
    Material* materialLata = new Material(cocacola, 0.35, 0.5, 0.5, 0.5);

    Material* materialBase = new Material(0.5, 0.5, 0.5, 0.7);

    NodoGrafoEscena *base = new NodoGrafoEscena();
    base->agregar(materialBase);
    base->agregar(new MallaRevolPLY("lata-pinf.ply", 30));

    NodoGrafoEscena *tapa = new NodoGrafoEscena();
    tapa->agregar(materialBase);
    tapa->agregar(new MallaRevolPLY("lata-psup.ply", 30));

    NodoGrafoEscena *cuerpo = new NodoGrafoEscena();
    cuerpo->agregar(materialLata);
    cuerpo->agregar(new MallaRevolPLY("lata-pcue.ply", 30));

    lata->agregar(base);
    lata->agregar(tapa);
    lata->agregar(cuerpo);

    agregar(lata);
}

Peon::Peon() {
    pm_tras = leerPtrMatriz(agregar(translate(vec3(0.0))));
    agregar(new MallaRevolPLY("peon.ply", 40));
}

bool Peon::cuandoClick(const glm::vec3 & centro_wc) {
    *pm_tras = translate(vec3(0.0, 0.0, 1.0));
    return true;
}


VariasLatasPeones::VariasLatasPeones() {
    unsigned id_lata_cocacola = 1;
    unsigned id_lata_pepsi = 2;
    unsigned id_lata_ugr = 3;
    unsigned id_peon_madera = 4;
    unsigned id_peon_blanco = 5;
    unsigned id_peon_negro = 6;

    // CocaCola
    NodoGrafoEscena *lataCocacola = new NodoGrafoEscena();
    lataCocacola->ponerNombre("Lata de CocaCola");
    lataCocacola->ponerIdentificador(id_lata_cocacola);
    lataCocacola->agregar( new Lata("lata-coke.jpg") );
    
    // Pepsi
    NodoGrafoEscena *lataPepsi = new NodoGrafoEscena();
    lataPepsi->ponerNombre("Lata de Pepsi");
    lataPepsi->ponerIdentificador(id_lata_pepsi);
    lataPepsi->agregar(translate(vec3(1.0, 0.0, 0.0)));
    lataPepsi->agregar( new Lata("lata-pepsi.jpg") );

    // Lata UGR
    NodoGrafoEscena *lataUGR = new NodoGrafoEscena();
    lataUGR->ponerNombre("Lata de la UGR");
    lataUGR->ponerIdentificador(id_lata_ugr);
    lataUGR->agregar(translate(vec3(2.0, 0.0, 0.0)));
    lataUGR->agregar( new Lata("window-icon.jpg") );

    // Peones
    Textura* texturaXY_madera = new Textura("text-madera.jpg");
    Material* materialPeonMadera = new Material(texturaXY_madera, 0.6, 0.5, 0.4, 60.0);
    Material *materialPeonBlanco = new Material(0.5, 0.5, 0.6, 15.0);
    Material *materialPeonNegro = new Material(0.01, 0.2, 0.5, 60.0);

    NodoGrafoEscena *peones = new NodoGrafoEscena();
    peones->agregar(translate(vec3(0.0, 0.35, 1.0)));
    peones->agregar(scale(vec3(0.25, 0.25, 0.25)));

    Peon *peonMadera = new Peon();
    peonMadera->ponerNombre("Peón de Madera");
    peonMadera->ponerIdentificador(id_peon_madera);
    peones->agregar(materialPeonMadera);
    peones->agregar(peonMadera);
    
    Peon *peonBlanco = new Peon();
    peonBlanco->ponerNombre("Peón Blanco");
    peonBlanco->ponerIdentificador(id_peon_blanco);
    peones->agregar(translate(vec3(3.0, 0.0, 0.0)));
    peones->agregar(materialPeonBlanco);
    peones->agregar(peonBlanco);

    Peon *peonNegro = new Peon();
    peonNegro->ponerNombre("Peón Negro");
    peonNegro->ponerIdentificador(id_peon_negro);
    peones->agregar(translate(vec3(3.0, 0.0, 0.0)));
    peones->agregar(materialPeonNegro);
    peones->agregar(peonNegro);


    agregar(lataCocacola);
    agregar(lataPepsi);
    agregar(lataUGR);
    agregar(peones);
}
