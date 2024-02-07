<?php



use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\usuarios\FormularioLogout;
$app = Aplicacion::getInstance();

function mostrarSaludo()
{
    $html = '';
	$busqueda= '';
    $app = Aplicacion::getInstance();
    
    if ($_SERVER['PHP_SELF'] == RUTA_APP.'/registro.php') {
     $loginUrl = $app->resuelve('/login.php');
     $html = <<<EOS
      ¿Ya estas registrado? <a href="{$loginUrl}">Identificate</a> 
     EOS;
  } elseif ($_SERVER['PHP_SELF'] == RUTA_APP.'/login.php') {
     
  }
    

    return $html;
}

?>

<html>
<head><title>Cabecera</title></head>
<body>

<header class="CabeceraPrincipal">

	<div class="CabeceraSuperiorlogreg">		
	<?php echo mostrarSaludo(); ?>
        

	</div>

    <div class="CabeceraInferiorlogreg">		
		<div class="Imagen">		
   
    <a href="index.php">	<img src= <?php echo RUTA_IMGS.'\logotiktak.jpeg'; ?>	 alt="Logo TikTak"></a>
		</div>
		
    </div>
</header>
</body>
</html>