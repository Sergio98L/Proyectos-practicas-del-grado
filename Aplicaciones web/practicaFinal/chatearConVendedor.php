<?php

require_once __DIR__.'/includes/config.php';

$chat = new \es\ucm\fdi\aw\mensajes\Chat();
$chat = $chat->gestiona();

$tituloPagina = 'Chat';
$contenidoPrincipal=<<<EOF
    $chat
   
EOF;

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantilla.php', $params);