<?php
require_once __DIR__.'/includes/config.php';
require_once __DIR__.'/includes/src/subastas/listadoSubastas.php';

$tituloPagina = 'Mi perfil';
$contenidoPrincipal='';
$contenido='ventas';
if ($app->tieneRol(es\ucm\fdi\aw\usuarios\Usuario::USER_ROLE)||$app->tieneRol(es\ucm\fdi\aw\usuarios\Usuario::BUSSINES_ROLE)) {
    
    $addsubastaUrl = $app->resuelve('/addSubasta.php');
    $modificarsubastaUrl = $app->resuelve('/vistaModificarSubastas.php');
    
  $contenidoPrincipal=<<<EOS

                            <div>
                          
                            <a href="{$addsubastaUrl}">subir subasta</a>
                            <a href="{$modificarsubastaUrl}">modificar subastas</a>
                            </div>

    
  EOS;
  $contenido=$_GET["ventas"];

$contenidoPrincipal .= \es\ucm\fdi\aw\subastas\listasubastas($contenido);
 
} else {
  $contenidoPrincipal=<<<EOS
    <h1>Usuario no registrado!</h1>
    <p>Debes iniciar sesión para ver el contenido.</p>
    
  EOS;
}

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantillaPerfil.php', $params);