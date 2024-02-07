<?php
require_once __DIR__.'/includes/config.php';
require_once __DIR__.'/includes/src/subastas/ListadoSubastas.php';

$tituloPagina = 'Mi perfil';
$contenidoPrincipal='';
$contenido='ventas';
if ($app->tieneRol(es\ucm\fdi\aw\usuarios\Usuario::USER_ROLE)||$app->tieneRol(es\ucm\fdi\aw\usuarios\Usuario::BUSSINES_ROLE)) {
    
    $addsubastaUrl = $app->resuelve('/addSubasta.php');
    $modificarsubastaUrl = $app->resuelve('/vistaModificarSubastas.php');
    
  $contenidoPrincipal=<<<EOS

                            
          <div class="top-bar">
          <div class="stats">
            <div class="datos">
              <span class="number">12</span> anuncios activos
            </div>
            <div class="datos">
              <span class="number">25</span> ventas
            </div>
            <div class="datos">
              <span class="number">1250</span> € ganados
            </div>
          </div>
          <div class="actions">
            <a href="{$addsubastaUrl}" class="btn">Subir anuncios</a>
            <a href="{$modificarsubastaUrl}" class="btn">Modificar anuncios</a>
          </div>
        </div>


    
  EOS;
  $contenido=$_GET["ventas"];

$contenidoPrincipal .= \es\ucm\fdi\aw\subastas\listasubastas($contenido);
$contenidoPrincipal .= "</div>";
} else {
  $contenidoPrincipal=<<<EOS
    <h1>Usuario no registrado!</h1>
    <p>Debes iniciar sesión para ver el contenido.</p>
    
  EOS;
}

$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantillaPerfil.php', $params);