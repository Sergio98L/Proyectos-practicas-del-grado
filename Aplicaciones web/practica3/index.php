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
    <section>
    <div class="carousel-container">
      <div class="slides">
        <div class="slide">
          <img src="img1.jpg" alt="Imagen 1">
          <h3>Título de la imagen 1</h3>
        </div>
        <div class="slide">
          <img src="img2.jpg" alt="Imagen 2">
          <h3>Título de la imagen 2</h3>
        </div>
        <div class="slide">
          <img src="img3.jpg" alt="Imagen 3">
          <h3>Título de la imagen 3</h3>
        </div>
      </div>
      <button class="prev-btn">Anterior</button>
      <button class="next-btn">Siguiente</button>
    </div>
    <div id="carrusel">
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