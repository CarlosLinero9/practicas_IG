// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación). Clase 'MallaInd' y derivadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************


#include "ig-aux.h"
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent'
#include <cmath> // para operaciones con seno y coseno 
#include <vector>

using namespace std;
using namespace glm;

// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....
   for(unsigned int i = 0; i<nt; i++){
      vec3 p = vertices[triangulos[i][0]];
      vec3 q = vertices[triangulos[i][1]];
      vec3 r = vertices[triangulos[i][2]];

      vec3 a = q-p;
      vec3 b = r-p;

      vec3 producto = cross(a,b);

      vec3 normalizado;

      if(length(producto) != 0.0){
         normalizado = normalize(producto);
      }else{
         normalizado = vec3(0.0, 0.0, 0.0);
      }

      nor_tri.push_back(normalizado);
   }

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......
   calcularNormalesTriangulos();

   nor_ver = vector<vec3>(vertices.size(), vec3(0.0, 0.0, 0.0));

   for(unsigned int i = 0; i < triangulos.size(); i++){
      nor_ver[triangulos[i][0]] = nor_ver[triangulos[i][0]] + nor_tri[i];
      nor_ver[triangulos[i][1]] = nor_ver[triangulos[i][1]] + nor_tri[i];
      nor_ver[triangulos[i][2]] = nor_ver[triangulos[i][2]] + nor_tri[i];
   }

   for(long unsigned int i = 0; i < nor_ver.size(); i++){
      if(length(nor_ver[i])!= 0.0){
         nor_ver[i] = normalize(nor_ver[i]);
      }
   }

}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')
   if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   //
   if(dvao == nullptr){
      dvao = new DescrVAO(numero_atributos_cauce, new DescrVBOAtribs(ind_atrib_posiciones,
                                                         vertices));

      
      dvao->agregar( new DescrVBOInds( triangulos ));

      if ( col_ver.size() > 0)
         dvao->agregar( new DescrVBOAtribs( ind_atrib_colores, col_ver ));
      if ( nor_ver.size() > 0)
         dvao->agregar( new DescrVBOAtribs( ind_atrib_normales, nor_ver ));
      if ( cc_tt_ver.size() > 0 )
         dvao->agregar( new DescrVBOAtribs( ind_atrib_coord_text, cc_tt_ver ));
   }

   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'
   dvao->draw(GL_TRIANGLES); 

   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce
   if(tieneColor()){
      cauce->popColor();
   }

}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
   if ( col_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_colores, false);
   if ( nor_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_normales, false);
   if ( cc_tt_ver.size() > 0 )
      dvao->habilitarAtrib(ind_atrib_coord_text, false);

   //    2. Dibujar la malla (únicamente visualizará los triángulos), se usa el método 'draw' del VAO (dvao)
   dvao->draw(GL_TRIANGLES); //???

   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
   // ....
   if ( col_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_colores, true);
   if ( nor_ver.size() > 0)
      dvao->habilitarAtrib(ind_atrib_normales, true);
   if ( cc_tt_ver.size() > 0 )
      dvao->habilitarAtrib(ind_atrib_coord_text, true);

}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

   if(dvao_normales == nullptr){
      float x = 0.20f;
      for(unsigned int i = 0; i < vertices.size(); i++){
         segmentos_normales.push_back(vertices[i]);
         segmentos_normales.push_back(vertices[i] + (x*nor_ver[i]));
      }
      dvao_normales = new DescrVAO(numero_atributos_cauce, new DescrVBOAtribs(ind_atrib_posiciones, 
      segmentos_normales));
   }

   dvao_normales->draw(GL_LINES);



}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //
   int id = leerIdentificador();

   if(id != -1){
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(id));
   }

   visualizarGeomGL();

   if(id != -1){
      cauce->popColor();
   }

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................
   calcularNormales();
}

// ****************************************************************************
// Clase 'Cubo'

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

      

      calcularNormales();

}

