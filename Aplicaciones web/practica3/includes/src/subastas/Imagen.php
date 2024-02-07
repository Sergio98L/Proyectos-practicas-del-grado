<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\MagicProperties;

class Imagen
{
    const PUBLICA = 0;

    const PRIVADA = 1;

    const TIPOS_ACCESO = [self::PUBLICA, self::PRIVADA];

    public static function crea($id_subasta,$nombre, $mimeType, $tipoAcceso, $ruta)
    {
        $imagen = new Imagen($id_subasta,$ruta, $nombre, $mimeType, $tipoAcceso);
        return $imagen;
    }

    public static function listaImagenes()
    {
        return self::getImagenes();
    }

    private static function getImagenes($tipoAcceso = null)
    {
        $result = [];

        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = 'SELECT * FROM imagenes';
        if ($tipoAcceso !== null) {
            $query = sprintf('SELECT * FROM imagenes I WHERE tipoAcceso = %d', $tipoAcceso);
        }
        
        $rs = $conn->query($query);
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $result[] = new Imagen($fila['id_subasta'],$fila['ruta'], $fila['nombre'], $fila['mimeType'], $fila['tipoAcceso'], $fila['id_imagen']);
            }
            $rs->free();
        } else {
            error_log($conn->error);
        }

        return $result;
    }
    public static function buscaPorsubasta($idSubasta)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM imagenes I WHERE I.id_subasta='%d' ", $idSubasta );
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Imagen($fila['id_subasta'],$fila['ruta'], $fila['nombre'], $fila['mimeType'], $fila['tipoAcceso'], $fila['id_imagen']);
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
       
        return $result;
    }
    public static function buscaPorTipoAcceso($tipoAcceso = self::PUBLICA)
    {
        return self::getImagenes($tipoAcceso);
    }

    public static function buscaPorId($idImagen)
    {
        $result = null;

        $conn = BD::getInstance()->getConexionBd();
        $query = sprintf('SELECT * FROM imagenes I WHERE I.id_imagen = %d', intval($idImagen));
        $rs = $conn->query($query);
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $result = new Imagen($fila['id_subasta'],$fila['ruta'], $fila['nombre'], $fila['mimeType'], $fila['tipoAcceso'], $fila['id_imagen']);
            }
            $rs->free();
        } else {
            error_log($conn->error);
        }

        return $result;
    }

    private static function inserta($imagen)
    {
        $result = false;

        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf(
            "INSERT INTO imagenes (id_subasta,ruta, nombre, mimeType, tipoAcceso) VALUES ( %d,'%s', '%s', '%s', %d)",
            $imagen->id_subasta,
            $conn->real_escape_string($imagen->ruta),
            $conn->real_escape_string($imagen->nombre),
            $conn->real_escape_string($imagen->mimeType),
            $imagen->tipoAcceso
        );


        $result = $conn->query($query);
        if ($result) {
            $imagen->id_imagen = $conn->insert_id;
            $result = $imagen;
        } else {
            error_log($conn->error);
        }

        return $result;
    }

    private static function actualiza($imagen)
    {
        $result = false;

        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf(
            "UPDATE imagenes I SET id_subasta = %d ,ruta = '%s', nombre = '%s', mimeType = '%s', tipoAcceso = %d WHERE I.id_imagen = %d",
            $imagen->id_subasta,
            $conn->real_escape_string($imagen->ruta),
            $conn->real_escape_string($imagen->nombre),
            $conn->real_escape_string($imagen->mimeType),
            $imagen->tipoAcceso,
            $imagen->id_imagen
        );
        $result = $conn->query($query);
        if (!$result) {
            error_log($conn->error);
        } else if ($conn->affected_rows != 1) {
            error_log(__CLASS__ . ": Se han actualizado '$conn->affected_rows' !");
        }

        return $result;
    }

    private static function borra($imagen)
    {
        return self::borraPorId($imagen->id_imagen);
    }

    public static function borraPorId($idImagen)
    {
        $result = false;

        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("DELETE FROM imagenes WHERE id_imagen = %d", intval($idImagen));
        $result = $conn->query($query);
        if (!$result) {
            error_log($conn->error);
        } else if ($conn->affected_rows != 1) {
            error_log("Se han borrado '$conn->affected_rows' !");
        }

        return $result;
    }
    public static function borraPorIdSubasta($idSubasta)
    {
        $result = false;

        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("DELETE FROM imagenes WHERE id_subasta = %d", intval($idSubasta));
        $result = $conn->query($query);
        if (!$result) {
            error_log($conn->error);
        } else if ($conn->affected_rows != 1) {
            error_log("Se han borrado '$conn->affected_rows' !");
        }

        return $result;
    }
    use MagicProperties;

    private $id_imagen;

    private $id_subasta;

    private $ruta;

    private $nombre;

    private $mimeType;

    private $tipoAcceso;

    private function __construct($id_subasta,$ruta, $nombre, $mimeType, $tipoAcceso = self::PUBLICA,  $id_imagen = NULL)
    {
        $this->id_subasta = $id_subasta;
        $this->ruta = $ruta;
        $this->nombre = $nombre;
        $this->mimeType = $mimeType;
        if (!in_array($tipoAcceso, self::TIPOS_ACCESO)) {
            throw new Exception("$tipoAcceso no es un tipo de acceso válido");
        }
        $this->tipoAcceso = intval($tipoAcceso);
        $this->id_imagen = intval($id_imagen);
    }

    public function getid_imagen()
    {
        return $this->id_imagen;
    }
    public function getid_subasta()
    {
        return $this->id_subasta;
    }
    public function getRuta()
    {
        return $this->ruta;
    }

    public function setRuta($nuevaRuta)
    {
        $this->ruta = $nuevaRuta;
    }
    
    public function getNombre()
    {
        return $this->nombre;
    }

    public function setNombre($nuevoNombre)
    {
        $this->nombre = $nuevoNombre;
    }

    public function getMimeType()
    {
        return $this->mimeType;
    }

    public function getTipoAcceso()
    {
        return $this->tipoAcceso;
    }

    public function guarda()
    {
        if (!$this->id_imagen) {
            self::inserta($this);
        } else {
            self::actualiza($this);
        }

        return $this;
    }

    public function borrate()
    {
        if ($this->id_imagen !== null) {
            return self::borra($this);
        }
        return false;
    }
}
