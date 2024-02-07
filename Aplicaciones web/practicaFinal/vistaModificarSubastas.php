<?php

require_once __DIR__.'/includes/config.php';

$ModificarSubastas = new \es\ucm\fdi\aw\subastas\ModificarSubastas();
$ModificarSubastas = $ModificarSubastas->gestiona();

 
$tituloPagina = 'Borrar';
$contenidoPrincipal=<<<EOF
  
      $ModificarSubastas
    
EOF;

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantillaPerfil.php', $params);
