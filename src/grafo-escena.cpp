// Nombre: Juan Carlos, Apellidos: Vílchez Sánchez, Titulación: GIM.
// email: carlosvilsan@correo.ugr.es, DNI o pasaporte: 14276362D

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación). Clase 'NodoGrafoEscena' y relacionadas.
// ** Copyright (C) 2016-2024 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
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
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 



// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( aplicacionIG != nullptr );

   //cout << "Entra " << __FUNCTION__ << ": " << leerNombre() << endl ;

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = aplicacionIG->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = aplicacionIG->pila_materiales ; assert( pila_materiales != nullptr );

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 
   // 3. Para cada entrada del vector de entradas:
   //     - si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGL'
   //     - si la entrada es de tipo transformación: componer la matriz (con 'compMM')
   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')

   if(aplicacionIG->iluminacion){
      pila_materiales->push();
   }
   
   if(tieneColor()){
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }

   cauce->pushMM();

   for(unsigned i = 0; i < entradas.size(); i++){
      switch(entradas[i].tipo){
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGL();
            break;

         case TipoEntNGE::transformacion:
            cauce->compMM(*(entradas[i].matriz));
            break;

         case TipoEntNGE::material:
            if(aplicacionIG->iluminacion)
               pila_materiales->activar(entradas[i].material);
            break;

         case TipoEntNGE::noInicializado:
            break;

      }
   }

   cauce->popMM();

   if(tieneColor()){
      cauce->popColor();
   }

   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)

   // ......
   if(aplicacionIG->iluminacion){
      pila_materiales->pop();
   }
      

}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizarGeomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')

   // .......

   cauce->pushMM();

   for(unsigned i = 0; i < entradas.size(); i++){
      switch(entradas[i].tipo){
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarGeomGL();
            break;

         case TipoEntNGE::transformacion:
            cauce->compMM(*(entradas[i].matriz));
            break;

         case TipoEntNGE::noInicializado:
            break;
         
         case TipoEntNGE::material:
            break;
      }
   }
   cauce->popMM();
}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   // .......

   cauce->pushMM();

   for(long unsigned int i = 0; i < entradas.size(); i++){
      if(entradas[i].tipo == TipoEntNGE::objeto){
         entradas[i].objeto->visualizarNormalesGL();
      }else if(entradas[i].tipo == TipoEntNGE::transformacion){
         cauce->compMM(*entradas[i].matriz);
      }
   }

   cauce->popMM();
}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( aplicacionIG != nullptr );
   Cauce * cauce = aplicacionIG->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........
   int id = leerIdentificador();

   if(id != -1){
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(id));
   }

   cauce->pushMM();

   for(unsigned int i = 0; i < entradas.size(); i++){
      switch(entradas[i].tipo){
         case TipoEntNGE::objeto:
            entradas[i].objeto->visualizarModoSeleccionGL();
         break;

         case TipoEntNGE::transformacion:
            cauce->compMM(*(entradas[i].matriz));
         break;

         case TipoEntNGE::material:
         break;

         case TipoEntNGE::noInicializado:
         break;
      }
   }

   cauce->popMM();

   if(id != -1){
      cauce->popColor();
   }


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   unsigned indice = entradas.size();
   entradas.push_back(entrada);

   return indice ; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //
   assert(indice<entradas.size());
   assert(entradas[indice].tipo == TipoEntNGE::transformacion);
   assert(entradas[indice].matriz != nullptr);
   return entradas[indice].matriz ;


}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........

   if(centro_calculado)
      return;

   int centros = 0;
   mat4 matrizModelview(1.0f);
   vec3 centro = vec3(0.0f, 0.0f, 0.0f);

   for(unsigned int i = 0; i<entradas.size(); i++){
      if(entradas[i].tipo == TipoEntNGE::transformacion){
         matrizModelview = matrizModelview * (*entradas[i].matriz);
      }else if(entradas[i].tipo == TipoEntNGE::objeto){
         entradas[i].objeto->calcularCentroOC();
         centro = centro + vec3(matrizModelview *
         vec4(entradas[i].objeto->leerCentroOC(), 1.0f));
         centros++;
      }
   }

   for(int i = 0; i < 3; i++){
      centro[i] = centro[i]/centros;
   }
   ponerCentroOC(centro);
   centro_calculado = true;

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........
   calcularCentroOC();


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........
   if(leerIdentificador() == ident_busc){
      centro_wc = leerCentroOC();
      *objeto = this;
      return true;
   }


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........
   mat4 matriz = mmodelado;

   for(unsigned int i = 0; i < entradas.size(); i++){
      if(entradas[i].tipo == TipoEntNGE::objeto){
         if(entradas[i].objeto->buscarObjeto(ident_busc, matriz, 
         objeto, centro_wc)){
            return true;
         }
      }else if(entradas[i].tipo == TipoEntNGE::transformacion){
         matriz = matriz*(*entradas[i].matriz);
      }
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

GrafoEstrellaX::GrafoEstrellaX(unsigned int n){

   unsigned int indice = agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
   
   NodoGrafoEscena * estrella = new NodoGrafoEscena();
   estrella->agregar(rotate(radians(90.0f), vec3(0.0, 1.0, 0.0)));
   estrella->agregar(scale(vec3(1.3/0.5, 1.3/0.5, 1.0)));
   estrella->agregar(translate(vec3(-0.5, -0.5, 0)));
   estrella->agregar(new EstrellaZ(n));

   agregar(estrella);

   NodoGrafoEscena * cono = new NodoGrafoEscena();
   cono->agregar(translate(vec3(0.0, 0.0, -1.3)));
   cono->agregar(rotate(radians(-90.0f), vec3(1.0, 0.0, 0.0)));
   cono->agregar(scale(vec3(0.14, 0.15, 0.14)));
   cono->agregar(new Cono(10, 25));

   agregar(cono);

   for(unsigned int i = 0; i < n; i++){
      agregar(rotate(radians(360.0f/n), vec3(1.0, 0.0, 0.0)));
      agregar(cono);
   }

   rotacion = leerPtrMatriz(indice);
}

unsigned GrafoEstrellaX::leerNumParametros() const{
   return 1;
}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   assert (iParam < leerNumParametros());

   switch(iParam){
      case 0:
         *rotacion = rotate(radians(velocidad*t_sec), vec3(1.0, 0.0, 0.0));
         break;
   }
}


