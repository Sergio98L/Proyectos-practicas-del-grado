<?php
use es\ucm\fdi\aw\Aplicacion;

$app = Aplicacion::getInstance();
?>
<nav class="sidebarIzqPerfil">
	<h3>Navegación</h3>
	<ul>
		<li><a href="<?= $app->resuelve('/resumenPerfil.php')?>">Resumen</a></li>
		<li><a href="<?= $app->resuelve('/comprasPerfil.php')?>">Compras</a></li>
		<li><a href="<?= $app->resuelve('/guardadosPerfil.php')?>">Guardados</a></li>
		<li class="dropdown"><a href="<?= $app->resuelve('/ventasPerfil.php')?>">Ventas</a>
			<ul class="dropdown-content">
				<li><a href="<?= $app->resuelve('/contenidomiperfil.php?ventas=ventas')?>">Vista general</a></li> 
				<li><a href="<?= $app->resuelve('/contenidomiperfil.php?ventas=borrador')?>">Borradores</a></li>
				<li><a href="<?= $app->resuelve('/contenidomiperfil.php?ventas=programado')?>">Programados</a></li>
				<li><a href="<?= $app->resuelve('/contenidomiperfil.php?ventas=activa')?>">Activos</a></li>
				<li><a href="<?= $app->resuelve('/contenidomiperfil.php?ventas=cerrada')?>">Vendidos</a></li>
			</ul>
		</li>
	</ul>
</nav>
