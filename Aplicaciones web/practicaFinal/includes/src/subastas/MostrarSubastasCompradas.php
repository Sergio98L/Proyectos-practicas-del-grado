<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;


class MostrarSubastasCompradas extends Formulario
{
    public function __construct() {     
        parent::__construct('formObjeto', ['urlRedireccion']);
  
    }
    
    public function generaCamposFormulario(&$datos)
    {
        //Llega hasta el metodo Subasta::public static function listarSubastas($busqueda)
        $resultadoTablaSubastas = ListadoSubastas::listadoCompradas("compras");
        //Creamos aqui la parte fija del codigo HTML
        $html = <<<EOF
        <fieldset>
            <legend>Subastas ganadas</legend>
            $resultadoTablaSubastas      
        </fieldset>
    EOF;
    return $html;
    }
    

    protected function procesaFormulario(&$datos)
    {
       
       
    }
}
?>