<?php

require_once 'D:\XAMPP\htdocs\Archivos_GIT\practicaFinal\includes\config.php';

$conn = $app->getConexionBd();
$emisorId = $app->idUsuario();
$receptor_id = mysqli_real_escape_string($conn, $_POST['incoming_id']);
$subasta_aso = mysqli_real_escape_string($conn, $_POST['subasta_id']);;

//$query = sprintf("SELECT * FROM mensajes WHERE emisor_id = %d && receptor_id= %d && id_subasta_aso=%d  ORDER BY id_mensaje", $emisorId, $receptor_id,$subasta_aso);
$query = sprintf("
SELECT * FROM mensajes LEFT JOIN usuarios ON usuarios.id_usuario = mensajes.emisor_id
                WHERE (emisor_id = {$emisorId} AND receptor_id = {$receptor_id})
                OR (emisor_id = {$receptor_id} AND receptor_id = {$emisorId}) ORDER BY id_mensaje");

$rs = $conn->query($query);
$output = "";

if ($rs->num_rows > 0) {
    while ($row = mysqli_fetch_assoc($rs)) {
        if ($row['emisor_id'] === $emisorId) {
            $output .= '<div class="chat outgoing">
                            <div class="details">
                                <p>' . $row['mensaje'] . '</p>
                            </div>
                        </div>';
        } else {
            $output .= '<div class="chat incoming">
                            <div class="details">
                                <p>' . $row['mensaje'] . '</p>
                            </div>
                        </div>';
        }
    }
} else {
    $output .= '<div class="text">No hay mensajes disponibles. Una vez que envíe el mensaje, aparecerán aquí.</div>';
}
echo $output;