GrafoCubos::GrafoCubos(unsigned int n, unsigned int m){

   
   NodoGrafoEscena * rejilla = new NodoGrafoEscena();
   rejilla->agregar(translate(vec3(-0.5, -0.5, -0.5)));
   rejilla->agregar(new RejillaY(n, m));
   agregar(rejilla);

   NodoGrafoEscena * cubo = new NodoGrafoEscena();
   unsigned int indice = cubo->agregar(rotate(0.0f, glm::vec3(1.0, 0.0, 0.0)));
   cubo->agregar(translate(vec3(0.0, -0.65, 0.0)));
   cubo->agregar(scale(vec3(0.1, 0.15, 0.1)));
   cubo->agregar(new Cubo());
   agregar(cubo);

   for(int i = 0; i < 3; i++){
      agregar(rotate(radians(90.0f), vec3(0.0, 0.0, 1.0)));
      agregar(rejilla);
      agregar(cubo);
   }
   
   agregar(rotate(radians(90.0f), vec3(1.0, 0.0, 0.0)));
   agregar(rejilla);
   agregar(cubo);

   agregar(rotate(radians(90.0f), vec3(1.0, 0.0, 0.0)));
   agregar(rotate(radians(90.0f), vec3(1.0, 0.0, 0.0)));
   agregar(rejilla);
   agregar(cubo);

   rotacion = cubo->leerPtrMatriz(indice);
}

unsigned GrafoCubos::leerNumParametros() const{
   return 1;
}

void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   assert (iParam < leerNumParametros());

   switch(iParam){
      case 0:
         *rotacion = rotate(radians(velocidad*t_sec), vec3(0.0, 1.0, 0.0));
         break;
   }
}

