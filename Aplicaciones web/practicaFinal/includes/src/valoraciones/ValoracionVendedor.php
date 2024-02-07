<?php
namespace es\ucm\fdi\aw\valoraciones;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\MagicProperties;

class Valoracionvendedor
{
    use MagicProperties;

   
    
    public static function crea($idusuario, $puntuacion, $comentario,$idvendedor)
    {
        $valoracion = new Valoracionvendedor($idusuario,$puntuacion, $comentario,$idvendedor);
        return $valoracion->guarda();
    }
    public static function actualizaValoracion($idvaloracion,$idusuario, $puntuacion, $comentario,$idvendedor)
    {
        $valoracion = new Valoracionvendedor($idusuario,$puntuacion, $comentario,$idvendedor, $idvaloracion);
        return $valoracion->guarda();
    }
    
    public static function buscaPorId($idvaloracion)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM valoracionesvendedor V WHERE V.id_valoracion='%d' ", $idvaloracion );
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Valoracionvendedor( $fila['id_usuario'],  $fila['puntuacion'],  $fila['comentario'],$fila['id_vendedor'],$fila['id_valoracion']);            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
       
        return $result;
    }

    //Sirve para ver si el usuario ya ha valorado al vendedor
    public static function buscarValoracionExistente($idvendedor,$idusuario)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM valoracionesvendedor V WHERE V.id_vendedor='%d' AND V.id_usuario='%d'" , $idvendedor ,$idusuario);
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Valoracionvendedor( $fila['id_usuario'],  $fila['puntuacion'],  $fila['comentario'],$fila['id_vendedor'],$fila['id_valoracion']);            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
       
        return $result;
    }

    public static function listarValoraciones($busqueda,$buscar=null)
    {
        $app=Aplicacion::getInstance();
        $idusuario=$app->idUsuario();
        $conn = $app->getConexionBd();
        $query =" ";

        if($busqueda=='usuario'){
            //listado general todas las valoraciones
            $query = sprintf("SELECT * FROM valoracionesvendedor V WHERE V.id_usuario= '%d'",  $idusuario);
           }       
        else if($busqueda=='vendedor'){
            $query = sprintf("SELECT * FROM valoracionesvendedor V WHERE V.id_vendedor= '%d'",  $conn->real_escape_string($buscar));
        }
        $rs = $conn->query($query);
        $valoraciones = array(); 
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $valoracion = new Valoracionvendedor(
                    $fila['id_usuario'],
                    $fila['puntuacion'],
                    $fila['comentario'],
                    $fila['id_vendedor'],
                );
                $valoraciones[] = $valoracion; 
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $valoraciones; 
    }

    private static function inserta($valoracion)
    {
        $result = false;
        $conn = Aplicacion::getInstance()->getConexionBd();
        
        $query=sprintf("INSERT INTO valoracionesvendedor(id_usuario,puntuacion,comentario,id_vendedor) VALUES ('%d', '%s','%s', '%d')"
            , $valoracion->idusuario
            , $conn->real_escape_string($valoracion->puntuacion)
            , $conn->real_escape_string($valoracion->comentario)
            , $valoracion->idvendedor       
        );
        if ( $conn->query($query) ) {
            $valoracion->idvaloracion = $conn->insert_id;
            $result = $valoracion;
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $result;
    }
   
    
    private static function actualiza($valoracion)
    {
        $result = false;
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("UPDATE valoracionesvendedor V SET 
        puntuacion = '%s',
        comentario = '%s'
        WHERE V.id_valoracion = %d",
        $conn->real_escape_string($valoracion->puntuacion),
        $conn->real_escape_string($valoracion->comentario),
        $valoracion->idvaloracion
    );
        if ( $conn->query($query) ) {
            $result = $valoracion;
            
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        
        return $result;
    }
   
      
    private static function borra($valoracion)
    {
        return self::borraPorId($valoracion->idvaloracion);
    }
    
    private static function borraPorId($idvaloracion)
    {
        if (!$idvaloracion) {
            return false;
        } 
       
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("DELETE FROM valoracionesvendedor WHERE id_valoracion = %d" , $idvaloracion);
        if ( ! $conn->query($query) ) {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
            return false;
        }
        return true;
    }

   
    private $idvaloracion;

    private $idusuario;

    private $puntuacion;

    private $comentario;

    private $idvendedor;
    //Las valoraciones siempre estan relacionadas con un usuario
    private function __construct($idusuario,$puntuacion, $comentario,$idvendedor,$idvaloracion = null)
    {
        $this->idvaloracion = $idvaloracion;
        $this->idusuario = $idusuario;
        $this->puntuacion = $puntuacion;
        $this->comentario = $comentario;
        $this->idvendedor = $idvendedor;
    }

    public function getIdValoracion() {
        return $this->idvaloracion;
    }

    public function getIdUsuario() {
        return $this->idusuario;
    }

    public function getPuntuacion() {
        return $this->puntuacion;
    }

    public function getComentario() {
        return $this->comentario;
    }


    public function guarda()
    {
        if ($this->idvaloracion !== null) {
            return self::actualiza($this);
        }
        return self::inserta($this);
    }
    
    public function borrate()
    {
        if ($this->idvaloracion !== null) {
            return self::borra($this);
        }
        return false;
    }
}
