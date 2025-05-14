// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D

#include "modelo-jer.h"

using namespace glm;



BMO::BMO(){

    NodoGrafoEscena * BMO = new NodoGrafoEscena(); 
    unsigned int ident_BMO = BMO->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    BMO->agregar(scale(vec3(0.1, 0.1, 0.1)));

    NodoGrafoEscena * cuerpo = new NodoGrafoEscena();
    cuerpo->ponerNombre("Cuerpo");
    unsigned int id_cuerpo = 1;
    cuerpo->ponerIdentificador(id_cuerpo);
    cuerpo->agregar(new Cuerpo());
    BMO->agregar(cuerpo);


    Textura * textura_cuerpo = new Textura("cuerpo.jpg");
    Material * verde_cuerpo = new Material(textura_cuerpo, 0.5, 0.7, 1.0, 10.0);
    NodoGrafoEscena * brazo_dcho = new NodoGrafoEscena();
    unsigned int ident_brazo_dcho = brazo_dcho->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    brazo_dcho->ponerNombre("Brazo Dcho");
    int id_brazo_dcho = 2;
    brazo_dcho->ponerIdentificador(id_brazo_dcho);
    brazo_dcho->agregar(verde_cuerpo);
    brazo_dcho->agregar(new Brazo_Dcho());
    rotacion_brazo_dcho = brazo_dcho->leerPtrMatriz(ident_brazo_dcho);
    
    NodoGrafoEscena * antebrazo_dcho = new NodoGrafoEscena();
    unsigned int ident_antebrazo_dcho = antebrazo_dcho->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    antebrazo_dcho->ponerNombre("Antebrazo Derecho");
    int id_antebrazo_dcho = 3;
    antebrazo_dcho->ponerIdentificador(id_antebrazo_dcho);
    antebrazo_dcho->agregar(new Antebrazo_Dcho());
    rotacion_antebrazo_dcho = antebrazo_dcho->leerPtrMatriz(ident_antebrazo_dcho);
    brazo_dcho->agregar(antebrazo_dcho);
    

    brazo_dcho->ponerColor(vec3(0.46, 0.73, 0.76));
    BMO->agregar(brazo_dcho);

    NodoGrafoEscena * brazo_izqdo = new NodoGrafoEscena();
    unsigned int ident_brazo_izqdo = brazo_izqdo->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    brazo_izqdo->ponerNombre("Brazo Izqdo");
    int id_brazo_izqdo = 4;
    brazo_izqdo->ponerIdentificador(id_brazo_izqdo);
    brazo_izqdo->agregar(verde_cuerpo);
    brazo_izqdo->agregar(new Brazo_Izqdo());
    rotacion_brazo_izqdo = brazo_izqdo->leerPtrMatriz(ident_brazo_izqdo);

    NodoGrafoEscena * antebrazo_izqdo = new NodoGrafoEscena();
    unsigned int ident_antebrazo_izqdo = antebrazo_izqdo->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    antebrazo_izqdo->ponerNombre("Antebrazo Izquierdo");
    int id_antebrazo_izqdo = 5;
    antebrazo_izqdo->ponerIdentificador(id_antebrazo_izqdo);
    antebrazo_izqdo->agregar(new Antebrazo_Izqdo());
    rotacion_antebrazo_izqdo = antebrazo_izqdo->leerPtrMatriz(ident_antebrazo_izqdo);
    brazo_izqdo->agregar(antebrazo_izqdo);

    brazo_izqdo->ponerColor(vec3(0.46, 0.73, 0.76));
    BMO->agregar(brazo_izqdo);

    NodoGrafoEscena * pierna_dcha = new NodoGrafoEscena();
    unsigned int ident_pierna_dcha = pierna_dcha->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    pierna_dcha->ponerNombre("Pierna Derecha");
    int id_pierna_dcha = 6;
    pierna_dcha->ponerIdentificador(id_pierna_dcha);
    pierna_dcha->agregar(verde_cuerpo);
    pierna_dcha->agregar(new Pierna_Dcha());
    rotacion_pierna_dcha = pierna_dcha->leerPtrMatriz(ident_pierna_dcha);

    NodoGrafoEscena * pie_dcho = new NodoGrafoEscena();
    unsigned int ident_pie_dcho = pie_dcho->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    pie_dcho->ponerNombre("Pie Derecho");
    int id_pie_dcho = 7;
    pie_dcho->ponerIdentificador(id_pie_dcho);
    pie_dcho->agregar(new Pie_Dcho());
    rotacion_pie_dcho = pie_dcho->leerPtrMatriz(ident_pie_dcho);
    pierna_dcha->agregar(pie_dcho);

    pierna_dcha->ponerColor(vec3(0.46, 0.73, 0.76));
    BMO->agregar(pierna_dcha);

    NodoGrafoEscena * pierna_izqda = new NodoGrafoEscena();
    unsigned int ident_pierna_izqda = pierna_izqda->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    pierna_izqda->ponerNombre("Pierna Izquierda");
    int id_pierna_izqda = 8;
    pierna_izqda->ponerIdentificador(id_pierna_izqda);
    pierna_izqda->agregar(verde_cuerpo);
    pierna_izqda->agregar(new Pierna_Izqda());
    rotacion_pierna_izqda = pierna_izqda->leerPtrMatriz(ident_pierna_izqda);

    NodoGrafoEscena * pie_izqdo = new NodoGrafoEscena();
    unsigned int ident_pie_izqdo = pie_izqdo->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
    pie_izqdo->ponerNombre("Pie Izquierdo");
    int id_pie_izqdo = 9;
    pie_izqdo->ponerIdentificador(id_pie_izqdo);
    pie_izqdo->agregar(new Pie_Izqdo());
    rotacion_pie_izqdo = pie_izqdo->leerPtrMatriz(ident_pie_izqdo);
    pierna_izqda->agregar(pie_izqdo);

    pierna_izqda->ponerColor(vec3(0.46, 0.73, 0.76));
    BMO->agregar(pierna_izqda);

    NodoGrafoEscena * globos = new NodoGrafoEscena();
   
    globos->ponerNombre("Globos");
    int id_globos = 10;
    globos->ponerIdentificador(id_globos);
    globos->ponerColor(vec3(1.0, 0.35, 0.47));
    globos->agregar(translate(glm::vec3(0.0, 12.8, 0.0)));
    globos->agregar(new Globos());
    BMO->agregar(globos);

    traslacion = BMO->leerPtrMatriz(ident_BMO);
    agregar(BMO);

}

