<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;


class ModificarSubastas extends Formulario
{
    public function __construct() {     
        parent::__construct('formObjeto', ['urlRedireccion']);
  
    }
    
    public function generaCamposFormulario(&$datos)
    {
        $resultadoTablaSubastas = ListadoSubastas::listadoActualizar("ventas");
        //Creamos aqui la parte fija del codigo HTML
        $html = <<<EOF
        <fieldset>
            <legend>Subastas actuales</legend>
            $resultadoTablaSubastas      
        </fieldset>
    EOF;
    return $html;
    }
    

    protected function procesaFormulario(&$datos)
    {
       
        if(isset($_POST['borrar']) && $_POST['borrar'] === 'borrarSubasta') {
            $idSubasta = $_POST['parametro'];
            $subasta = Subasta::buscaPorId($idSubasta);
            if($subasta) {
                $subasta->borrate();
                echo "<p>Subasta borrada correctamente.</p>";
            } else {
                echo "<p>No se ha encontrado la subasta que se quiere borrar.</p>";
            }
        }
    }
}
?>