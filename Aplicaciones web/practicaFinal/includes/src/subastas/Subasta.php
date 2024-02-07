<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\MagicProperties;

class Subasta
{
    use MagicProperties;

   
    
    public static function crea($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $categoria, $estadoproducto)
    {
        $subasta = new subasta($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $categoria, $estadoproducto);
        return $subasta->guarda();
    }
    public static function actualizaSubasta($idSubasta,$idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $categoria, $estadoproducto,$idganador=null)
    {
        $subasta = new subasta($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $categoria, $estadoproducto,$idSubasta,$idganador);
        return $subasta->guarda();
    }
    public static function buscaSubasta($tituloSubasta)
    {
        $app=Aplicacion::getInstance();
        $conn = $app->getConexionBd();
        $query = sprintf("SELECT * FROM subastas S WHERE S.titulo LIKE '%%%s%%'", $conn->real_escape_string($tituloSubasta));
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Subasta( $fila['id_usuario'],  $fila['titulo'],  $fila['descripcion'],  $fila['fecha_inicio'],  $fila['fecha_fin'],  $fila['precio_inicial'],  $fila['precio_actual'],$fila['categoria'],$fila['estadoproducto'], $fila['id_subasta'], $fila['id_ganador'], $fila['estado']);            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
       
        return $result;
    }
    public static function buscaPorId($idSubasta)
    {
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("SELECT * FROM subastas S WHERE S.id_subasta='%d' ", $idSubasta );
        $rs = $conn->query($query);
        $result = false;
        if ($rs) {
            $fila = $rs->fetch_assoc();
            if ($fila) {
                $result = new Subasta( $fila['id_usuario'],  $fila['titulo'],  $fila['descripcion'],  $fila['fecha_inicio'],  $fila['fecha_fin'],  $fila['precio_inicial'],  $fila['precio_actual'],$fila['categoria'],$fila['estadoproducto'], $fila['id_subasta'], $fila['id_ganador'], $fila['estado']);            }
            $rs->free();
        } else {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
        }
       
        return $result;
    }


    public static function listarSubastas($busqueda,$buscar=null)
    {
        $app=Aplicacion::getInstance();
        $idusuario=$app->idUsuario();
        $conn = $app->getConexionBd();
        $query =" ";
        if($busqueda=='ventas'){
            //listado general todas las subastas
            $query = sprintf("SELECT * FROM subastas S WHERE S.id_usuario= '%d'",  $idusuario);

           }else if($busqueda=='borrador'){
        //listado de subsatas que tengo en estado borrador
            $query = sprintf("SELECT * FROM subastas S WHERE S.estado= '%s'AND S.id_usuario= '%d'", $conn->real_escape_string($busqueda), $idusuario);

        }else if($busqueda=='programado'){
          //  listado de subastas que tengo en estado programadas
          $query = sprintf("SELECT * FROM subastas S WHERE S.estado= '%s'AND S.id_usuario= '%d'", $conn->real_escape_string($busqueda), $idusuario);

        }else if($busqueda=='activa'){
            //listado de subastas activas
            $query = sprintf("SELECT * FROM subastas S WHERE S.estado= '%s' AND S.id_usuario= '%d'", $conn->real_escape_string($busqueda), $idusuario);
            
        }else if($busqueda=='cerrada'){
            //listado de subastas cerradas 
            $query = sprintf("SELECT * FROM subastas S WHERE S.estado= '%s' AND S.id_usuario= '%d'", $conn->real_escape_string($busqueda), $idusuario);

        }else if($busqueda=='busquedaTitulo'){
            //listado de subastas buscadas por un titulo
            $query = sprintf("SELECT * FROM subastas S WHERE S.titulo LIKE '%%%s%%'", $conn->real_escape_string($buscar));

        }else if($busqueda=='categoria'){
            //listado de subastas por categoria
            $query = sprintf("SELECT * FROM subastas S  WHERE S.categoria= '%s'", $conn->real_escape_string($buscar));

        }else if($busqueda=='compras'){
            //listado de subastas cerradas 
            
            $query = sprintf("SELECT * FROM subastas S WHERE S.id_ganador= '%s'", $conn->real_escape_string($idusuario));
        }else{
            $query = sprintf("SELECT * FROM subastas");
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
      //  echo($subasta->id_usuario.",".$subasta->titulo .",".$subasta->descripcion .",".$subasta->fecha_inicio.",". $subasta->fecha_fin .",".$subasta->precio_inicial.",". $subasta->precio_actual.",". $subasta->id_ganador .",".$subasta->estado .",".$subasta->categoria.",". $subasta->estadoproducto.",". $subasta->obtenerEstadoSubasta($subasta->fecha_inicio,$subasta->fecha_fin));
        $result = false;
        $conn = Aplicacion::getInstance()->getConexionBd();
                                            
        $query=sprintf("INSERT INTO subastas(id_usuario, titulo, descripcion, fecha_inicio, fecha_fin, precio_inicial, precio_actual, id_ganador, estado, categoria, estadoproducto) VALUES ('%d', '%s', '%s', '%s','%s', '%f', '%f', NULL,'%s', '%s', '%s')"
            , $subasta->idusuario
            , $conn->real_escape_string($subasta->titulo)
            , $conn->real_escape_string($subasta->descripcion)
            , $conn->real_escape_string($subasta->fechainicio)
            , $conn->real_escape_string($subasta->fechafin)
            , $subasta->precioinicial
            , $subasta->precioactual
            , $conn->real_escape_string($subasta->obtenerEstadoSubasta($subasta->fechainicio,$subasta->fechafin))
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
        $conn->real_escape_string($subasta->obtenerEstadoSubasta($subasta->fechainicio,$subasta->fechafin)),
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
        Imagen::borraPorIdSubasta($idSubasta);
        $conn = Aplicacion::getInstance()->getConexionBd();
        $query = sprintf("DELETE FROM subastas WHERE id_subasta = %d" , $idSubasta);
        if ( ! $conn->query($query) ) {
            error_log("Error BD ({$conn->errno}): {$conn->error}");
            return false;
        }
        return true;
    }

    public static function numeroSubastas()
    {
        $app=Aplicacion::getInstance();
        $conn = $app->getConexionBd();
        $query = sprintf("SELECT COUNT(*) FROM subastas");
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


    private $categoria;

    private $estadoproducto;

    private function __construct($idusuario, $titulo, $descripcion, $fechainicio, $fechafin, $precioinicial, $precioactual, $categoria, $estadoproducto,$idsubasta = null,$idganador = null, $estado = null)
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
