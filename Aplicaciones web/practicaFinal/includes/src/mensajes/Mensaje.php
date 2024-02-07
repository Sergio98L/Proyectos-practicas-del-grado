<?php
namespace es\ucm\fdi\aw\mensajes;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\MagicProperties;

class Mensaje
{
    use MagicProperties;

    public static function crea($id_subasta_aso, $emisor_id, $receptor_id, $mensaje, $fecha)
    {
        $mensaje = new Mensaje($id_subasta_aso, $emisor_id, $receptor_id, $mensaje, $fecha);
        return $mensaje->guarda();
    }
    public static function buscarConversacion($emisorId,$receptorId)
    {
        $app=Aplicacion::getInstance();
        $conn = $app->getConexionBd();
        $query = sprintf("SELECT * FROM mensajes WHERE emisor_id = %d && receptor_id= %d ORDER BY msg_id",$emisorId,$receptorId);
        $rs = $conn->query($query);
        $mensajes = array(); // Creamos un array vacío para almacenar los mensajes
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $mensaje = new Mensaje( $fila['id_mensaje'],  $fila['id_subasta_aso'],  $fila['emisor_id'],  $fila['receptor_id'],  $fila['mensaje'],  $fila['fecha']);
                $mensajes[] = $mensaje; 
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $mensajes; // Devolvemos el array de mensajes
    }
    public static function buscaPorEmisor($emisorId)
    {
        $app=Aplicacion::getInstance();
        $conn = $app->getConexionBd();
        $query = sprintf("SELECT * FROM mensajes WHERE emisor_id LIKE '%d'", $emisorId);
        $rs = $conn->query($query);
        $mensajes = array(); // Creamos un array vacío para almacenar los mensajes
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $mensaje = new Mensaje( $fila['id_mensaje'],  $fila['id_subasta_aso'],  $fila['emisor_id'],  $fila['receptor_id'],  $fila['mensaje'],  $fila['fecha']);
                $mensajes[] = $mensaje; 
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $mensajes; // Devolvemos el array de mensajes
    }
    public static function buscaPorReceptor($receptorId)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM mensajes WHERE receptor_id ='%d' ", $receptorId );
        $rs = $conn->query($query);
        $mensajes = array(); // Creamos un array vacío para almacenar los mensajes
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $mensaje = new Mensaje( $fila['id_mensaje'],  $fila['id_subasta_aso'],  $fila['emisor_id'],  $fila['receptor_id'],  $fila['mensaje'],  $fila['fecha']);
                $mensajes[] = $mensaje; 
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $mensajes; // Devolvemos el array de mensajes
    }   

    /*public static function buscaPorReceptor($receptorId)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM mensajes WHERE receptor_id ='%d' ", $receptorId );
        $rs = $conn->query($query);
        $mensajes = array(); // Creamos un array vacío para almacenar los mensajes
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $mensaje = new Mensaje( $fila['id_mensaje'],  $fila['id_subasta_aso'],  $fila['emisor_id'],  $fila['receptor_id'],  $fila['mensaje'],  $fila['fecha']);
                $mensajes[] = $mensaje; 
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $mensajes; // Devolvemos el array de mensajes
    }*/

public static function usuariosQueHasEnviadoMensaje($emisorId)
{
$conn = Aplicacion::getInstance()->getConexionBd();
$query = sprintf("SELECT DISTINCT subastas.*, usuarios_vendedor.nombreUsuario, usuarios_comprador.nombreUsuario
    FROM subastas
    INNER JOIN usuarios AS usuarios_vendedor ON subastas.id_usuario = usuarios_vendedor.id_usuario
    INNER JOIN usuarios AS usuarios_comprador ON subastas.id_ganador = usuarios_comprador.id_usuario
    INNER JOIN mensajes ON subastas.id_subasta = mensajes.id_subasta_aso
    WHERE (mensajes.emisor_id = $emisorId)
    OR (mensajes.receptor_id = $emisorId)");

    $rs = $conn->query($query);
    $subastas = array(); // Creamos un array vacío para almacenar las subastas y sus datos relacionados
    if ($rs) {
        while ($fila = $rs->fetch_assoc()) {
            $subasta = \es\ucm\fdi\aw\subastas\Subasta::buscaPorId($fila['id_subasta']);
            $usuarioVendedor = \es\ucm\fdi\aw\usuarios\Usuario::buscaPorId($fila['id_usuario']);
            $usuarioComprador = \es\ucm\fdi\aw\usuarios\Usuario::buscaPorId($fila['id_ganador']);

            $datosSubasta = array(
                'subasta' => $subasta,
                'vendedor' => $usuarioVendedor,
                'comprador' => $usuarioComprador
            );

            $subastas[] = $datosSubasta;
        }
        $rs->free();
    } else {
        error_log("Error BD ({$conn->errno}): {$conn->error}");
    }
    return $subastas; // Devolvemos el array de subastas con sus datos relacionados
}


    private static function borra($receptorId,$emisorId)
    {
        return self::borraPorId($receptorId,$emisorId);
    }
    
    private static function borraPorId($receptorId,$emisorId)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("DELETE FROM mensajes WHERE emisor_id = %d && receptor_id= %d ",$emisorId,$receptorId);
        if ( ! $conn->query($query) ) {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
            return false;
        }
        return true;
    }

    public static function numeroMensajes($receptorId,$emisorId)
    {
        $app=Aplicacion::getInstance();
        $conn = $app->getConexionBd();
        $query = sprintf("SELECT COUNT(*) FROM mensajes WHERE emisor_id = %d && receptor_id= %d",$emisorId,$receptorId);
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $row = $rs->fetch_row();
            $result = $row[0];
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $result;
    }
