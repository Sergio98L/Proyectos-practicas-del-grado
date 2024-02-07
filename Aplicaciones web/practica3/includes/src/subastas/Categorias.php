<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\MagicProperties;

class Categorias
{
    use MagicProperties;


    
   /* public static function crea($nombreUsuario, $password, $nombre,$email, $rol)
    {
        $user = new Usuario($nombreUsuario, self::hashPassword($password), $nombre,$email);
        $user->añadeRol($rol);
        return $user->guarda();
    }*/

    public static function buscaCategoria($nombreCategoria)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM categorias C WHERE C.nombre='%s'", $conn->real_escape_string($nombreCategoria));
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Categorias($fila['nombre'], $fila['id']);
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $result;
    }

    public static function buscaPorId($idCategoria)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM categorias WHERE id=%d", $idCategoria);
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Categorias($fila['nombre'], $fila['id']);
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $result;
    }
    public static function listarCategorias()
    {
        $app=Aplicacion::getInstance();
        $conn = $app->getConexionBd();
        $query =" ";
        $query = sprintf("SELECT * FROM categorias");
        //$query = sprintf("SELECT * FROM Subastas WHERE Subastas.titulo LIKE %'%s'%",$conn->real_escape_string($busqueda));
        
       // $query = sprintf("SELECT * FROM Subastas", $conn->real_escape_string($tituloSubasta));
        $rs = $conn->query($query);
        $categorias = array(); // Creamos un array vacío para almacenar las subastas
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $categoria = new Categorias(
                    $fila['nombre'] ,
                    $fila['id']
                );
                $categorias[] = $categoria; // Agregamos la subasta al array
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $categorias; // Devolvemos el array de subastas
    }

   /*
    private static function inserta($usuario)
    {
        $result = false;
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query=sprintf("INSERT INTO usuarios(nombreUsuario,nombre, email, password, fecha_registro) VALUES ('%s', '%s', '%s', '%s', NOW())"
            , $conn->real_escape_string($usuario->nombreUsuario)
            , $conn->real_escape_string($usuario->nombre)
            , $conn->real_escape_string($usuario->email)
            , $conn->real_escape_string($usuario->password)
        );
        if ( $conn->query($query) ) {
            $usuario->id = $conn->insert_id;
            $result = self::insertaRoles($usuario);
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $result;
    }
   
    private static function actualiza($usuario)
    {
        $result = false;
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query=sprintf("UPDATE usuarios U SET nombreUsuario = '%s', nombre='%s', password='%s' WHERE U.id=%d"
            , $conn->real_escape_string($usuario->nombreUsuario)
            , $conn->real_escape_string($usuario->nombre)
            , $conn->real_escape_string($usuario->password)
            , $usuario->id
        );
        if ( $conn->query($query) ) {
            $result = self::borraRoles($usuario);
            if ($result) {
                $result = self::insertaRoles($usuario);
            }
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        
        return $result;
    }
   */
  public static function numeroCategorias()
  {
      $app=Aplicacion::getInstance();
      $conn = $app->getConexionBd();
      $query = sprintf("SELECT COUNT(*) FROM categorias");
      $rs = $conn->query($query);
      $result = false;
      if ($rs) {
          $row = $rs->fetch_row();
          $result = $row[0];
          $rs->free();
      } else {
          error_log("Error BD ({$conn->errno}): {$conn->error}");
      }
      if($result<7){
        return $result;
       }else{
        return 7;
       }
      
  }
    private static function borra($Categoria)
    {
        return self::borraPorId($Categoria->id);
    }
    
    private static function borraPorId($idCategoria)
    {
        if (!$idCategoria) {
            return false;
        } 
        /* Los roles se borran en cascada por la FK
         * $result = self::borraRoles($usuario) !== false;
         */
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("DELETE FROM categoria C WHERE C.id = %d"
            , $idCategoria
        );
        if ( ! $conn->query($query) ) {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
            return false;
        }
        return true;
    }

    private $id;

    private $nombre;

    private function __construct($nombre,$id = null)
    {
        $this->id = $id;
        $this->nombre = $nombre;
    }

    public function getId()
    {
        return $this->id;
    }

    public function getNombre()
    {
        return $this->nombre;
    }

    
    public function guarda()
    {
        if ($this->id !== null) {
            return self::actualiza($this);
        }
        return self::inserta($this);
    }
    
    public function borrate()
    {
        if ($this->id !== null) {
            return self::borra($this);
        }
        return false;
    }
}
