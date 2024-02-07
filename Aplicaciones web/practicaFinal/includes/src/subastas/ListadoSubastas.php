<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;
use DateTime;

class ListadoSubastas extends Formulario
{
    public function __construct() {
        parent::__construct('formObjeto', ['urlRedireccion' => Aplicacion::getInstance()->resuelve('/index.php')]);
    }
    
    
    static function listadoActualizar($busqueda){
        $subastas = Subasta::listarSubastas($busqueda);
 
       
        $html ="";
   
    
       foreach($subastas as $subasta) {
          
            $html .= visualizaSubasta($subasta,"actualizar");
          // echo($subasta);
       }
        
       
        return $html;
    }


static function listadoCompradas($busqueda){
        $subastas = Subasta::listarSubastas($busqueda);
 
        $html = ""; 
   
    
       foreach($subastas as $subasta) {
          
            $html .= visualizaSubasta($subasta,"compradas");
          // echo($subasta);
       }
        
       $html .= "</table>";
        return $html;
    }

    static function listadoUnicaSubasta($id){
        $subasta = Subasta::buscaPorId($id);
        $imagen=Imagen::buscaPorsubasta($id);

        $hacerpuja= new \es\ucm\fdi\aw\subastas\HacerPuja();
        $fecha_actual = new DateTime();
        $fecha_dada = new DateTime($subasta->getFechaFin());
        $intervalo = $fecha_dada->diff($fecha_actual);
       // $fechafin=$intervalo->format('%d D:%H H:%I M:%S S');
        $fechafin=$fecha_dada->format('M d, Y H:i:s');
        $rutaimagen="";
        if($imagen!=false){
        $rutaimagen=RUTA_ALMACEN_BAJADA.$imagen->getRuta();
        }
        $app = Aplicacion::getInstance();
        $html = <<<EOF
                    <div class="containervendedorproducto">
                    <div class="product-info">
                    <div class="product-image">
                    <img src="{$rutaimagen}" alt="Producto">
                    </div>
                    <div class="product-details">
                    <div class="product-title">
                        <h1>{$subasta->getTitulo()}</h1>
                    </div>
                    <div class="product-status">
                        <p>Estado: {$subasta->getEstado()}</p>
                        <p>Categoría: {$subasta->getCategoria()}</p>
                        <p id="contador">Tiempo Restante: {$fechafin} </p>
                        <p class="current-bid">Puja Actual: {$subasta->getPrecioActual()}€</p>
                    </div>

                    EOF;       

                            
                                 $vendedor= \es\ucm\fdi\aw\usuarios\Usuario::buscaPorId($subasta->getIdUsuario());
                               
                 $html .=<<<EOF

                    </div>
                </div>
                
                <div class="seller-info">
                    <h2>Información del Vendedor</h2>
                    <p>Nombre de Usuario: {$vendedor->getNombreUsuario()} ( )</p>
                    <a href="#">Ver más Artículos</a>
                    <a href="#">Contactar al Vendedor</a>
                </div>
                </div>
                
     EOF;       
                        
    
       
        return $html;
    }



    static function listadoPujar($busqueda,$buscar=null){
        $subastas = Subasta::listarSubastas($busqueda,$buscar);
        $titulosCol = mostrarTitulosTabla();

        $html ="";
        $cont=0;
    
       foreach($subastas as $subasta) {
        $cont=$cont+1;
            $html .= visualizaSubasta($subasta,"pujar");
          // echo($subasta);
       }
        
       
        return $html;
    }

    static function formularioSubastas($Subastasvisibles){
        $subastas= \es\ucm\fdi\aw\subastas\Subasta::listarSubastas("");
        
         $contenidoPrincipal="";
         $rutaimagen="";
            for($contador=0;$contador<$Subastasvisibles;$contador++) {  
                $imagen=Imagen::buscaPorsubasta($contador);
        if($imagen!=false){
            $rutaimagen=RUTA_ALMACEN_BAJADA.$imagen->getRuta();
            }
                $contenidoPrincipal .=  parent::formulariosvisiblesindex("$rutaimagen","idsubasta", RUTA_APP.'\vistaUnicaSubasta.php',"GET",$subastas[$contador]->getIdSubasta(),$subastas[$contador]->getTitulo());
            }
            return $contenidoPrincipal;
        }

