// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D
#include "examen-ec-p45.h"

Piramide::Piramide()
:MallaInd("Piramide"){
    vertices = {
        {0.0, 0.0, 0.0}, 
        {2.0, 0.0, 0.0}, 
        {2.0, 0.0, 2.0}, 
        {0.0, 0.0, 2.0},

        
        {0.0, 0.0, 0.0}, 
        {2.0, 0.0, 0.0}, 
        {1.0, 2.0, 1.0}, 

        
        {2.0, 0.0, 0.0}, 
        {2.0, 0.0, 2.0}, 
        {1.0, 2.0, 1.0}, 

        {0.0, 0.0, 2.0}, 
        {2.0, 0.0, 2.0}, 
        {1.0, 2.0, 1.0}, 

        {0.0, 0.0, 2.0}, 
        {0.0, 0.0, 0.0}, 
        {1.0, 2.0, 1.0}, 

   };

    triangulos = {
        {0, 1, 3},
        {1, 2, 3},

        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
        {13, 14, 15}
    };

    cc_tt_ver = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0},

        {0.0, 1.0},
        {1.0, 1.0},
        {0.5, 0.0},

        {0.0, 1.0},
        {1.0, 1.0},
        {0.5, 0.0},
        {0.0, 1.0},
        {1.0, 1.0},
        {0.5, 0.0},
        {0.0, 1.0},
        {1.0, 1.0},
        {0.5, 0.0},
    };
}


NodoPiramide::NodoPiramide()
{
   ponerNombre("Nodo piramide examen");
   Textura * textura_piramide = new Textura("window-icon.jpg");
   Material * material_piramide = new Material(textura_piramide, 0.7, 0.5, 0.0, 30);
   agregar(material_piramide);
   agregar(new Piramide());
}

Triangulo_N::Triangulo_N(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{

   vertices.push_back(a);
   vertices.push_back(b);
   vertices.push_back(c);

    punto_medio = (a+b+c)/(float)3.0;

   triangulos =
      {  
        {0,1,2},
      };

      ponerColor(glm::vec3(1.0, 1.0, 1.0));
    

      calcularNormales();
}

GrafoTriangulo::GrafoTriangulo(int i, glm::vec3 a,
glm::vec3 b, glm::vec3 c)
{
   std::string nom_temp = "Triangulo Nº "; 
   nom_temp += std::to_string(i+1);

   ponerNombre(nom_temp);
   agregar( new Triangulo_N(a,b,c));

}

bool GrafoTriangulo::cuandoClick(const glm::vec3 &centro) {
   std::cout << "Se ha seleccionado la " << leerNombre() << std::endl ;
   if (leerColor() == glm::vec3(1.0, 1.0, 1.0)) {
      ponerColor(glm::vec3(1.0, 0.0, 0.0));
      std::cout << "Se ha cambiado el color de Blanco a Rojo" <<  std::endl ;
   } else {
      ponerColor(glm::vec3(1.0, 1.0, 1.0));
      std::cout << "Se ha cambiado el color de la esfera de Rojo a Blanco" <<  std::endl ;
   }
   return true ;
}

GrafoPiramide::GrafoPiramide()
{
   int cont = 1;
   
   NodoGrafoEscena * grafo_piramide = new NodoGrafoEscena() ;
   
    GrafoTriangulo * cara_1 = new GrafoTriangulo(cont,vec3{0.0, 0.0, 0.0}, 
    vec3{2.0, 0.0, 0.0}, vec3{1.0,2.0, 1.0}) ;
    cara_1->ponerIdentificador(cont);
    grafo_piramide->agregar( cara_1 );
    cont++;
   
   GrafoTriangulo * cara_2 = new GrafoTriangulo(cont,vec3{2.0, 0.0, 0.0}, 
    vec3{2.0, 0.0, 2.0}, vec3{1.0,2.0, 1.0}) ;
    cara_2->ponerIdentificador(cont);
    grafo_piramide->agregar( cara_2 );
    cont++;

    GrafoTriangulo * cara_3 = new GrafoTriangulo(cont,vec3{0.0, 0.0, 2.0}, 
    vec3{2.0, 0.0, 2.0}, vec3{1.0,2.0, 1.0}) ;
    cara_3->ponerIdentificador(cont);
    grafo_piramide->agregar( cara_3 );
    cont++;

    GrafoTriangulo * cara_4 = new GrafoTriangulo(cont,vec3{0.0, 0.0, 2.0}, 
    vec3{0.0, 0.0, 0.0}, vec3{1.0,2.0, 1.0}) ;
    cara_4->ponerIdentificador(cont);
    grafo_piramide->agregar( cara_4 );
    cont++;

    agregar(grafo_piramide);

} 
