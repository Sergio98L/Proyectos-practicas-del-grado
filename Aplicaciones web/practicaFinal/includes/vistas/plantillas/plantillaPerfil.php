<?php
$params['app']->doInclude('/vistas/helpers/plantilla.php');
$mensajes = mensajesPeticionAnterior();
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
    <title><?= $params['tituloPagina'] ?></title>
	<link rel="stylesheet" type="text/css" href="<?= $params['app']->resuelve('/css/estilo.css') ?>" />
	<script type="text/javascript" src="<?= $params['app']->resuelve('js/jquery-3.6.0.min.js')?>"></script>
	<script type="text/javascript" src="<?= $params['app']->resuelve('configjs.php') ?>"></script>
</head>
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
		<div class="estructuraperfil">
			
			<?= $params['app']->doInclude('/vistas/comun/sidebarIzqPerfil.php') ?>
			<?= $params['contenidoPrincipal'] ?>
		</div>
		</article>
	</main>
<?php
$params['app']->doInclude('/vistas/comun/pie.php');
?>
</div>
</body>
<script type="text/javascript" src="<?= $params['app']->resuelve('/js/contador.js') ?>"></script>
</html>
