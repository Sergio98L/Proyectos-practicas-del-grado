<?php

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\usuarios\FormularioLogout;
$app = Aplicacion::getInstance();

function mostrarUsername()
{
    $html = '';
    $app = Aplicacion::getInstance();
    if ($app->usuarioLogueado()) {
        $nombreUsuario = $app->nombreUsuario();
        $html = "${nombreUsuario}";
    } else {
        $loginUrl = $app->resuelve('/login.php');
        $registroUrl = $app->resuelve('/registro.php');
        $html = <<<EOS
        Usuario desconocido. <a href="{$loginUrl}">Login</a> <a href="{$registroUrl}">Registro</a>
      EOS;
    }

    return $html;
}
?>

<h1>Vista general de subastas en Mi tiktak </h1>
      
      <div>
          <nav>
          <ul>
          <li>  <a href="{$actividad}">Actividad</a></li> 
          <li>  <a href="<?= $app->resuelve('/mensajesPerfil.php')?>">Mensajes</a></li> 
          <li>   <a href="{$notificaciones}">Notificaciones</a></li> 
          </ul>
          </nav>
          
    <div class="saludo">
      <?= mostrarUsername(); ?>
    </div>
  </div>