Coche::Coche(){

   Cubo * cubo = new Cubo();
   Cilindro * cilindro = new Cilindro(10, 25);


   NodoGrafoEscena * llanta = new NodoGrafoEscena();
   NodoGrafoEscena * rueda = new NodoGrafoEscena();

   llanta->agregar(scale(vec3(sqrt(2.0), 1.0, sqrt(2.0))));
   llanta->ponerColor(vec3(0.0, 0.0, 0.0));
   llanta->agregar(cubo);

   unsigned int indice_rueda = rueda->agregar(rotate(radians(0.0f), vec3(1.0, 0.0, 0.0)));
   rueda->agregar(scale(vec3(0.5, 0.5, 0.5)));
   rueda->agregar(rotate(radians(90.0f), vec3(0.0, 0.0, 1.0)));
   rueda->agregar(llanta);
   rueda->agregar(translate(vec3(0.0, -1.0, 0.0)));
   rueda->agregar(scale(vec3(2.0, 2.0, 2.0)));
   rueda->agregar(cilindro);

   NodoGrafoEscena * chasis = new NodoGrafoEscena();
   NodoGrafoEscena * chasis_superior = new NodoGrafoEscena();
   NodoGrafoEscena * chasis_inferior = new NodoGrafoEscena();


   chasis_inferior->ponerColor(vec3(1.0, 0.0, 0.0));
   chasis_inferior->agregar(translate(vec3(0.0, 3.0, 0.0)));
   chasis_inferior->agregar(scale(vec3(3.0, 2.0, 5.0)));
   chasis_inferior->agregar(cubo);

   chasis_superior->agregar(translate(vec3(0.0, 6.0, 0.0)));
   chasis_superior->agregar(scale(vec3(2.0, 1.0, 3.0)));
   chasis_superior->agregar(cubo);

   chasis->agregar(chasis_inferior);
   chasis->agregar(chasis_superior);

   

   NodoGrafoEscena * rueda_delantera_dcha = new NodoGrafoEscena();

   rueda_delantera_dcha->agregar(translate(vec3(3.5, 1.0, 3.0)));
   rueda_delantera_dcha->agregar(rueda);

   NodoGrafoEscena * rueda_trasera_dcha = new NodoGrafoEscena();
   rueda_trasera_dcha->agregar(translate(vec3(3.5, 1.0, -3.0)));
   rueda_trasera_dcha->agregar(rueda);

   NodoGrafoEscena * rueda_delantera_izqda = new NodoGrafoEscena();
   rueda_delantera_izqda->agregar(translate(vec3(-3.5, 1.0, 3.0)));
   rueda_delantera_izqda->agregar(rueda);

   NodoGrafoEscena * rueda_trasera_izqda = new NodoGrafoEscena();
   rueda_trasera_izqda->agregar(translate(vec3(-3.5, 1.0, -3.0)));
   rueda_trasera_izqda->agregar(rueda);

   unsigned int indice_coche = agregar(rotate(radians(0.0f), vec3(1.0, 0.0, 0.0)));

   agregar(translate(vec3(10.0, 0.0 , 0.0)));
   agregar(chasis);
   agregar(rueda_delantera_dcha);
   agregar(rueda_delantera_izqda);
   agregar(rueda_trasera_dcha);
   agregar(rueda_trasera_izqda);

   rotacion_rueda = rueda->leerPtrMatriz(indice_rueda);
   rotacion_coche = leerPtrMatriz(indice_coche);
}

unsigned Coche::leerNumParametros() const{
   return 2;
}

void Coche::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   assert (iParam < leerNumParametros());

   switch(iParam){
      case 0:
         *rotacion_rueda = rotate(radians(v_rotacion_rueda*t_sec), vec3(1.0, 0.0, 0.0));
         break;

      case 1:
         *rotacion_coche = rotate(radians(v_coche*t_sec), vec3(0.0, 1.0, 0.0));
         break;
   }
}



Trifuerza::Trifuerza(){

   Triangulo_Boton * triangulo = new Triangulo_Boton();
   triangulo->ponerColor(vec3(1, 0.84, 0));

   NodoGrafoEscena * triangulo_1 = new NodoGrafoEscena();
   NodoGrafoEscena * triangulo_2 = new NodoGrafoEscena();
   NodoGrafoEscena * triangulo_3 = new NodoGrafoEscena();

   unsigned int indice_1 = triangulo_1->agregar(rotate(0.0f, vec3(1.0, 0.0, 0.0)));
   traslacion_1 = triangulo_1->leerPtrMatriz(indice_1);
   triangulo_1->agregar(translate(vec3(-0.5, 0.0, 0.0)));
   triangulo_1->agregar(triangulo);

   unsigned int indice_2 = triangulo_2->agregar(rotate(0.0f, vec3(1.0, 0.0, 0.0)));
   traslacion_2 = triangulo_2->leerPtrMatriz(indice_2);
   triangulo_2->agregar(translate(vec3(0.5, 0.0, 0.0)));
   triangulo_2->agregar(triangulo);
   

   unsigned int indice_3 = triangulo_3->agregar(rotate(0.0f, vec3(1.0, 0.0, 0.0)));
   traslacion_3 = triangulo_3->leerPtrMatriz(indice_3);
   triangulo_3->agregar(translate(vec3(0.0, sqrt(3.0) - sqrt(0.75), 0.0)));
   triangulo_3->agregar(triangulo);
   
 
   agregar(triangulo_1);
   agregar(triangulo_2);
   agregar(triangulo_3);
   
}

unsigned Trifuerza::leerNumParametros() const{
   return 3;
}

void Trifuerza::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   assert (iParam < leerNumParametros());

   switch(iParam){
      case 0:
         *traslacion_1 = translate(vec3(1.0*abs(sin(t_sec)), 0.0, 0.0));
         break;

      case 1:
         *traslacion_2 = translate(vec3(-0.5*abs(sin(t_sec)), sqrt(0.75)*abs(sin(t_sec)),0.0));
         break;

      case 2:
         *traslacion_3 = translate(vec3(-0.5*abs(sin(t_sec)), -sqrt(0.75)*abs(sin(t_sec)),0.0));
         break;
   }
}

