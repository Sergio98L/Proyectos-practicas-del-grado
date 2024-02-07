<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\MagicProperties;

class Subasta
{
    use MagicProperties;

   
    
    public static function crea($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $imagen, $categoria, $estadoproducto)
    {
        $subasta = new subasta($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $imagen, $categoria, $estadoproducto);
        return $subasta->guarda();
    }
    public static function actualizaSubasta($idSubasta,$idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $imagen, $categoria, $estadoproducto,$idganador=null)
    {
        $subasta = new subasta($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $imagen, $categoria, $estadoproducto,$idSubasta,$idganador);
        return $subasta->guarda();
    }
    public static function buscaSubasta($tituloSubasta)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM Subastas S ", $conn->real_escape_string($tituloSubasta));
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Subasta( $fila['id_usuario'],  $fila['titulo'],  $fila['descripcion'],  $fila['fecha_inicio'],  $fila['fecha_fin'],  $fila['precio_inicial'],  $fila['precio_actual'],$fila['imagen'],$fila['categoria'],$fila['estadoproducto'], $fila['id_subasta'], $fila['id_ganador'], $fila['estado']);            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
       
        return $result;
    }
    public static function buscaPorId($idSubasta)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM Subastas S WHERE S.id_subasta='%d' ", $idSubasta );
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Subasta( $fila['id_usuario'],  $fila['titulo'],  $fila['descripcion'],  $fila['fecha_inicio'],  $fila['fecha_fin'],  $fila['precio_inicial'],  $fila['precio_actual'],$fila['imagen'],$fila['categoria'],$fila['estadoproducto'], $fila['id_subasta'], $fila['id_ganador'], $fila['estado']);            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
       
        return $result;
    }


    public static function listarSubastas($busqueda)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query =" ";
        if($busqueda=='ventas'){
            //listado general todas las subastas
            $query = sprintf("SELECT * FROM Subastas");

           }else if($busqueda=='borrador'){
        //listado de subsatas que tengo en estado borrador
            $query = sprintf("SELECT * FROM Subastas S WHERE S.estado= '%s'", $conn->real_escape_string($busqueda));

        }else if($busqueda=='programado'){
          //  listado de subastas que tengo en estado programadas
          $query = sprintf("SELECT * FROM Subastas S WHERE S.estado= '%s'", $conn->real_escape_string($busqueda));

        }else if($busqueda=='activo'){
            //listado de subastas activas
            $query = sprintf("SELECT * FROM Subastas S WHERE S.estado= '%s'", $conn->real_escape_string($busqueda));
            
        }else if($busqueda=='cerrada'){
            //listado de subastas cerradas 
            $query = sprintf("SELECT * FROM Subastas S WHERE S.estado= '%s'", $conn->real_escape_string($busqueda));

        }else{
            $query = sprintf("SELECT * FROM Subastas");
            //$query = sprintf("SELECT * FROM Subastas WHERE Subastas.titulo LIKE %'%s'%",$conn->real_escape_string($busqueda));
        }
       // $query = sprintf("SELECT * FROM Subastas", $conn->real_escape_string($tituloSubasta));
        $rs = $conn->query($query);
        $subastas = array(); // Creamos un array vacío para almacenar las subastas
        if ($rs) {
            while ($fila = $rs->fetch_assoc()) {
                $subasta = new Subasta(
                    $fila['id_usuario'],
                    $fila['titulo'],
                    $fila['descripcion'],
                    $fila['fecha_inicio'],
                    $fila['fecha_fin'],
                    $fila['precio_inicial'],
                    $fila['precio_actual'],
                    $fila['imagen'],
                    $fila['categoria'],
                    $fila['estadoproducto'],
                    $fila['id_subasta'],
                    $fila['id_ganador'],
                    $fila['estado']
                );
                $subastas[] = $subasta; // Agregamos la subasta al array
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $subastas; // Devolvemos el array de subastas
    }

   /* public static function buscaPorId($idUsuario)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM Usuarios WHERE id=%d", $idUsuario);
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Usuario($fila['nombreUsuario'], $fila['password'], $fila['nombre'],$fila['email'], $fila['id']);
            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $result;
    }*/
    function obtenerEstadoSubasta($fechaInicio, $fechaFin) {
        $fechaActual = date('Y-m-d H:i:s');
        
        if ($fechaInicio > $fechaActual) {
            return 'borrador';
        } else if ($fechaInicio <= $fechaActual && $fechaActual <= $fechaFin) {
            return 'activa';
        } else {
            return 'cerrada';
        }
    }
    private static function inserta($subasta)
    {
      //  echo($subasta->id_usuario.",".$subasta->titulo .",".$subasta->descripcion .",".$subasta->fecha_inicio.",". $subasta->fecha_fin .",".$subasta->precio_inicial.",". $subasta->precio_actual.",". $subasta->id_ganador .",".$subasta->estado .",".$subasta->imagen .",".$subasta->categoria.",". $subasta->estadoproducto.",". $subasta->obtenerEstadoSubasta($subasta->fecha_inicio,$subasta->fecha_fin));
        $result = false;
        $conn = Aplicacion::getInstance()->getConexionBd();
        
        $query=sprintf("INSERT INTO Subastas(id_usuario, titulo, descripcion, fecha_inicio, fecha_fin, precio_inicial, precio_actual, id_ganador, estado, imagen, categoria, estadoproducto) VALUES ('%d', '%s', '%s', '%s','%s', '%f', '%f', NULL,'%s','%s', '%s', '%s')"
            , $subasta->idusuario
            , $conn->real_escape_string($subasta->titulo)
            , $conn->real_escape_string($subasta->descripcion)
            , $conn->real_escape_string($subasta->fechainicio)
            , $conn->real_escape_string($subasta->fechafin)
            , $subasta->precioinicial
            , $subasta->precioactual
            , $conn->real_escape_string($subasta->obtenerEstadoSubasta($subasta->fechainicio,$subasta->fechafin))
            , $conn->real_escape_string($subasta->imagen)
            , $conn->real_escape_string($subasta->categoria)
            , $conn->real_escape_string($subasta->estadoproducto)
            
        );
        if ( $conn->query($query) ) {
            $subasta->idsubasta = $conn->insert_id;
            $result = $subasta;
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        return $result;
    }
   
    
    private static function actualiza($subasta)
    {
        $result = false;
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("UPDATE subastas S SET 
        titulo = '%s',
        descripcion = '%s',
        fecha_inicio = '%s',
        fecha_fin = '%s',
        precio_inicial = %f,
        precio_actual = %f,
        id_ganador = %d,
        estado = '%s',
        imagen = '%s',
        categoria = '%s',
        estadoproducto = '%s'
        WHERE S.id_subasta = %d",
        $conn->real_escape_string($subasta->titulo),
        $conn->real_escape_string($subasta->descripcion),
        $conn->real_escape_string($subasta->fechainicio),
        $conn->real_escape_string($subasta->fechafin),
        $subasta->precioinicial,
        $subasta->precioactual,
        $subasta->idganador,
        $conn->real_escape_string($subasta->estado),
        $conn->real_escape_string($subasta->imagen),
        $conn->real_escape_string($subasta->categoria),
        $conn->real_escape_string($subasta->estadoproducto),
        $subasta->idSubasta
    );
        if ( $conn->query($query) ) {
            $result = $subasta;
            
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
        
        return $result;
    }
   
      
    private static function borra($subasta)
    {
        return self::borraPorId($subasta->idSubasta);
    }
    
    private static function borraPorId($idSubasta)
    {
        if (!$idSubasta) {
            return false;
        } 
       
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("DELETE FROM subastas WHERE id_subasta = %d" , $idSubasta);
        if ( ! $conn->query($query) ) {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
            return false;
        }
        return true;
    }

   

    private $idsubasta;

    private $idusuario;

    private $titulo;

    private $descripcion;

    private $fechainicio;
    
    private  $fechafin;

    private $precioinicial;

    private $precioactual;

    private $idganador;

    private $estado;

    private $imagen;

    private $categoria;

    private $estadoproducto;

    private function __construct($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual,$imagen, $categoria, $estadoproducto,$idsubasta = null,$idganador = null, $estado = null)
    {
        $this->idsubasta = $idsubasta;
        $this->idusuario = $idusuario;
        $this->titulo = $titulo;
        $this->descripcion = $descripcion;
        $this->fechainicio = $fechainicio;
        $this->fechafin = $fechafin;
        $this->precioinicial = $precioinicial;
        $this->precioactual = $precioactual;
        $this->idganador = $idganador;
        $this->estado = $estado;
        $this->imagen = $imagen;
        $this->categoria = $categoria;
        $this->estadoproducto = $estadoproducto;
    }
   public function getIdSubasta() {
        return $this->idsubasta;
    }

    public function getIdUsuario() {
        return $this->idusuario;
    }

    public function getTitulo() {
        return $this->titulo;
    }

    public function getDescripcion() {
        return $this->descripcion;
    }

    public function getFechaInicio() {
        return $this->fechainicio;
    }
    public function getFechaFin() {
        return $this->fechafin;
    }
    public function getPrecioInicial() {
        return $this->precioinicial;
    }

    public function getPrecioActual() {
        return $this->precioactual;
    }

    public function getIdGanador() {
        return $this->idganador;
    }

    public function getEstado() {
        return $this->estado;
    }

    public function getImagen() {
        return $this->imagen;
    }

    public function getCategoria() {
        return $this->categoria;
    }

    public function getEstadoProducto() {
        return $this->estadoproducto;
    }

    public function guarda()
    {
        if ($this->idsubasta !== null) {
            return self::actualiza($this);
        }
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