// ****************************************************************************
// Clase 'Tetraedro'

Tetraedro::Tetraedro()
:  MallaInd( "tetraedro 4 vértices" )
{

   // Definición de los vértices del tetraedro
   vertices = {
      {0.0, 1.0, 0.0},   // Vértice 0 (cima)
      {-1.0, -1.0, -1.0}, // Vértice 1 (base)
      {1.0, -1.0, -1.0},  // Vértice 2 (base)
      {0.0, -1.0, 1.0}    // Vértice 3 (base)
  };

  // Definición de las caras del tetraedro (triángulos)
  triangulos = {
      {0, 1, 2}, // Cara 1
      {0, 2, 3}, // Cara 2
      {0, 3, 1}, // Cara 3
      {1, 2, 3}   // Cara 4
  };

  // Asignar un color diferente al tetraedro (por ejemplo, rojo)
  glm::vec3 nuevo_color = {1.0f, 0.0f, 0.0f};
  ponerColor(nuevo_color); // Color rojo

  calcularNormales();

}

// ****************************************************************************
// Clase 'Triangulo Botón'

Triangulo_Boton::Triangulo_Boton()
:  MallaInd( "triangulo con volumen" )
{

   vertices =
   {
      {-0.5, -0.0, -0.0},
      {+0.5, -0.0, +0.0},
      {-0.0, sqrt(0.75), -0.0},
      {-0.5, -0.0, -0.5},
      {+0.5, -0.0, -0.5},
      {-0.0, sqrt(0.75), -0.5},
   };

   triangulos = {
      {0, 1, 2},  
      {3, 4, 5},  
      {0, 3, 4},  
      {0, 4, 1},
      {1, 4, 5},
      {1, 5, 2},
      {2, 5, 3},
      {2, 3, 0},
      
   };

    calcularNormales();
}

// ****************************************************************************
// Clase 'CuboColores'

CuboColores::CuboColores()
:  MallaInd( "cubocolores 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   col_ver={{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1}, {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
   calcularNormales();
   
}



// -----------------------------------------------------------------------------------------------

/*
EJERCICIO 1
*/
EstrellaZ::EstrellaZ (int n)
: MallaInd("estrella de colores de n puntas"){

   assert(n > 1);
   vertices.push_back({0.5, 0.5, 0});
   col_ver.push_back({1, 1, 1});
   float x, y, z;
   z=0;
   unsigned int n_vert = 2 * n;
   float re= 0.5;
   float ri = 0.2;
   float ang = 360 / n_vert;
   float ang_aux = 0;

   for(unsigned int i = 0; i < n_vert; i++){
      if(i%2 == 0)
      {
         x = re*cos(ang_aux * M_PI/180) + 0.5;
         y= 0.5 + re * sin(ang_aux * M_PI/180) ;
      }
      else
      {
         x = ri*cos(ang_aux * M_PI/180) + 0.5;
         y= 0.5 + ri * sin(ang_aux * M_PI/180) ;
      }
      ang_aux += ang ;
      vertices.push_back({x , y, z});
      col_ver.push_back({x, y, z});
   }

   triangulos.push_back({0, 1, 2});
   triangulos.push_back({0, 1, vertices.size()-1});

   for ( unsigned int i = 3 ; i < vertices.size(); i+=2){
      triangulos.push_back({0, i, i-1});
      triangulos.push_back({0, i, i+1});
   }
}

// -----------------------------------------------------------------------------------------------

/*
EJERCICIO 2
*/

