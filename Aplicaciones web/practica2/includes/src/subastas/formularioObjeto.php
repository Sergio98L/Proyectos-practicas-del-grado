<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;

class FormularioObjeto extends Formulario
{
    public function __construct() {
        parent::__construct('formObjeto', ['urlRedireccion' => Aplicacion::getInstance()->resuelve('/index.php')]);
    }
    
    protected function generaCamposFormulario(&$datos)
    {
       
        $idSubasta= '';
        $precioactual= '';
        $idganador= '';
        $titulo = $datos['titulo'] ?? '';
        $descripcion = $datos['descripcion'] ?? '';
        $fechaInicio = $datos['fechaInicio'] ?? '';
        $fechaFin = $datos['fechaFin'] ?? '';
        $precioInicial = $datos['precioInicial'] ?? '';
        $categoria = $datos['categoria'] ?? '';
        $estadoProducto = $datos['estadoProducto'] ?? '';

        if(isset($_POST['idsubasta'])){
            $idSubasta= $_POST['idsubasta'];
            $precioactual= $_POST['precioactual'];
            $idganador= $_POST['idganador'];
            
            $subasta = Subasta::buscaPorId($idSubasta);
            $titulo = $subasta->getTitulo();
            $descripcion =$subasta->getDescripcion();
            $fechaInicio=$subasta->getFechaInicio();
            $fechaFin=$subasta->getFechaFin();
            $precioInicial=$subasta->getPrecioInicial();
            $categoria=$subasta->getCategoria();
            $estadoProducto=$subasta->getEstadoProducto();
       }

     

        // Se generan los mensajes de error si existen.
        $htmlErroresGlobales = self::generaListaErroresGlobales($this->errores);
        $erroresCampos = self::generaErroresCampos(['titulo', 'descripcion', 'fechaInicio', 'fechaFin', 'precioInicial', 'categoria', 'estadoProducto'], $this->errores, 'span', array('class' => 'error'));

        $html = <<<EOF
        $htmlErroresGlobales
        <fieldset>
            <legend>Datos para el registro de una subasta</legend>
            <input type="hidden" name="idSubasta" value="$idSubasta" />
            <input type="hidden" name="precioactual" value="$precioactual" />
            <input type="hidden" name="idganador" value="$idganador" />
            <div >
                <label>Título:</label> <input type="text" name="titulo" value="$titulo" />
                $erroresCampos[titulo]
            </div>
            <div >
                <label>Descripción:</label> <textarea name="descripcion">$descripcion</textarea>
                $erroresCampos[descripcion]
            </div>
            <div >
                <label>Fecha de inicio:</label> <input type="datetime-local" name="fechaInicio" value="$fechaInicio" />
                $erroresCampos[fechaInicio]
            </div>
            <div >
                <label>Fecha de fin:</label> <input type="datetime-local" name="fechaFin" value="$fechaFin" />
                $erroresCampos[fechaFin]
            </div>
            <div >
                <label>Precio inicial:</label> <input type="number" name="precioInicial" value="$precioInicial" />
                $erroresCampos[precioInicial]
            </div>
            <div >
                <label>Categoría:</label> <input type="text" name="categoria" value="$categoria" />
                $erroresCampos[categoria]
            </div>
            <div>
                <label for="imagen">Selecciona una imagen:</label>
                <input type="file" name="imagen" >
           </div>

            <div >
                <label>Estado del producto:</label> 
                <select name="estadoProducto">
                    <option value="nuevo">Nuevo</option>
                    <option value="usado" >Usado</option>
                    <option value="para piezas" >Para piezas</option>
                </select>
                $erroresCampos[estadoProducto]
            </div>
            
            <div >
                <button type="submit" name="subasta">Crear
            <div>

        </fieldset>
        EOF;
        return $html;
    }
    

    protected function procesaFormulario(&$datos)
    {
        $this->errores = [];

        $estadoproducto = trim($datos['estadoProducto'] ?? '');
       
        $imagen=trim($datos['imagen'] ?? '');

        $idSubasta = trim($datos['idSubasta'] ?? '');
        $idSubasta = filter_var($idSubasta, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
       
        $precioactual = trim($datos['precioactual'] ?? '');
        $precioactual = filter_var($precioactual, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $idganador = trim($datos['idganador'] ?? '');
        $idganador = filter_var($idganador, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $titulo = trim($datos['titulo'] ?? '');
        $titulo = filter_var($titulo, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $titulo || mb_strlen($titulo) < 5) {
            $this->errores['titulo'] = 'El titulo de usuario tiene que tener una longitud de al menos 5 caracteres.';
        }

        $descripcion = trim($datos['descripcion'] ?? '');
        $descripcion = filter_var($descripcion, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $descripcion || mb_strlen($descripcion) < 5) {
            $this->errores['descripcion'] = 'la descripcion tiene que tener una longitud de al menos 5 caracteres.';
        }
        $fechaInicio = trim($datos['fechaInicio'] ?? '');
        $fechaInicio = filter_var($fechaInicio, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $fechaInicio ) {
            $this->errores['fechaInicio'] = 'El fechaInicio tiene que tener una longitud de al menos 5 caracteres.';
        }
        $fechaFin = trim($datos['fechaFin'] ?? '');
        $fechaFin = filter_var($fechaFin, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $fechaFin  ) {
            $this->errores['fechaFin'] = 'El fechaFin tiene que tener una longitud de al menos 5 caracteres.';
        }

        $precioInicial = trim($datos['precioInicial'] ?? '');
        $precioInicial = filter_var($precioInicial, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $precioInicial  ) {
            $this->errores['precioInicial'] = 'Los passwords deben coincidir';
        }

        $categoria = trim($datos['categoria'] ?? '');
        $categoria = filter_var($categoria, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $categoria  ) {
            $this->errores['categoria'] = 'Los categoria deben coincidir';
        }

        if (count($this->errores) === 0) {
          //  $subasta = Subasta::buscaSubasta($tituloSubasta);
	
                $app = Aplicacion::getInstance();
                $idUsuario = $app->idUsuario();
              if($idSubasta!=""){
                $subasta = Subasta::actualizaSubasta($idSubasta,$idUsuario, $titulo, $descripcion, $fechaInicio, $fechaFin, $precioInicial, $precioactual,$imagen, $categoria, $estadoproducto,$idganador);           
              }else{
                $subasta = Subasta::crea($idUsuario, $titulo, $descripcion, $fechaInicio, $fechaFin, $precioInicial, $precioInicial,$imagen, $categoria, $estadoproducto);
              }
                
        }
    }
}