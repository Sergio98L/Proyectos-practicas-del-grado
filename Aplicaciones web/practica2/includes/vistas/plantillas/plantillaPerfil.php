<?php
$params['app']->doInclude('/vistas/helpers/plantilla.php');
$mensajes = mensajesPeticionAnterior();
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
    <title><?= $params['tituloPagina'] ?></title>
	<link rel="stylesheet" type="text/css" href="<?= $params['app']->resuelve('/css/estilo.css') ?>" /></head>
<body>
<?= $mensajes ?>
<div id="contenedorperfilusuario">
<?php
$params['app']->doInclude('/vistas/comun/cabecera.php');
//$params['app']->doInclude('/vistas/comun/sidebarIzqPerfil.php');
?>
	<main>
		<article>
		<?= $params['app']->doInclude('/vistas/comun/cabeceraPerfilusuario.php') ?>
		<div>
			<?= $params['contenidoPrincipal'] ?>
			<?= $params['app']->doInclude('/vistas/comun/sidebarIzqPerfil.php') ?>
		</div>
		</article>
	</main>
<?php
$params['app']->doInclude('/vistas/comun/pie.php');
?>
</div>
</body>
</html>
