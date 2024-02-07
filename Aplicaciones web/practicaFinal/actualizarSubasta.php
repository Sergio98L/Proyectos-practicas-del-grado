<?php

require_once __DIR__.'/includes/config.php';
require_once __DIR__.'/includes/src/subastas/Subasta.php';

$idsubasta=$_GET["subasta"];
$subasta =  \es\ucm\fdi\aw\subastas\Subasta::buscaPorId($idsubasta) ;
$fechaActual=date('Y-m-d H:i:s');

return \es\ucm\fdi\aw\subastas\Subasta::actualizaSubasta($subasta->getIdSubasta(),$subasta->getIdUsuario(), $subasta->getTitulo(), $subasta->getDescripcion(), $subasta->getFechaInicio(), $subasta->getFechaFin(), $subasta->getPrecioInicial(), $subasta->getPrecioActual(), $subasta->getCategoria(), $subasta->getEstadoProducto(),$subasta->getIdGanador()) ;


