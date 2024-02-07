<?php
require_once __DIR__.'/includes/config.php';
require_once __DIR__.'/includes/src/usuarios/Usuario.php';

	
	$nombreUser=$_GET["user"];

	$usuario =  \es\ucm\fdi\aw\usuarios\Usuario::buscaUsuario($nombreUser) ;
	
	if ($usuario) {
		echo "existe";
	}else {
		echo "disponible";
	}
?>