unsigned BMO::leerNumParametros() const{
    return 9;
}

void BMO::actualizarEstadoParametro(const unsigned iParam, const float t_sec){

    assert(iParam < leerNumParametros());

    switch(iParam){
        case 0:{
            float a_rotacion_brazo_dcho = (30.0 - 30.0)/2;
            float b_rotacion_brazo_dcho = (-30.0 - 30.0)/2;
            float giro_brazo_dcho = a_rotacion_brazo_dcho + b_rotacion_brazo_dcho*sin(2*M_PI*angular_1*t_sec);
            *rotacion_brazo_dcho = translate(vec3(0.0, 6.0, 0.0)) * 
                           rotate(radians(giro_brazo_dcho), vec3(1.0, 0.0, 0.0)) *
                           translate(vec3(0.0, -6.0, 0.0));
            break;
        }
        

        case 1:{
            float a_rotacion_brazo_izqdo = (-30.0 + 30.0)/2;
            float b_rotacion_brazo_izqdo = (30.0 + 30.0)/2;
            float giro_brazo_izqdo = a_rotacion_brazo_izqdo + b_rotacion_brazo_izqdo*sin(2*M_PI*angular_2*t_sec);
            *rotacion_brazo_izqdo = translate(vec3(0.0, 6.0, 0.0)) * 
                           rotate(radians(giro_brazo_izqdo), vec3(1.0, 0.0, 0.0)) *
                           translate(vec3(0.0, -6.0, 0.0));
            break;
        }

        case 2:{
            float a_rotacion_antebrazo_izqdo = (15.0 - 15.0)/2;
            float b_rotacion_antebrazo_izqdo = (-15.0 - 15.0)/2;
            float giro_antebrazo_izqdo = a_rotacion_antebrazo_izqdo + b_rotacion_antebrazo_izqdo*sin(2*M_PI*angular_3*t_sec);
            *rotacion_antebrazo_izqdo = translate(vec3(4.50, 4.0, 0.0)) * 
                           rotate(radians(giro_antebrazo_izqdo), vec3(1.0, 0.0, 0.0)) *
                           translate(vec3(-4.50, -4.0, 0.0));
            break;
        }

        case 3:{
            float a_rotacion_antebrazo_dcho = (15.0 - 15.0)/2;
            float b_rotacion_antebrazo_dcho = (-15.0 - 15.0)/2;
            float giro_antebrazo_dcho = a_rotacion_antebrazo_dcho + b_rotacion_antebrazo_dcho*sin(2*M_PI*angular_4*t_sec);
            *rotacion_antebrazo_dcho = translate(vec3(-4.50, 4.0, 0.0)) *
                                    rotate(radians(giro_antebrazo_dcho), vec3(1.0, 0.0, 0.0))*
                                    translate(vec3(4.50, -4.0, 0.0));
            break;
        }
            

        case 4:{
            float a_rotacion_pierna_dcha = (-45.0 + 45.0)/2;
            float b_rotacion_pierna_dcha = (45.0 + 45.0)/2;
            float giro_pierna_dcha = a_rotacion_pierna_dcha + b_rotacion_pierna_dcha*sin(2*M_PI*angular_5*t_sec);
            *rotacion_pierna_dcha = translate(vec3(0.0, 4.0, 0.0)) * 
                           rotate(radians(giro_pierna_dcha), vec3(1.0, 0.0, 0.0)) *
                           translate(vec3(0.0, -4.0, 0.0));
            break;
        }

        case 5:{
            float a_rotacion_pierna_izqda = (45.0 - 45.0)/2;
            float b_rotacion_pierna_izqda = (-45.0 - 45.0)/2;
            float giro_pierna_izqda = a_rotacion_pierna_izqda + b_rotacion_pierna_izqda*sin(2*M_PI*angular_6*t_sec);
            *rotacion_pierna_izqda = translate(vec3(0.0, 4.0, 0.0)) * 
                           rotate(radians(giro_pierna_izqda), vec3(1.0, 0.0, 0.0)) *
                           translate(vec3(0.0, -4.0, 0.0));
            break;
        }

        case 6:{
            float a_rotacion_pie_dcho = (15.0 - 15.0)/2;
            float b_rotacion_pie_dcho = (-15.0 - 15.0)/2;
            float giro_pie_dcho = a_rotacion_pie_dcho + b_rotacion_pie_dcho*sin(2*M_PI*angular_7*t_sec);
            *rotacion_pie_dcho = translate(vec3(-2.5, 0.0, 0.0)) * 
                           rotate(radians(giro_pie_dcho), vec3(1.0, 0.0, 0.0)) *
                           translate(vec3(2.5, 0.0, 0.0));
            break;
        }

        case 7:{
            float a_rotacion_pie_izqdo = (15.0 - 15.0)/2;
            float b_rotacion_pie_izqdo = (-15.0 - 15.0)/2;
            float giro_pie_izqdo = a_rotacion_pie_izqdo + b_rotacion_pie_izqdo*sin(2*M_PI*angular_8*t_sec);
            *rotacion_pie_izqdo = translate(vec3(2.5, 0.0, 0.0)) * 
                           rotate(radians(giro_pie_izqdo), vec3(1.0, 0.0, 0.0)) *
                           translate(vec3(-2.5, 0.0, 0.0));
            break;
        }

        case 8: {
            
            // Aplicamos las traslaciones en los tres ejes
            *traslacion = translate(vec3(2*cos(velocidad*t_sec), 
                        0.6*cos(velocidad*t_sec)*sin(velocidad*t_sec),
                        1.6*sin(velocidad*t_sec)*cos(velocidad*t_sec)));
            break;
        }            
    }


}