function mostrarTitulosTabla(){
    $html = <<<EOF
    <table>
        <tr>
            <th>Nombre</th>
            <th>Producto</th>
            <th>Fecha</th>                         
    EOF;
    return $html;

}
public static function listarConservaciones($idEmisor)
{
    $app=Aplicacion::getInstance();
    $mensajes = Mensaje::usuariosQueHasEnviadoMensaje($idEmisor); //Obtenemos la informacion de las subastas con conversaciones abiertas
    $titulosCol = <<<EOF
    <table>
        <tr>
            <th>Nombre</th>
            <th>Producto</th>
            <th>Fecha</th>                         
    EOF;
    
    $html = <<<EOF
        <div class="listing">
    EOF;

    foreach($mensajes as $mensaje) {
        $subasta = $mensaje['subasta'];
        $vendedor =$mensaje['vendedor'];
        $comprador = $mensaje['comprador'];
        $nombreVendedor = $vendedor->getNombre();
        $fechafin = $subasta->getFechaFin();

        $rutaimagen="";
        $imagen= \es\ucm\fdi\aw\subastas\Imagen::buscaPorsubasta($subasta->getIdSubasta());
        if($imagen!=false){
            $rutaimagen=RUTA_ALMACEN_BAJADA.$imagen->getRuta();
            }
        
        $html .= <<<EOF
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
    EOF;
    if($vendedor->getId()  == $app->idUsuario()){
        $html .= <<<EOF
        <div class="buttons-container">
                    <form method="POST" action="addSubasta.php">
                    </form>
                    <td>
                        <form method="POST" action="chatearConVendedor.php">
                            <input type="hidden" name="mensaje" value="iniciarCHat">
                            <input type="hidden" name="idsubasta" value="{$subasta->getIdSubasta()}">
                            <input type="hidden" name="receptor" value="{$subasta->getIdGanador()}">
                            <input type="hidden" name="emisor" value="{$subasta->getIdUsuario()}">
                            <input type="hidden" name="tituloproducto" value="{$subasta->getTitulo()}">
                            <button type="submit">Contactar con el vendedor</button>
                        </form>
                    </td>                
                </div>
            </div>
        EOF;
    }else{
        $html .= <<<EOF
        <div class="buttons-container">
                    <form method="POST" action="addSubasta.php">
                    </form>
                    <td>
                        <form method="POST" action="chatearConVendedor.php">
                            <input type="hidden" name="mensaje" value="iniciarCHat">
                            <input type="hidden" name="idsubasta" value="{$subasta->getIdSubasta()}">
                            <input type="hidden" name="receptor" value="{$subasta->getIdUsuario()}">
                            <input type="hidden" name="emisor" value="{$app->idUsuario()}">
                            <input type="hidden" name="tituloproducto" value="{$subasta->getTitulo()}">
                            <button type="submit">Contactar con el vendedor</button>
                        </form>
                    </td>                
                </div>
            </div>
        EOF;
    }
    
    }
    
    $html .= "</div>";
    return $html;
}

    private $idMensaje;

    private $id_subasta_aso;

    private $emisor_id;

    private $receptor_id;

    private $mensaje;
    
    private  $fecha;


    private function __construct($id_subasta_aso, $emisor_id, $receptor_id, $mensaje, $fecha,$idMensaje = null)
    {
        $this->idMensaje = $idMensaje;
        $this->id_subasta_aso = $id_subasta_aso;
        $this->emisor_id = $emisor_id;
        $this->receptor_id = $receptor_id;
        $this->mensaje = $mensaje;
        $this->fecha = $fecha;
    }
   public function getIdMensaje() {
        return $this->idMensaje;
    }

    public function getId_subasta_aso() {
        return $this->id_subasta_aso;
    }

    public function getEmisor_id() {
        return $this->emisor_id;
    }

    public function getMensaje() {
        return $this->mensaje;
    }

    public function getFecha() {
        return $this->fecha;
    }
    
    public function guarda()
    {
        return self::inserta($this);
    }
    
    public function borrate()
    {
        if ($this->idsubasta !== null) {
            return self::borra($this);
        }
        return false;
    }
}
