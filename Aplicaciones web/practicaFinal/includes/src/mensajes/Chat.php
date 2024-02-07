<?php
namespace es\ucm\fdi\aw\mensajes;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;

class Chat extends Formulario
{

    public function __construct() {
        parent::__construct('formObjeto', ['enctype' => 'multipart/form-data', 'urlRedireccion' => Aplicacion::getInstance()->resuelve('/index.php')]);
    }
    
    protected function generaCamposFormulario(&$datos)
    {
        $app=Aplicacion::getInstance();
        $emisorId=$app->idUsuario();

        $id_SubastaAso= '';
        $receptorId= '';
        
        $mensaje= '';
        $fecha= '';

        if(isset($_POST['idsubasta'])){
            $id_SubastaAso= $_POST['idsubasta'];
            $receptorId= $_POST['receptor'];
            $tituloproducto= $_POST['tituloproducto'];

            //$valoracion = Valoracionproducto::buscarValoracionExistente($idvendedor,$idusuario);
        
            //if($valoracion != false){
             //   $idvaloracion= $valoracion->getIdValoracion();
           //     $puntuacion = $valoracion->getPuntuacion();
            //    $comentario =$valoracion->getComentario();  
            //    $titulovaloracion= $valoracion->getitulovaloracion();
            //}               
        }
        $nombreReceptor ="";
        $nombreReceptor = \es\ucm\fdi\aw\usuarios\Usuario::buscaPorId($receptorId);
        if($nombreReceptor){
            $nombreReceptor = $nombreReceptor->getNombre();
        }else{
            $nombreReceptor =$datos['incoming_id'];
        }
        $subasta =  \es\ucm\fdi\aw\subastas\Subasta::buscaPorId($id_SubastaAso);
        if($subasta){
            $tituloSubasta = $subasta->getTitulo();
        }else{
            $tituloSubasta =$datos['tituloSubasta'];
        }
        
        // Se generan los mensajes de error si existen. (Si se usa EOF js no puede detectar los)     
        echo '<script>var app = ' . json_encode($app) . ';</script>';
        echo '<div class="wrapper">';
        echo '<section class="chat-area">';
        echo '<header>';
        echo '<div class="details">';
        echo '<span>' . $nombreReceptor . '</span>';
        echo '<p>' . $tituloSubasta . '</p>';
        echo '</div>';
        echo '</header>';
        echo '<div class="chat-box"></div>';
        echo '<form action="#" class="typing-area">';
        echo '<input type="text" class="incoming_id" name="incoming_id" value="' . $receptorId . '" hidden>';
        echo '<input type="text" class="subasta_id" name="subasta_id" value="' . $id_SubastaAso . '" hidden>';
        echo '<input type="text" name="message" class="input-field" placeholder="Escribe tu mensaje aquí..." autocomplete="off">';
        echo '<button><i class="fab fa-telegram-plane">Enviar</i></button>';
        echo '</form>';
        echo '</section>';
        echo '</div>';
        echo '<script src="js/chat.js"></script>';
       
    }   

    protected function procesaFormulario(&$datos)
    {
        $this->errores = [];

        $comentario = trim($datos['comentario'] ?? '');
        $comentario = filter_var($comentario, FILTER_SANITIZE_FULL_SPECIAL_CHARS);

        $titulovaloracion = trim($datos['titulovaloracion'] ?? '');
        $titulovaloracion = filter_var($titulovaloracion, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $titulovaloracion || mb_strlen($titulovaloracion) < 5) {
            $this->errores['titulo'] = 'El titulo debe tener una longitud de al menos 5 caracteres.';
        }                
        
    }
}