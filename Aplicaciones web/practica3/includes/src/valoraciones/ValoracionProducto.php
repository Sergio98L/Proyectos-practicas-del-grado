<?php
namespace es\ucm\fdi\aw\valoraciones;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\MagicProperties;

class Valoracionproducto
{
    use MagicProperties;

   
    
    public static function crea($idusuario, $idsubasta, $tituloproducto, $puntuacion, $comentario,$idvendedor,$titulovaloracion)
    {
        $valoracion = new Valoracionproducto($idusuario,$idsubasta,$tituloproducto,$puntuacion, $comentario,$idvendedor,$titulovaloracion);
        return $valoracion->guarda();
    }
    public static function actualizaValoracion($idvaloracion,$idusuario, $idsubasta, $tituloproducto, $puntuacion, $comentario,$idvendedor,$titulovaloracion)
    {
        $valoracion = new Valoracionproducto($idusuario,$idsubasta,$tituloproducto,$puntuacion, $comentario,$idvendedor,$titulovaloracion,$idvaloracion);
        return $valoracion->guarda();
    }
    
    public static function buscaPorId($idvaloracion)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM valoracionesproducto V WHERE V.id_valoracion='%d' ", $idvaloracion );
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Valoracionproducto( $fila['id_usuario'],  $fila['id_subasta'],  $fila['titulo_producto'],  $fila['puntuacion'],  $fila['comentario'],$fila['id_vendedor'],$fila['id_valoracion'],$fila['titulo_valoracion']);            }
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
        $query = sprintf("SELECT * FROM valoracionesproducto V WHERE V.id_vendedor='%d' AND V.id_usuario='%d'" , $idvendedor ,$idusuario);
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Valoracionproducto( $fila['id_usuario'],  $fila['id_subasta'],  $fila['titulo_producto'],  $fila['puntuacion'],  $fila['comentario'],$fila['id_vendedor'],$fila['titulo_valoracion'],$fila['id_valoracion']);            }
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
            $query = sprintf("SELECT * FROM valoracionesproducto V WHERE V.id_usuario= '%d'",  $idusuario);

           }else if($busqueda=='producto'){
        //listado de subsatas que tengo en estado borrador
        $query = sprintf("SELECT * FROM valoracionesproducto V WHERE V.titulo_producto= '%d'",  $conn->real_escape_string($buscar));       
        }else if($busqueda=='vendedor'){
            $query = sprintf("SELECT * FROM valoracionesproducto V WHERE V.id_vendedor= '%d'",  $conn->real_escape_string($buscar));
        }
        $rs = $conn->query($query);
        $valoraciones = array(); 
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $valoracion = new Valoracion(
                    $fila['id_usuario'],
                    $fila['id_subasta'],
                    $fila['titulo_producto'],
                    $fila['puntuacion'],
                    $fila['comentario'],
                    $fila['id_vendedor'],
                    $fila['titulo_valoracion']
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
        
        $query=sprintf("INSERT INTO valoracionesproducto(id_usuario,id_subasta,titulo_producto,puntuacion,comentario,id_vendedor,titulo_valoracion) VALUES ('%d', '%d', '%s', '%s','%s', '%d','%s')"
            , $valoracion->idusuario
            , $valoracion->idsubasta
            , $valoracion->tituloproducto
            , $conn->real_escape_string($valoracion->puntuacion)
            , $conn->real_escape_string($valoracion->comentario)
            , $valoracion->idvendedor  
            , $conn->real_escape_string($valoracion->titulovaloracion)  
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
        $query = sprintf("UPDATE valoracionesproducto V SET 
        puntuacion = '%s',
        comentario = '%s',
        titulo_valoracion = '%s'
        WHERE V.id_valoracion = %d",
        $conn->real_escape_string($valoracion->puntuacion),
        $conn->real_escape_string($valoracion->comentario),
        $conn->real_escape_string($valoracion->titulovaloracion),
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
        $query = sprintf("DELETE FROM valoracionesproducto WHERE id_valoracion = %d" , $idvaloracion);
        if ( ! $conn->query($query) ) {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
            return false;
        }
        return true;
    }

   
    private $idvaloracion;

    private $idusuario;

    private $idsubasta;

    private $tituloproducto;

    private $titulovaloracion;

    private $puntuacion;

    private $comentario;

    private $idvendedor;
    //Las valoraciones siempre estan relacionadas con un usuario
    private function __construct($idusuario,$idsubasta,$tituloproducto,$puntuacion, $comentario,$idvendedor,$titulovaloracion,$idvaloracion = null)
    {
        $this->idvaloracion = $idvaloracion;
        $this->idusuario = $idusuario;
        $this->idsubasta = $idsubasta;
        $this->tituloproducto = $tituloproducto;
        $this->titulovaloracion = $titulovaloracion;
        $this->puntuacion = $puntuacion;
        $this->comentario = $comentario;
        $this->idvendedor = $idvendedor;
        
    }

    public function getIdValoracion() {
        return $this->idvaloracion;
    }
   public function getIdSubasta() {
        return $this->idsubasta;
    }

    public function getIdUsuario() {
        return $this->idusuario;
    }

    public function gettituloproducto() {
        return $this->tituloproducto;
    }

    public function getPuntuacion() {
        return $this->puntuacion;
    }

    public function getComentario() {
        return $this->comentario;
    }

    public function getitulovaloracion() {
        return $this->titulovaloracion;
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
