<?php

require_once __DIR__.'/includes/config.php';

$ModificarSubastas = new \es\ucm\fdi\aw\subastas\modificarSubastas();
$ModificarSubastas = $ModificarSubastas->gestiona();

 
$tituloPagina = 'Borrar';
$contenidoPrincipal=<<<EOF
  	<h1>Listado de subasta</h1>
      $ModificarSubastas
    
EOF;

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantillaPerfil.php', $params);
