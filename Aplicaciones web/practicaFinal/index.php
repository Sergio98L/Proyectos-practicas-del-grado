<?php

require_once __DIR__.'/includes/config.php';
require_once __DIR__.'/includes/src/subastas/ListadoCategorias.php';

$tituloPagina = 'Portada';

$contenidoPrincipal=<<<EOS

<header>
  <nav>
    <ul>
EOS; 

$contenidoPrincipal .= \es\ucm\fdi\aw\subastas\ListadoCategorias::menuCategorias(10);

$contenidoPrincipal .=<<<EOS
                  </ul>
          </li>
        </ul>
      </nav>
    </header>
    <section class="carrusel-section">
          <div class="carousel">
          <button id="retroceder"></button>
          <div id="imagen"></div>
          
      
      <div class="controles">
          <button id="play"></button>
          <button id="stop" disabled></button>
      </div>
      <button id="avanzar"></button>
      </div>
    </section>
    <section>
      <h2>Subastas destacadas</h2>
      <ul class="listasdestacadas">

  EOS;
  $nSubastas = \es\ucm\fdi\aw\subastas\Subasta::numeroSubastas();
  $contenidoPrincipal .= \es\ucm\fdi\aw\subastas\ListadoSubastas::formularioSubastas($nSubastas);

  $contenidoPrincipal .="  </ul></section> <section>  <h2>Categorias destacadas</h2> <ul class='listasdestacadas'>";

  $nCategorias = \es\ucm\fdi\aw\subastas\Categorias::numeroCategorias();
  $contenidoPrincipal .= \es\ucm\fdi\aw\subastas\ListadoCategorias::formularioCategorias($nCategorias);


      $contenidoPrincipal .= "</ul> </section>";
    


$params = ['tituloPagina' => $tituloPagina, 'contenidoPrincipal' => $contenidoPrincipal];
$app->generaVista('/plantillas/plantillaInicio.php', $params);