CasaX::CasaX()
: MallaInd("Casa X")
{
      vertices =
      {  {  0.0,  0.0,  0.0 }, // 0
         {  0.0,  0.0,  0.5 }, // 1
         {  0.0,  0.5,  0.0 }, // 2
         {  0.0,  0.5,  0.5 }, // 3
         {  0.5,  0.0,  0.0 }, // 4
         {  0.5,  0.0,  0.5 }, // 5
         {  0.5,  0.5,  0.0 }, // 6
         {  0.5,  0.5,  0.5 }, // 7
         {  0.25,  0.625,  0.0 }, // 8
         {  0.25,  0.625,  0.5 }, // 9

      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3},  // Z+ (+1)

         {3,7,9},  // Tejado frontal_1
         {8,2,6},  // Tejado frontal_2

         {9,6,7}, // Tejado dcha_arriba
         {9,6,8}, // Tejado dcha_abajo

         {3,2,9}, // Tejado izqda_arriba
         {2,8,9} // Tejado izqda_arriba
      } ;

      col_ver = 
      {  {  0.0,  0.0,  0.0 }, // 0
         {  0.0,  0.0,  0.5 }, // 1
         {  0.0,  0.5,  0.0 }, // 2
         {  0.0,  0.5,  0.5 }, // 3
         {  0.5,  0.0,  0.0 }, // 4
         {  0.5,  0.0,  0.5 }, // 5
         {  0.5,  0.5,  0.0 }, // 6
         {  0.5,  0.5,  0.5 }, // 7
         {  0.25,  0.625,  0.0 }, // 8
         {  0.25,  0.625,  0.5 }, // 9
      } ;      
}

// -----------------------------------------------------------------------------------------------

/*
EJERCICIO 3
*/

MallaTriangulo::MallaTriangulo()
   : MallaInd("Malla de 1 triangulo")
{
   vertices =
   {
      {-0.5, -0.0, -0.0},
      {+0.5, -0.0, +0.0},
      {-0.0, +sqrt(2.0), -0.0},
   };

   triangulos = {{0, 1, 2}};
   cc_tt_ver = {{1,0}, {0,0}, {0.5, -1}};
}

MallaCuadrado::MallaCuadrado()
   : MallaInd("Malla de 1 cuadrado")
{
   vertices =
   {
      {-1.0, -1.0, -0.0}, 
      {+1.0, -1.0, -0.0}, 
      {-1.0, +1.0, -0.0},
      {+1.0, +1.0, -0.0}, 
   };

   triangulos = {{0, 1, 3}, {0, 3, 2}};
}

MallaPiramideL::MallaPiramideL()
   : MallaInd( "Malla de piramide en forma de L" )
{
   vertices =
   {
      {-0.0, -0.0, -0.0},
      {+1.0, -0.0, +0.0},
      {+1.0, -0.0, +0.5},
      {+0.5, -0.0, +0.5}, 
      {+0.5, -0.0, +1.0},
      {+0.0, -0.0, +1.0},
      {+0.0, +1.0, -0.0},
   };

   triangulos =
   {
      {0, 1, 5}, 
      {1, 2, 3},
      {3, 4, 5}, 
      {0, 5, 6},
      {0, 1, 6},
      {4, 5, 6},
      {3, 4, 6},
      {2, 3, 6},
      {1, 2, 6}
   };
}


// -----------------------------------------------------------------------------------------------

/*
EJERCICIO 1
*/
PiramideEstrellaZ::PiramideEstrellaZ (int n)
: MallaInd("Piramide estrella de colores de n puntas"){

   vertices.push_back({0.5, 0.5, 0});
   col_ver.push_back({1, 1, 1});
   float x, y, z;
   z=0;
   unsigned int n_vert = 2 * n;
   float re= 0.5;
   float ri = 0.2;
   float ang = 360 / n_vert;
   float ang_aux = 0;

   for(unsigned int i = 0; i < n_vert; i++){
      if(i%2 == 0)
      {
         x = re*cos(ang_aux * M_PI/180) + 0.5;
         y= 0.5 + re * sin(ang_aux * M_PI/180) ;
      }
      else
      {
         x = ri*cos(ang_aux * M_PI/180) + 0.5;
         y= 0.5 + ri * sin(ang_aux * M_PI/180) ;
      }
      ang_aux += ang ;
      vertices.push_back({x , y, z});
      col_ver.push_back({x, y, z});
   }
   int ultimo_vert = vertices.size()-1;

   triangulos.push_back({0, 1, 2});
   triangulos.push_back({0, 1, vertices.size()-1});

   for ( unsigned int i = 3 ; i < vertices.size(); i+=2){
      triangulos.push_back({0, i, i-1});
      triangulos.push_back({0, i, i+1});
   }

   vertices.push_back({0.5, 0.5, 1});
   col_ver.push_back({1, 1, 1});

   triangulos.push_back({vertices.size()-1, 1, 2});
   triangulos.push_back({vertices.size()-1, 1, ultimo_vert});

   for ( unsigned int i = 3 ; i < n_vert; i+=2){
      triangulos.push_back({vertices.size()-1, i, i-1});
      triangulos.push_back({vertices.size()-1, i, i+1});
   }

}