Cuerpo::Cuerpo(){
    NodoGrafoEscena *cuerpo = new NodoGrafoEscena();


    Textura * textura_cuerpo = new TexturaXY("cuerpo.jpg");
    Material * verde_cuerpo = new Material(textura_cuerpo, 0.5, 0.7, 1.0, 10.0);
    cuerpo->agregar(translate(vec3(0.0, 8.0, 0.0)));
    cuerpo->agregar(scale(vec3(4.0, 5.0, 3.0)));
    cuerpo->ponerColor(vec3(0.57, 0.87, 0.84));
    cuerpo->agregar(verde_cuerpo);
    cuerpo->agregar(new Cubo24());
    agregar(cuerpo);

    NodoGrafoEscena * cruceta = new NodoGrafoEscena();
    cruceta->ponerNombre("Cruceta");
    int id_cruceta = 11;
    cruceta->ponerIdentificador(id_cruceta);
    cruceta->ponerColor(vec3(1.0, 0.83, 0.27));
    cruceta->agregar(new Cruceta());
    agregar(cruceta);

    NodoGrafoEscena * puertos = new NodoGrafoEscena();
    puertos->ponerNombre("Puertos");
    int id_puertos = 12;
    puertos->ponerIdentificador(id_puertos);
    puertos->ponerColor(vec3(0.24, 0.27, 0.42));
    puertos->agregar(new Puertos());
    agregar(puertos);

    NodoGrafoEscena * lector = new NodoGrafoEscena();
    lector->ponerNombre("Lector");
    int id_lector = 13;
    lector->ponerIdentificador(id_lector);
    lector->ponerColor(vec3(0.10, 0.13, 0.20));
    lector->agregar(translate(vec3(-1.2, 7.5, 3.0)));
    lector->agregar(new Lector());
    agregar(lector);

    NodoGrafoEscena * pantalla = new NodoGrafoEscena();
    pantalla->ponerColor(vec3(0.68, 0.91, 0.86));
    pantalla->ponerNombre("Pantalla");
    int id_pantalla = 14;
    pantalla->ponerIdentificador(id_pantalla);
    pantalla->agregar(new Pantalla());
    agregar(pantalla);

    NodoGrafoEscena * botones = new NodoGrafoEscena();
    botones->ponerNombre("Botones Redondos");
    botones->agregar(new Botones_Redondos());
    agregar(botones);

    NodoGrafoEscena * boton_triangular = new NodoGrafoEscena();
    boton_triangular->ponerNombre("Botón Triangular");
    int id_boton_triangular = 15;
    boton_triangular->ponerIdentificador(id_boton_triangular);
    boton_triangular->agregar(new Boton_Triangular());
    boton_triangular->ponerColor(vec3(0.46, 0.73, 0.76));
    agregar(boton_triangular);

    NodoGrafoEscena * ventilacion = new NodoGrafoEscena();
    ventilacion->ponerColor(vec3(0.10, 0.13, 0.20));
    ventilacion->ponerNombre("Ventilación");
    int id_ventilacion = 16;
    ventilacion->ponerIdentificador(id_ventilacion);
    ventilacion->agregar(new Ventilacion());
    agregar(ventilacion);

    NodoGrafoEscena * pilas = new NodoGrafoEscena();
    pilas->ponerColor(vec3(0.46, 0.73, 0.76));
    pilas->ponerNombre("Pilas");
    int id_pilas = 17;
    pilas->ponerIdentificador(id_pilas);
    pilas->agregar(new Pilas());
    agregar(pilas);


    NodoGrafoEscena * altavoces = new NodoGrafoEscena();
    altavoces->ponerNombre("Altavoces");
    int id_altavoces = 18;
    altavoces->ponerIdentificador(id_altavoces);
    altavoces->ponerColor(vec3(0.10, 0.13, 0.20));
    altavoces->agregar(translate(vec3(-4.25, 0.0, 0.0)));
    altavoces->agregar(translate(vec3(0.0, 10.7, 0.0)));

    NodoGrafoEscena * altavoz_dcho = new NodoGrafoEscena();
    altavoz_dcho->agregar(rotate(radians(90.0f), vec3(0.0, 1.0, 0.0)));
    altavoz_dcho->agregar(new Altavoces());
    altavoces->agregar(altavoz_dcho);

    altavoces->agregar(translate(vec3(8.40, 0.0, 0.0)));
    NodoGrafoEscena * altavoz_izqdo = new NodoGrafoEscena();
    altavoz_izqdo->agregar(rotate(radians(90.0f), vec3(0.0, 1.0, 0.0)));
    altavoz_izqdo->agregar(new Altavoces());
    altavoces->agregar(altavoz_izqdo);

    agregar(altavoces);

    NodoGrafoEscena * letras = new NodoGrafoEscena();
    letras->ponerNombre("Letras");
    int id_letras = 19;
    letras->ponerIdentificador(id_letras);
    letras->ponerColor(vec3(0.0, 0.0, 0.0));
    letras->agregar(translate(vec3(-4.1, 6.7, -0.2)));

    NodoGrafoEscena * letras_izqda = new NodoGrafoEscena();
    letras_izqda->agregar(new Letras());
    letras->agregar(letras_izqda);

    letras->agregar(translate(vec3(8.2, 0.0, 0.0)));
    NodoGrafoEscena * letras_dcha = new NodoGrafoEscena();
    letras_dcha->agregar(new Letras());
    letras->agregar(letras_dcha);

    agregar(letras);
}

