<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;

class FormularioObjeto extends Formulario
{
    const EXTENSIONES_PERMITIDAS = array('gif', 'jpg', 'jpe', 'jpeg', 'png', 'webp', 'avif');
    const TIPO_ALMACEN = [Imagen::PUBLICA => 'Publico', Imagen::PRIVADA =>'Privado'];

    public function __construct() {
        parent::__construct('formObjeto', ['enctype' => 'multipart/form-data', 'urlRedireccion' => Aplicacion::getInstance()->resuelve('/index.php')]);
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
        $tipoAlmacenSeleccionado = $datos['tipo'] ?? null;

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
        $erroresCampos = self::generaErroresCampos(['titulo', 'descripcion', 'fechaInicio', 'fechaFin', 'precioInicial', 'categoria', 'estadoProducto','archivo', 'tipo'], $this->errores, 'span', array('class' => 'error'));
        $selectorTipoAlmacen = self::generaSelectorTipoAlmacen('tipo', $tipoAlmacenSeleccionado, 'tipo');

        $html = <<<EOF
                    $htmlErroresGlobales
                    <fieldset>

                    <input type="hidden" name="idSubasta" value="$idSubasta" />
                    <input type="hidden" name="precioactual" value="$precioactual" />
                    <input type="hidden" name="idganador" value="$idganador" />
                    <div class="seccion">
                        <label for="titulo">Título:</label> 
                        <input type="text" name="titulo" id="campotitulo" value="$titulo" />
                        $erroresCampos[titulo]
                    </div>
                    <div class="seccion">
                        <label for="descripcion">Descripción:</label> 
                        <textarea name="descripcion" id="campodescripcion">$descripcion</textarea>
                        $erroresCampos[descripcion]
                        <label for="categoria">Categoría:</label> 
        EOF;
                $html .=\es\ucm\fdi\aw\subastas\ListadoCategorias::desplegableCategorias();
                $html .=<<<EOF
                        $erroresCampos[categoria]
                        <label for="estadoProducto">Estado del producto:</label> 
                        <select name="estadoProducto" id="estadoProducto">
                            <option value="nuevo">Nuevo</option>
                            <option value="usado">Usado</option>
                            <option value="para piezas">Para piezas</option>
                        </select>
                        $erroresCampos[estadoProducto]
                    </div>
                    <div class="seccion">
                        <label for="archivo">Subida de imágenes:</label> 
                        <input type="file" name="archivo" id="archivo" />
                        $erroresCampos[archivo]
                    </div>
                    <div class="seccion">
                        <label for="precio">Precio inicial:</label> 
                        <input type="number" name="precioInicial" id="precioInicial" value="$precioInicial" />
                        $erroresCampos[precioInicial]
                    </div>
                    <div class="seccion">
                        <label for="fechainicio">Fecha de inicio:</label> 
                       <input type="datetime-local" name="fechaInicio" value="$fechaInicio" />
                        $erroresCampos[fechaInicio]
                        <label for="fechafin">Fecha de fin:</label> 
                        <input type="datetime-local" name="fechaFin" value="$fechaFin" />
                        $erroresCampos[fechaFin]
                    </div>
                    <button type="submit" name="subasta" id="boton-publicar">Publicar</button>

                
             </fieldset>      
    EOF;
                
        return $html;
    }
    private static function generaSelectorTipoAlmacen($name, $tipoSeleccionado=null, $id_imagen=null)
    {
        $id_imagen= $id_imagen !== null ? "id=\"{$id_imagen}\"" : '';
        $html = "<select {$id_imagen} name=\"{$name}\">";
        foreach(self::TIPO_ALMACEN as $clave => $valor) {
            $selected='';
            if ($tipoSeleccionado && $clave == $tipoSeleccionado) {
                $selected='selected';
            }
            $html .= "<option value=\"{$clave}\"{$selected}>{$valor}</option>";
        }
        $html .= '</select>';

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
        
        $fechaFin = trim($datos['fechaFin'] ?? '');
        $fechaFin = filter_var($fechaFin, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        
        if ( $fechaInicio > $fechaFin) {
            $this->errores['fechaInicio'] = 'La fecha de inicio no puede ser posterior a la fecha de finalizacion';
            $this->errores['fechaFin'] = 'La fecha de finalizacion debe ser posterior a la fecha de inicio';
        }
        
        $precioInicial = trim($datos['precioInicial'] ?? '');
        $precioInicial = filter_var($precioInicial, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $precioInicial  ) {
            $this->errores['precioInicial'] = 'Precio no valido';
        }

        $categoria = trim($datos['categoria'] ?? '');
        $categoria = filter_var($categoria, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $categoria  ) {
            $this->errores['categoria'] = 'Los categoria deben coincidir';
        }

        $ok = $_FILES['archivo']['error'] == UPLOAD_ERR_OK && count($_FILES) == 1;
        if (! $ok ) {
            $this->errores['archivo'] = 'Error al subir el archivo';
            return;
        }  

        $nombre = $_FILES['archivo']['name'];

        $tipoAlmacen = $datos['tipo'] ?? Imagen::PUBLICA;

        $ok = array_key_exists($tipoAlmacen, self::TIPO_ALMACEN);
        if (!$ok) {
            $this->errores['tipo'] = 'El tipo del almacén no está seleccionado o no es correcto';
        }
        
        /* 1.a) Valida el nombre del archivo */
        $ok = self::check_file_uploaded_name($nombre) && $this->check_file_uploaded_length($nombre);
        
        /* 2. comprueba si la extensión está permitida */
        $extension = pathinfo($nombre, PATHINFO_EXTENSION);
        $ok = $ok && in_array($extension, self::EXTENSIONES_PERMITIDAS);

        /* 3. comprueba el tipo mime del archivo corresponde a una imagen image/* */
        $finfo = new \finfo(FILEINFO_MIME_TYPE);
        $mimeType = $finfo->file($_FILES['archivo']['tmp_name']);
        $ok = preg_match('/image\/*./', $mimeType);

        if (!$ok) {
            $this->errores['archivo'] = 'El archivo tiene un nombre o tipo no soportado';
        }


        if (count($this->errores) === 0) {
          //  $subasta = Subasta::buscaSubasta($tituloSubasta);
	
                $app = Aplicacion::getInstance();
                $idUsuario = $app->idUsuario();
              if($idSubasta!=""){
                $subasta = Subasta::actualizaSubasta($idSubasta,$idUsuario, $titulo, $descripcion, $fechaInicio, $fechaFin, $precioInicial, $precioactual, $categoria, $estadoproducto,$idganador);  

              }else{
                $subasta = Subasta::crea($idUsuario, $titulo, $descripcion, $fechaInicio, $fechaFin, $precioInicial, $precioInicial, $categoria, $estadoproducto);
                $subastaaux = Subasta::buscaSubasta($titulo);
                $id_subasta=$subastaaux->getIdSubasta();

                $tmp_name = $_FILES['archivo']['tmp_name'];
               $imagen = Imagen::crea($id_subasta,$nombre, $mimeType, $tipoAlmacen, '');
               $imagen->guarda();
               $fichero = "{$imagen->id_imagen}.{$extension}";
               $imagen->setRuta($fichero);
               $imagen->guarda();
               $ruta = implode(DIRECTORY_SEPARATOR, [RUTA_ALMACEN, $fichero]);
               
               if (!move_uploaded_file($tmp_name, $ruta)) {
                   $this->errores['archivo'] = 'Error al mover el archivo';
               }
         }
                
        }
    }

   
     /**
     * Check $_FILES[][name]
     *
     * @param (string) $filename - Uploaded file name.
     * @author Yousef Ismaeil Cliprz
     * @See http://php.net/manual/es/function.move-uploaded-file.php#111412
     */
    private static function check_file_uploaded_name($filename)
    {
        return (bool) ((mb_ereg_match('/^[0-9A-Z-_\.]+$/i', $filename) === 1) ? true : false);
    }

    /**
     * Sanitize $_FILES[][name]. Remove anything which isn't a word, whitespace, number
     * or any of the following caracters -_~,;[]().
     *
     * If you don't need to handle multi-byte characters you can use preg_replace
     * rather than mb_ereg_replace.
     * 
     * @param (string) $filename - Uploaded file name.
     * @author Sean Vieira
     * @see http://stackoverflow.com/a/2021729
     */
    private static function sanitize_file_uploaded_name($filename)
    {
        /* Remove anything which isn't a word, whitespace, number
     * or any of the following caracters -_~,;[]().
     * If you don't need to handle multi-byte characters
     * you can use preg_replace rather than mb_ereg_replace
     * Thanks @Łukasz Rysiak!
     */
        $newName = mb_ereg_replace("([^\w\s\d\-_~,;\[\]\(\).])", '', $filename);
        // Remove any runs of periods (thanks falstro!)
        $newName = mb_ereg_replace("([\.]{2,})", '', $newName);

        return $newName;
    }

    /**
     * Check $_FILES[][name] length.
     *
     * @param (string) $filename - Uploaded file name.
     * @author Yousef Ismaeil Cliprz.
     * @See http://php.net/manual/es/function.move-uploaded-file.php#111412
     */
    private function check_file_uploaded_length($filename)
    {
        return (bool) ((mb_strlen($filename, 'UTF-8') < 250) ? true : false);
    }
}