// -----------------------------------------------------------------------------------------------

/*
EJERCICIO 2
*/
RejillaY::RejillaY(unsigned int n, unsigned int m)
: MallaInd("RejillaY"){

   assert(n > 0 && m > 0);
   
  
   for ( unsigned int i = 0 ; i < n; i++){
      for(unsigned int j = 0; j < m; j++){
         vertices.push_back({float(i)/(n-1), 0, float(j)/(m-1)});
         col_ver.push_back({float(i)/(n-1), 0, float(j)/(m-1)});
      }
   }


   for ( unsigned int i = 0 ; i < (n-1); i++){
      for(unsigned int j = 0; j < (m-1); j++){
         triangulos.push_back({i*m + j, i*m + j+1, (i+1)*m + j});
         triangulos.push_back({(i+1)*m + j+1, i*m + j+1, (i+1)*m + j});
      }
   }
}

// -----------------------------------------------------------------------------------------------

/*
EJERCICIO 3
*/
MallaTorre::MallaTorre(unsigned int n)
: MallaInd("MallaTorre"){

   assert(n > 0);
  
   for ( unsigned int i = 0 ; i <= n; i++){
      vertices.push_back({-0.5, float(i), +0.5});
      vertices.push_back({+0.5, float(i), +0.5});
      vertices.push_back({+0.5, float(i), -0.5});
      vertices.push_back({-0.5, float(i), -0.5});   
   }

   for ( unsigned int i = 0 ; i < n; i++){
      triangulos.push_back({i*4, (i+1)*4, i*4 + 1});
      triangulos.push_back({(i+1)*4 + 1, (i+1)*4, i*4 + 1});

      triangulos.push_back({i*4 + 1, (i+1)*4 +1 , i*4 + 2});
      triangulos.push_back({(i+1)*4 + 1, (i+1)*4 + 2, i*4 + 2});

      triangulos.push_back({i*4 + 2, (i+1)*4 + 2, i*4 + 3});
      triangulos.push_back({(i+1)*4 + 2, (i+1)*4 + 3, i*4 + 3});

      triangulos.push_back({i*4 + 3, (i+1)*4 + 3, i*4});
      triangulos.push_back({(i+1)*4 + 3, (i+1)*4, i*4 + 3});
        
   }
}