Brazo_Izqdo::Brazo_Izqdo(){
    NodoGrafoEscena *brazo_izqdo = new NodoGrafoEscena();
    NodoGrafoEscena *hombro_izqdo = new NodoGrafoEscena();
    NodoGrafoEscena *codo_izqdo = new NodoGrafoEscena();

    agregar(translate(vec3(-4.50, 4.0, 0.0)));
    brazo_izqdo->agregar(scale(vec3(0.5, 2.0, 0.5)));
    brazo_izqdo->agregar(new Cilindro(12,25));
    agregar(brazo_izqdo);

    hombro_izqdo->agregar(translate(vec3(0.0, 2.0, 0.0)));
    hombro_izqdo->agregar(scale(vec3(0.5, 0.5, 0.5)));
    hombro_izqdo->agregar(new Esfera(12,25));
    agregar(hombro_izqdo);

    codo_izqdo->agregar(scale(vec3(0.5, 0.5, 0.5)));
    codo_izqdo->agregar(new Esfera(12,25));
    agregar(codo_izqdo);
}

Brazo_Dcho::Brazo_Dcho(){
    NodoGrafoEscena *brazo_derecho = new NodoGrafoEscena();
    NodoGrafoEscena *hombro_dcho = new NodoGrafoEscena();
    NodoGrafoEscena *codo_dcho = new NodoGrafoEscena();
    
    agregar(translate(vec3(4.50, 4.0, 0.0)));
    brazo_derecho->agregar(scale(vec3(0.5, 2.0, 0.5)));
    brazo_derecho->agregar(new Cilindro(12,25));
    agregar(brazo_derecho);

    hombro_dcho->agregar(translate(vec3(0.0, 2.0, 0.0)));
    hombro_dcho->agregar(scale(vec3(0.5, 0.5, 0.5)));
    hombro_dcho->agregar(new Esfera(12,25));
    agregar(hombro_dcho);

    codo_dcho->agregar(scale(vec3(0.5, 0.5, 0.5)));
    codo_dcho->agregar(new Esfera(12,25));
    agregar(codo_dcho);
}

