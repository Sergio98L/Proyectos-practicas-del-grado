<?php

require_once __DIR__.'/includes/config.php';

$formRegistroObjeto = new \es\ucm\fdi\aw\subastas\FormularioObjeto();
$formRegistroObjeto = $formRegistroObjeto->gestiona();


$tituloPagina = 'Registro';
$contenidoPrincipal=<<<EOF
  	<h1>Registro de subasta</h1>
    $formRegistroObjeto
EOF;

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantilla.php', $params);