NodoCubo24::NodoCubo24(){
   NodoGrafoEscena *nodo_cubo_24 = new NodoGrafoEscena();
    Textura * textura_ugr = new Textura("window-icon.jpg");
    Material * material_cubo_24 = new Material(textura_ugr, 0.4, 0.1, 1.0, 4.0);
    MallaInd *cubo = new Cubo24();
    nodo_cubo_24->agregar(material_cubo_24);
    nodo_cubo_24->agregar(cubo);
    agregar(nodo_cubo_24);

}

NodoDiscoP4E1::NodoDiscoP4E1()
{
   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
   Textura * textura_nododiscop4 = new TexturaXY("cuadricula.jpg");
   Material * material_nododiscop4 = new Material(textura_nododiscop4, 0.5, 0.5, 0.5, 10);
   agregar(material_nododiscop4);
   agregar(new MallaDiscoP4E1());
}

NodoDiscoP4E2::NodoDiscoP4E2()
{
   ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
   Textura * textura_nododiscop4 = new Textura("cuadricula.jpg");
   Material * material_nododiscop4 = new Material(textura_nododiscop4, 0.5, 0.5, 0.5, 10);
   agregar(material_nododiscop4);
   agregar(new MallaDiscoP4E2());
}

GrafoEsferasP5::GrafoEsferasP5()
{
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float
      e = 0.4/n_esferas_x_fila ;
   
   agregar( glm::scale( vec3{e,e,e} ));

   int cont = 1;
   
   for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
   {

      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;

      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
         MiEsferaE1 * esfera = new MiEsferaE1(i,j) ;
         esfera->ponerIdentificador(cont);
         fila_esferas->agregar( glm::translate( vec3{2.2, 0.0, 0.0} ));
         fila_esferas->agregar( esfera );
         cont++;
      }
      agregar( fila_esferas );
      agregar( glm::translate( vec3{0.0, 0.0, 5.0} ));
   }
}

bool MiEsferaE1::cuandoClick(const glm::vec3 &centro) {
   std::cout << "Se ha seleccionado la " << leerNombre() << std::endl ;
   return true ;
}

MiEsferaE1::MiEsferaE1(unsigned int i, unsigned int j) 
{
   std::string nom_temp = "Esfera Nº "; 
   nom_temp += std::to_string(j+1);
   nom_temp += " de la fila ";
   nom_temp += std::to_string(i+1);

   ponerNombre(nom_temp);
   agregar( new Esfera(100,100) );
}

GrafoEsferasP5_2::GrafoEsferasP5_2()
{
   const unsigned
      n_filas_esferas = 8,
      n_esferas_x_fila = 5 ;
   const float
      e = 2.5/n_esferas_x_fila ;
   
   agregar( glm::scale( vec3{e,e,e} ));

   int cont = 1;
   
   for( unsigned i = 0 ; i < n_filas_esferas ; i++ )
   {

      NodoGrafoEscena * fila_esferas = new NodoGrafoEscena() ;
      fila_esferas->agregar( glm::translate( vec3{3.0, 0.0, 0.0} ));

      for( unsigned j = 0 ; j < n_esferas_x_fila ; j++ )
      {
         MiEsferaE2 * esfera = new MiEsferaE2(i,j) ;
         esfera->ponerIdentificador(cont);
         fila_esferas->agregar( glm::translate( vec3{2.5, 0.0, 0.0} ));
         fila_esferas->agregar( esfera );
         cont++;
      }
      agregar( fila_esferas );
      agregar( glm::rotate(radians(float(360.0/n_filas_esferas)), glm::vec3{0.0, 1.0, 0.0} ));
   }
}

bool MiEsferaE2::cuandoClick(const glm::vec3 &centro) {
   std::cout << "Se ha seleccionado la " << leerNombre() << std::endl ;
   if (leerColor() == glm::vec3(1.0, 1.0, 1.0)) {
      ponerColor(glm::vec3(1.0, 0.0, 0.0));
      std::cout << "Se ha cambiado el color de la esfera de Blanco a Rojo" <<  std::endl ;
   } else {
      ponerColor(glm::vec3(1.0, 1.0, 1.0));
      std::cout << "Se ha cambiado el color de la esfera de Rojo a Blanco" <<  std::endl ;
   }
   return true ;
}

MiEsferaE2::MiEsferaE2(unsigned int i, unsigned int j) 
{
   ponerColor(glm::vec3(1.0, 1.0, 1.0));
   agregar( new Esfera(100,100) );
}