Pierna_Dcha::Pierna_Dcha(){
    NodoGrafoEscena *pierna_derecha = new NodoGrafoEscena();
    NodoGrafoEscena *tobillo_derecho = new NodoGrafoEscena();

    agregar(translate(vec3(2.5, 0.0, 0.0)));
    pierna_derecha->agregar(scale(vec3(0.5, 4.0, 0.5)));
    pierna_derecha->agregar(new Cilindro(12,25));
    agregar(pierna_derecha);

    tobillo_derecho->agregar(scale(vec3(0.5, 0.5, 0.5)));
    tobillo_derecho->agregar(new Esfera(12,25));
    agregar(tobillo_derecho);
}

Pierna_Izqda::Pierna_Izqda(){
    NodoGrafoEscena *pierna_izqda = new NodoGrafoEscena();
    NodoGrafoEscena *tobillo_izqdo = new NodoGrafoEscena();

    agregar(translate(vec3(-2.5, 0.0, 0.0)));
    pierna_izqda->agregar(scale(vec3(0.5, 4.0, 0.5)));
    pierna_izqda->agregar(new Cilindro(12,25));
    agregar(pierna_izqda);

    tobillo_izqdo->agregar(scale(vec3(0.5, 0.5, 0.5)));
    tobillo_izqdo->agregar(new Esfera(12,25));
    agregar(tobillo_izqdo);

}