    protected function generaCamposFormulario(&$datos)
    {
       
        $tipo = $datos['TipoSubasta'] ?? '';
        $estado = $datos['Estado'] ?? '';
        $relevancia = $datos['Relevancia'] ?? '';

        // Se generan los mensajes de error si existen.
        $htmlErroresGlobales = self::generaListaErroresGlobales($this->errores);
        $erroresCampos = self::generaErroresCampos(['TipoSubasta', 'Estado', 'Relevancia'], $this->errores, 'span', array('class' => 'error'));

        $html = <<<EOF
        $htmlErroresGlobales
        //Creamos aqui la parte fija del codigo HTML
        <form method="post">
            <p>Todas</p>
            <select name="TipoSubasta" value="$tipo">
                <option>Tipo de subasta</option>
                <optgroup>
                    <option>opcion1</option>
                </optgroup>
            </select>
            $erroresCampos[TipoSubasta]
            <select name="Estado" value="$estado">
                <option>Estado</option>
                <optgroup>
                    <option>opcion1</option>
                </optgroup>
            </select>
            $erroresCampos[Estado]
            <p>Ordenar</p>
            <select name="Relevancia" value="$relevancia">
                <option>Relevancia</option>
                <optgroup>
                    <option>opcion1</option>
                </optgroup>
            </select>
            $erroresCampos[Relevancia]
        </form>
        EOF;
        return $html;
    }

    

    protected function procesaFormulario(&$datos)
    {
       
        $tipo = $datos['TipoSubasta'] ?? '';
        $estado = $datos['Estado'] ?? '';
        $relevancia = $datos['Relevancia'] ?? '';



        $app = Aplicacion::getInstance();
        $idUsuario = $app->idUsuario();
        
      
        $subastas = array(); // Declarar $subastas como un array vacío
        $resultados = Subasta::buscaSubasta("");
        echo ($resultados->getEstado());
        // Agregar cada objeto Subasta devuelto por el método al array $subastas
        foreach ($resultados as $fila) {
            $subasta = new Subasta($fila['id_usuario'], $fila['titulo'], $fila['descripcion'], $fila['fecha_inicio'], $fila['fecha_fin'], $fila['precio_inicial'], $fila['precio_actual'], $fila['categoria'], $fila['estadoproducto'], $fila['id_subasta'], $fila['id_ganador'], $fila['estado']);
            array_push($subastas, $subasta); // o también: $subastas[] = $subasta;
        }
        echo "<table>";
        echo "<tr><th>ID</th><th>Titulo</th><th>Descripcion</th><th>Fecha de inicio</th><th>Fecha de fin</th><th>Precio inicial</th><th>Precio actual</th><th>ID ganador</th><th>Estado</th><th>Categoria</th></tr>";
        foreach ($subastas as $subasta) {
            echo "<tr>";
            echo "<td>" . $subasta->getIdSubasta() . "</td>";
            echo "<td>" . $subasta->getTitulo() . "</td>";
            echo "<td>" . $subasta->getDescripcion() . "</td>";
            echo "<td>" . $subasta->getFechaInicio() . "</td>";
            echo "<td>" . $subasta->getFechaFin() . "</td>";
            echo "<td>" . $subasta->getPrecioInicial() . "</td>";
            echo "<td>" . $subasta->getPrecioActual() . "</td>";
            echo "<td>" . $subasta->getIdGanador() . "</td>";
            echo "<td>" . $subasta->getEstado() . "</td>";
            echo "<td>" . $subasta->getCategoria() . "</td>";
            echo "</tr>";
        }
        echo "</table>";      
    }
}
function mostrarTitulosTabla()
{
    $html = <<<EOF
    <table>
        <tr>
            <th>Titulo</th>
            <th>Descripcion</th>
            <th>Fecha de inicio</th>
            <th>Fecha de fin</th>
            <th>Precio inicial</th>
            <th>Precio actual</th>
            <th>ID ganador</th>
            <th>Estado</th>
            <th>Categoria</th>                           
EOF;
    return $html;

}

function listasubastas($busqueda)
{
   
    
    $subastas = Subasta::listarSubastas($busqueda);
    $titulosCol = mostrarTitulosTabla();
 
  
    $html = <<<EOF
        <div class="listing">
            
                
EOF;

   foreach($subastas as $subasta) {
      
        $html .= visualizaSubasta($subasta);
      
   }
    
   
    return $html;
}

