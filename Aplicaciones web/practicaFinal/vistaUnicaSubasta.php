<?php
require_once __DIR__.'/includes/config.php';
require_once __DIR__.'/includes/src/subastas/ListadoSubastas.php';

$tituloPagina = 'Mi perfil';
$contenidoPrincipal='';
$contenido='ventas';

$idpuja=$_GET["idsubasta"];


$hacerpuja= new \es\ucm\fdi\aw\subastas\HacerPuja();
$hacerpuja = $hacerpuja->gestiona();

if ($_POST != null){
    unset($_POST);
    unset($hacerpuja);
    $hacerpuja= new \es\ucm\fdi\aw\subastas\HacerPuja();
    $hacerpuja = $hacerpuja->gestiona();
}


$resultadoTablaSubastas = \es\ucm\fdi\aw\subastas\ListadoSubastas::listadoUnicaSubasta($idpuja);

$tituloPagina = 'Subasta';
$contenidoPrincipal=<<<EOF
  	
      <fieldset>
    
      <div>
      $resultadoTablaSubastas
      $hacerpuja
      <div>
      </fieldset>
EOF;

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantillaInicio.php', $params);


