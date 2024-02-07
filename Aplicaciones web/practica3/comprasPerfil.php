<?php

require_once __DIR__.'/includes/config.php';

$SubastasCompradas = new \es\ucm\fdi\aw\subastas\MostrarSubastasCompradas();
$SubastasCompradas = $SubastasCompradas->gestiona();

 
$tituloPagina = 'Compras';
$contenidoPrincipal=<<<EOF
  	<h1>Listado de subastas compradas</h1>
      $SubastasCompradas
    
EOF;

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantillaPerfil.php', $params);