Pie::Pie(){
    NodoGrafoEscena *cilindro = new NodoGrafoEscena();
    NodoGrafoEscena *esfera = new NodoGrafoEscena();

    agregar(scale(vec3(0.5, 0.5, 1.0)));
    cilindro->agregar(rotate(radians(90.0f), vec3(1.0, 0.0, 0.0)));
    cilindro->agregar(new Cilindro(12,25));
    agregar(cilindro);
    
    esfera->agregar(translate(vec3(0.0, 0.0, 1.0)));
    esfera->agregar(new Esfera(12,25));
    agregar(esfera);
}

Antebrazo::Antebrazo(){
    NodoGrafoEscena *cilindro = new NodoGrafoEscena();
    NodoGrafoEscena *esfera = new NodoGrafoEscena();

    cilindro->agregar(scale(vec3(0.5, 0.5, 1.5)));
    cilindro->agregar(rotate(radians(90.0f), vec3(1.0, 0.0, 0.0)));
    cilindro->agregar(new Cilindro(12,25));
    agregar(cilindro);

    esfera->agregar(scale(vec3(0.5, 0.5, 0.5)));
    esfera->agregar(translate(vec3(0.0, 0.0, 3)));
    esfera->agregar(new Esfera(12,25));
    agregar(esfera);
}

Pie_Dcho::Pie_Dcho(){
    NodoGrafoEscena *pie_derecho = new NodoGrafoEscena();
    pie_derecho->agregar(translate(vec3(2.5, 0.0, 0.0)));
    pie_derecho->agregar(new Pie());
    agregar(pie_derecho);
}

Pie_Izqdo::Pie_Izqdo(){
    NodoGrafoEscena *pie_izqdo = new NodoGrafoEscena();
    pie_izqdo->agregar(translate(vec3(-2.5, 0.0, 0.0)));
    pie_izqdo->agregar(new Pie());
    agregar(pie_izqdo);
}

Antebrazo_Dcho::Antebrazo_Dcho(){
    NodoGrafoEscena *antebrazo_dcho = new NodoGrafoEscena();
    antebrazo_dcho->agregar(translate(vec3(4.50, 4.0, 0.0)));
    antebrazo_dcho->agregar(rotate(radians(15.0f), vec3(1.0, 0.0, 0.0)));
    antebrazo_dcho->agregar(new Antebrazo());
    agregar(antebrazo_dcho);
}

Antebrazo_Izqdo::Antebrazo_Izqdo(){
    NodoGrafoEscena *antebrazo_izqdo = new NodoGrafoEscena();
    antebrazo_izqdo->agregar(translate(vec3(-4.50, 4.0, 0.0)));
    antebrazo_izqdo->agregar(rotate(radians(45.0f), vec3(1.0, 0.0, 0.0)));
    antebrazo_izqdo->agregar(new Antebrazo());
    agregar(antebrazo_izqdo);
}

