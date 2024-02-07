<?php 
//Si hacemos el include de config si podemos acceder a la base de datos, problema al usar _DIR_ pilla la ruta hasta /mensajes en vez de la ruta raiz
require_once 'D:\XAMPP\htdocs\Archivos_GIT\practicaFinal\includes\config.php';

       $conn = $app->getConexionBd();
       $result = false;
       $emisorId=$app->idUsuario();
       $receptor_id = mysqli_real_escape_string($conn, $_POST['incoming_id']);
       $message = mysqli_real_escape_string($conn, $_POST['message']);
       $idSubasta = mysqli_real_escape_string($conn, $_POST['subasta_id']);



       $query=sprintf("INSERT INTO mensajes(id_subasta_aso,emisor_id,receptor_id, mensaje, fecha) VALUES ('$idSubasta','%d', '%d', '%s',NOW())"
           , $conn->real_escape_string($emisorId)
           , $conn->real_escape_string($receptor_id)
           , $conn->real_escape_string($message)
       );
       if ( !$conn->query($query) ) {
        error_log("Error BD ({$conn->errno}): {$conn->error}");
       }  
?>