function visualizaSubasta($subasta, $tipo=null) {
    $fecha_actual = new DateTime();
    $fecha_dada = new DateTime($subasta->getFechaFin());
    $intervalo = $fecha_dada->diff($fecha_actual);
    //$fechafin=$intervalo->format('%d D:%H H:%I M:%S S');
    $fechafin=$fecha_dada->format('M d, Y H:i:s');
    $rutaimagen="";
    $imagen=Imagen::buscaPorsubasta($subasta->getIdSubasta());
    if($imagen!=false){
        $rutaimagen=RUTA_ALMACEN_BAJADA.$imagen->getRuta();
        }
    $nombreVendedor = \es\ucm\fdi\aw\usuarios\Usuario::buscaPorId($subasta->getIdUsuario());
    $nombreVendedor = $nombreVendedor->getNombre();
    $html = <<<EOF
            <div class="item">
        <div class="image">
                <img src="{$rutaimagen}" alt="Producto 1">
            </div>
            <div class="details">
                <div class="title"> <a href="vistaUnicaSubasta.php?idsubasta={$subasta->getIdSubasta()}">{$subasta->getTitulo()}</a></div>
                <div class="status">Estado: {$subasta->getEstado()}</div>
                <div class="seller">Vendedor: {$nombreVendedor}</div>
                <div class="price">{$subasta->getPrecioActual()}€</div>
                <div class="bid-info">
                <span class="bids">x pujas</span>
                 <p id="contador">Tiempo Restante: {$fechafin} </p>
                </div>
                </div>
                <div class="buttons-container">
        
    EOF;

    switch ($tipo) {
        
        case 'actualizar':
            $html .= <<<EOF
                <td>
                    <form method="POST" action="vistaModificarSubastas.php">
                        <input type="hidden" name="borrar" value="borrarSubasta">
                        <input type="hidden" name="parametro" value="{$subasta->getIdSubasta()}">
                        <button type="submit">Borrar</button>
                    </form>
                </td>
                <td>
                    <form method="POST" action="addSubasta.php">
                        <input type="hidden" name="actualizar" value="actualizarSubasta">
                        <input type="hidden" name="idsubasta" value="{$subasta->getIdSubasta()}">
                        <input type="hidden" name="precioactual" value="{$subasta->getPrecioActual()}">
                        <input type="hidden" name="idganador" value="{$subasta->getIdGanador()}">
                        <button type="submit">Actualizar</button>
                    </form>
                </td>
                
            EOF;
        break;
        case 'compradas':
            $html .= <<<EOF
            
                    <form method="POST" action="addSubasta.php">                        
                    </form>
                
            <td>
                <form method="POST" action="addValoracionProducto.php">
                    <input type="hidden" name="valorar" value="valorarSubasta">
                    <input type="hidden" name="idsubasta" value="{$subasta->getIdSubasta()}">
                    <input type="hidden" name="idvendedor" value="{$subasta->getIdUsuario()}">
                    <input type="hidden" name="idganador" value="{$subasta->getIdGanador()}">
                    <input type="hidden" name="tituloproducto" value="{$subasta->getTitulo()}">
                    <button type="submit">Valorar producto</button>
                </form>
            </td>
            <td>
                <form method="POST" action="addValoracionVendedor.php">
                    <input type="hidden" name="valorar" value="valorarSubasta">
                    <input type="hidden" name="idsubasta" value="{$subasta->getIdSubasta()}">
                    <input type="hidden" name="idvendedor" value="{$subasta->getIdUsuario()}">
                    <input type="hidden" name="idganador" value="{$subasta->getIdGanador()}">
                    <input type="hidden" name="tituloproducto" value="{$subasta->getTitulo()}">
                    <button type="submit">Valorar vendedor</button>
                </form>
            </td>
            <td>
                <form method="POST" action="chatearConVendedor.php">
                    <input type="hidden" name="mensaje" value="iniciarCHat">
                    <input type="hidden" name="idsubasta" value="{$subasta->getIdSubasta()}">
                    <input type="hidden" name="receptor" value="{$subasta->getIdUsuario()}">
                    <input type="hidden" name="emisor" value="{$subasta->getIdGanador()}">
                    <input type="hidden" name="tituloproducto" value="{$subasta->getTitulo()}">
                    <button type="submit">Contactar con el vendedor</button>
                </form>
            </td>                
            EOF;
        break;
        default:
            // no hacer nada
    }

    $html .= "  </div></div>";

    return $html;
}

?>