Cubo24::Cubo24()
:MallaInd("Cubo24"){

   //Definimos los los 24 vértices del cubo
vertices =
      {  { -1.0, -1.0, -1.0 },  
         { -1.0, -1.0, -1.0 }, 
         { -1.0, -1.0, -1.0 }, 
         { -1.0, -1.0, +1.0 }, 
         { -1.0, -1.0, +1.0 },  
         { -1.0, -1.0, +1.0 },  
         { -1.0, +1.0, -1.0 },  
         { -1.0, +1.0, -1.0 }, 
         { -1.0, +1.0, -1.0 }, 
         { -1.0, +1.0, +1.0 }, 
         { -1.0, +1.0, +1.0 }, 
         { -1.0, +1.0, +1.0 },  
         { +1.0, -1.0, -1.0 }, 
         { +1.0, -1.0, -1.0 }, 
         { +1.0, -1.0, -1.0 }, 
         { +1.0, -1.0, +1.0 }, 
         { +1.0, -1.0, +1.0 }, 
         { +1.0, -1.0, +1.0 }, 
         { +1.0, +1.0, -1.0 }, 
         { +1.0, +1.0, -1.0 }, 
         { +1.0, +1.0, -1.0 }, 
         { +1.0, +1.0, +1.0 }, 
         { +1.0, +1.0, +1.0 }, 
         { +1.0, +1.0, +1.0 }, 
      } ;

   triangulos =
      {  {9,0,3}, {0,9,6}, 
         {10,4,15}, {15,21,10}, 

         {22,16,18}, {16,12,18}, 
         {13,1,19}, {1,7,19}, 

         {8,11,20}, {11,23,20}, 
         {17,5,2}, {17,2,14}  
      };


   cc_tt_ver = 
      {  {0.0, 1.0},     
         {1.0, 1.0},      
         {1.0, 0.0},      
         {1.0, 1.0},      
         {0.0, 1.0},     
         {1.0, 1.0},     
         {0.0, 0.0},      
         {1.0, 0.0},     
         {1.0, 0.0},       
         {1.0, 0.0},     
         {0.0, 0.0},      
         {0.0, 0.0},     
         {1.0, 1.0},     
         {0.0, 1.0},        
         {0.0, 0.0},     
         {1.0, 1.0},       
         {0.0, 1.0},     
         {0.0, 1.0},     
         {1.0, 0.0},      
         {0.0, 0.0},      
         {1.0, 1.0},     
         {1.0, 0.0},      
         {0.0, 0.0},      
         {0.0, 1.0},       
      };

   //cout << "Calculo normales del cubo: " << endl;
   calcularNormales();
   
   
}

MallaDiscoP4E1::MallaDiscoP4E1()
{
   ponerColor({1.0, 1.0, 1.0});
   const unsigned ni = 100, nj = 100 ;
   for( unsigned i= 0 ; i < ni ; i++ )
   for( unsigned j= 0 ; j < nj ; j++ )
   {
      const float
      fi = float(i)/float(ni-1),
      fj = float(j)/float(nj-1),
      ai = 2.0*M_PI*fi,
      x  = fj * cos( ai ),
      y  = fj * sin( ai ),
      z  = 0.0 ;
      vertices.push_back({ x, y, z });
   }
   for( unsigned i= 0 ; i < ni-1 ; i++ )
   for( unsigned j= 0 ; j < nj-1 ; j++ )
   {
      triangulos.push_back({ i*nj+j, i*nj+(j+1), (i+1)*nj+(j+1) });
      triangulos.push_back({ i*nj+j, (i+1)*nj+(j+1), (i+1)*nj+j });
   }
}

MallaDiscoP4E2::MallaDiscoP4E2()
{
   ponerColor({1.0, 1.0, 1.0});
   const unsigned ni = 100, nj = 100 ;
   for( unsigned i= 0 ; i < ni ; i++ )
   for( unsigned j= 0 ; j < nj ; j++ )
   {
      const float
      fi = float(i)/float(ni-1),
      fj = float(j)/float(nj-1),
      ai = 2.0*M_PI*fi,
      x  = fj * cos( ai ),
      y  = fj * sin( ai ),
      z  = 0.0 ;
      vertices.push_back({ x, y, z });
      cc_tt_ver.push_back({ fi, fj });
   }
   for( unsigned i= 0 ; i < ni-1 ; i++ )
   for( unsigned j= 0 ; j < nj-1 ; j++ )
   {
      triangulos.push_back({ i*nj+j, i*nj+(j+1), (i+1)*nj+(j+1) });
      triangulos.push_back({ i*nj+j, (i+1)*nj+(j+1), (i+1)*nj+j });
   }
}




