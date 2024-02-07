<?php

require_once __DIR__.'/includes/config.php';

$formRegistroValoracion = new \es\ucm\fdi\aw\valoraciones\FormularioValoracionesProducto();
$formRegistroValoracion = $formRegistroValoracion->gestiona();

$tituloPagina = 'Valoraciones';
$contenidoPrincipal=<<<EOF
  	<h1>Pagina de Valoraciones aaaaa</h1>
    $formRegistroValoracion
   
EOF;

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantilla.php', $params);