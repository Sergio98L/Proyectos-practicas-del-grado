<?php
namespace es\ucm\fdi\aw\valoraciones;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;

class FormularioValoracionesProducto extends Formulario
{

    public function __construct() {
        parent::__construct('formObjeto', ['enctype' => 'multipart/form-data', 'urlRedireccion' => Aplicacion::getInstance()->resuelve('/index.php')]);
    }
    
    protected function generaCamposFormulario(&$datos)
    {
        $app=Aplicacion::getInstance();
        $idusuario=$app->idUsuario();

        $idvaloracion= '';
        $idsubasta= '';
        $tituloproducto= '';

        $puntuacion = $datos['puntuacion'] ?? '';
        $comentario = $datos['comentario'] ?? '';

        $idvendedor = $datos['idvendedor'] ?? '';
        $titulovaloracion= $datos['titulovaloracion'] ?? '';;

        if(isset($_POST['idsubasta'])){
            $idsubasta= $_POST['idsubasta'];
            $idvendedor= $_POST['idvendedor'];
            $idganador= $idusuario;
            $tituloproducto= $_POST['tituloproducto'];

            $valoracion = Valoracionproducto::buscarValoracionExistente($idvendedor,$idusuario);
        
            if($valoracion != false){
                $idvaloracion= $valoracion->getIdValoracion();
                $puntuacion = $valoracion->getPuntuacion();
                $comentario =$valoracion->getComentario();  
                $titulovaloracion= $valoracion->getitulovaloracion();
            }               
        }


        // Se generan los mensajes de error si existen.
        
        $htmlErroresGlobales = self::generaListaErroresGlobales($this->errores);
        $erroresCampos = self::generaErroresCampos(['titulovaloracion','comentario'], $this->errores, 'span', array('class' => 'error'));
       
        $html = <<<EOF
        $htmlErroresGlobales
        <fieldset>
            <legend>Evaluacion de vendedor</legend>
            <input type="hidden" name="idvaloracion" value="$idvaloracion" />
            <input type="hidden" name="idsubasta" value="$idsubasta" />
            <div >
                <label>Vendedor:</label> <input type="text" name="idvendedor" readonly value="$idvendedor" />
            </div>
            <div >
                <label>Producto:</label> <input type="text" name="tituloproducto" readonly value="$tituloproducto"/>
            </div>
                <label for="titulovaloracion">Título:</label> 
                <input type="text" name="titulovaloracion" value="$titulovaloracion" />
                            $erroresCampos[titulovaloracion]
            
            <div >
                <label>Evalua al vendedor:</label> <input type="number" min="0" max="10" name="puntuacion" value="$puntuacion" />
            </div>
            <div >
                <label>Descripción:</label> <textarea name="comentario">$comentario</textarea>
                $erroresCampos[comentario]
            </div>           
            <div >
                <button type="submit" name="valoracion">Enviar evaluación
            <div>

        </fieldset>
        EOF;
        return $html;
    }   

    protected function procesaFormulario(&$datos)
    {
        $this->errores = [];

        $comentario = trim($datos['comentario'] ?? '');
        $comentario = filter_var($comentario, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $idvaloracion =trim($datos['idvaloracion'] ?? '');  
        $idvaloracion = filter_var($idvaloracion, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $idSubasta = trim($datos['idsubasta'] ?? '');
        $idSubasta = filter_var($idSubasta, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $tituloproducto = trim($datos['tituloproducto'] ?? '');
        $tituloproducto = filter_var($tituloproducto, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $idvendedor = trim($datos['idvendedor'] ?? '');
        $idvendedor = filter_var($idvendedor, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $puntuacion= trim($datos['puntuacion'] ?? '');
        $puntuacion = filter_var($puntuacion, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $titulovaloracion = trim($datos['titulovaloracion'] ?? '');
        $titulovaloracion = filter_var($titulovaloracion, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $titulovaloracion || mb_strlen($titulovaloracion) < 5) {
            $this->errores['titulo'] = 'El titulo debe tener una longitud de al menos 5 caracteres.';
        }

        if (count($this->errores) === 0) {
          //  $subasta = Subasta::buscaSubasta($tituloSubasta);
	
                $app = Aplicacion::getInstance();
                $idusuario = $app->idUsuario();
              if($idvaloracion!=""){
                $valoracion = Valoracionproducto::actualizaValoracion($idvaloracion,$idusuario, $idSubasta, $tituloproducto, $puntuacion, $comentario,$idvendedor,$titulovaloracion);  

              }else{
                $valoracion = Valoracionproducto::crea($idusuario, $idSubasta, $tituloproducto, $puntuacion, $comentario,$idvendedor,$titulovaloracion);               
         }
                
        }
    }
}