Pantalla::Pantalla(){
    NodoGrafoEscena *pantalla = new NodoGrafoEscena();
    Textura * textura_cara = new Textura("cara_bmo.jpg");
    Material * material_cara = new Material(textura_cara, 0.5, 0.7, 0.1, 5.0);

    pantalla->agregar(translate(vec3(0.0, 10.25, 3.0)));
    pantalla->agregar(scale(vec3(3, 2.0, 0.1)));
    pantalla->agregar(material_cara);
    pantalla->agregar(new Cubo24());

    agregar(pantalla);
}

Cruceta::Cruceta(){
    NodoGrafoEscena *flecha_horizontal = new NodoGrafoEscena();
    NodoGrafoEscena *flecha_vertical = new NodoGrafoEscena();

    agregar(translate(vec3(-1.8, 5.8, 3.1)));
    flecha_horizontal->agregar(scale(vec3(0.7, 0.25, 0.25)));
    flecha_horizontal->agregar(new Cubo24());
    agregar(flecha_horizontal);

    agregar(rotate(radians(90.0f), vec3(0.0, 0.0, 1.0)));
    flecha_vertical->agregar(scale(vec3(0.7, 0.25, 0.25)));
    flecha_vertical->agregar(new Cubo24());
    agregar(flecha_vertical);
}

Boton::Boton(){ 

    NodoGrafoEscena *boton = new NodoGrafoEscena();
    boton->agregar(rotate(radians(90.0f), vec3(1.0f, 0.0f, 0.0f)));
    boton->agregar(new Cilindro(12,25));

    agregar(boton);
}

Botones_Redondos::Botones_Redondos(){
    
    NodoGrafoEscena *boton_rojo = new NodoGrafoEscena();
    NodoGrafoEscena *boton_azul = new NodoGrafoEscena();
    NodoGrafoEscena *boton_verde = new NodoGrafoEscena();

    Textura * textura_rojo = new Textura("bmo_button_circle_textured.jpg");
    Material * rojo = new Material(textura_rojo, 0.6, 0.6, 1.0, 100.0);
    boton_rojo->ponerNombre("Boton rojo");
    int id_boton_rojo = 20;
    boton_rojo->ponerIdentificador(id_boton_rojo);
    boton_rojo->agregar(translate(vec3(1.6, 4.4, 3.0)));
    boton_rojo->agregar(scale(vec3(0.6, 0.6, 0.30)));
    boton_rojo->ponerColor(vec3(1.0, 0.35, 0.47));
    boton_rojo->agregar(rojo);
    boton_rojo->agregar(new Boton());

    boton_azul->ponerNombre("Boton azul");
    int id_boton_azul = 21;
    boton_azul->ponerIdentificador(id_boton_azul);
    boton_azul->agregar(translate(vec3(2.6, 7.4, 3.0)));
    boton_azul->agregar(scale(vec3(0.3, 0.3, 0.30)));
    boton_azul->ponerColor(vec3(0.24, 0.29, 0.52));
    boton_azul->agregar(new Boton());

    boton_verde->ponerNombre("Boton verde");
    int id_boton_verde = 22;
    boton_verde->ponerIdentificador(id_boton_verde);
    boton_verde->agregar(translate(vec3(2.6, 5.4, 3.0)));
    boton_verde->agregar(scale(vec3(0.4, 0.4, 0.30)));
    boton_verde->ponerColor(vec3(0.49, 0.74, 0.25));
    boton_verde->agregar(new Boton());

    agregar(boton_verde);
    agregar(boton_azul);
    agregar(boton_rojo);
}

Boton_Triangular::Boton_Triangular(){

    NodoGrafoEscena *boton_triangulo = new NodoGrafoEscena();


    //Aquí será necesario crear un boton triangulo en malla-ind
    agregar(translate(vec3(1.6, 5.7, 3.3)));
    boton_triangulo->agregar(scale(vec3(0.8, 0.8, 0.70)));
    boton_triangulo->agregar(new Triangulo_Boton());

    agregar(boton_triangulo);
}

