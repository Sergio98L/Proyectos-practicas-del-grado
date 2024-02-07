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
		<script type="text/javascript" src="<?= $params['app']->resuelve('js/validacionForm.js') ?>"></script>


</head>
<body>
<?= $mensajes ?>
<div id="contenedorinicio">
	<?= $params['app']->doInclude('/vistas/comun/cabeceraLoginRegistro.php') ?>

	<main>
	
		<article>
		<?= $params['contenidoPrincipal'] ?>
		</article>
	</main>

</div>
</body>
</html>