Lector::Lector(){
    NodoGrafoEscena *lector = new NodoGrafoEscena();
    
    lector->agregar(scale(vec3(1.7, 0.20, 0.25)));
    lector->agregar(new Cubo24());

    agregar(lector);
}

Puertos::Puertos(){
    NodoGrafoEscena *puerto_1 = new NodoGrafoEscena();
    NodoGrafoEscena *puerto_2 = new NodoGrafoEscena();

    agregar(translate(vec3(-2.5, 4.0, 3.1)));
    puerto_1->agregar(scale(vec3(0.55, 0.20, 0.25)));
    puerto_1->agregar(new Cubo24());
    agregar(puerto_1);

    agregar(translate(vec3(1.5, 0.0, 0.0)));
    puerto_2->agregar(scale(vec3(0.55, 0.20, 0.25)));
    puerto_2->agregar(new Cubo24());

    
    agregar(puerto_2);
}

Rejilla::Rejilla(){
    NodoGrafoEscena *rejilla = new NodoGrafoEscena();
    
    rejilla->agregar(scale(vec3(0.30, 1.50, 0.25)));
    rejilla->agregar(new Cubo24());

    agregar(rejilla);
}

Ventilacion::Ventilacion(){
    NodoGrafoEscena *ventilacion = new NodoGrafoEscena();
    
    for(int i = -2; i < 3; i++){
        NodoGrafoEscena * rejilla_i = new NodoGrafoEscena();
        
        rejilla_i->agregar(translate(vec3(1.5*i, 11.0, -3.0)));
        rejilla_i->agregar(new Rejilla());

        ventilacion->agregar(rejilla_i);
    }
    agregar(ventilacion);
}


Altavoz::Altavoz(){
    NodoGrafoEscena *altavoz = new NodoGrafoEscena();

    altavoz->agregar(rotate(radians(90.0f), vec3(1.0, 0.0, 0.0)));
    altavoz->agregar(scale(vec3(0.1, 0.1, 0.1)));
    altavoz->agregar(new Cilindro(12, 25));

    agregar(altavoz);
}

Altavoces::Altavoces(){
    NodoGrafoEscena *altavoces = new NodoGrafoEscena();

    NodoGrafoEscena *altavoz_centro = new NodoGrafoEscena();
    altavoz_centro->agregar(new Altavoz());

    altavoces->agregar(altavoz_centro);
    
    for(int i = 0; i <= 10*M_PI/6; i+=2*M_PI/6){
        NodoGrafoEscena * altavoz_i = new NodoGrafoEscena();
        
        altavoz_i->agregar(translate(vec3(cos(i), sin(i), 0.0)));
        altavoz_i->agregar(new Altavoz());

        altavoces->agregar(altavoz_i);
    }
    agregar(altavoces);
}

Pilas::Pilas(){
    NodoGrafoEscena *pilas = new NodoGrafoEscena();
    
    pilas->agregar(translate(vec3(0.0, 6.5, -3.0)));
    pilas->agregar(scale(vec3(3.0, 2.0, 0.25)));
    pilas->agregar(new Cubo24());

    agregar(pilas);
}

Letras::Letras(){
    NodoGrafoEscena *letras = new NodoGrafoEscena();
    
    letras->agregar(scale(vec3(3.0, 3.0, 3.0)));
    letras->agregar(rotate(radians(-90.0f), vec3(0.0, 1.0, 0.0)));
    letras->agregar(rotate(radians(-90.0f), vec3(0.0, 0.0, 1.0)));
    letras->agregar(new MallaPLY("bmo.ply"));

    agregar(letras);
}

Globos::Globos(){
    NodoGrafoEscena *globos = new NodoGrafoEscena();
    globos->agregar(new MallaPLY("balloon.ply"));

    agregar(globos);
}