// Seleccionamos el elemento que contiene el contador
var contador = document.getElementById("contador");

// Definimos la fecha futura (puedes cambiar esta fecha a la que desees)
var fecha = $("#contador").text();

var fechaFutura = new Date(fecha).getTime();

// Creamos la función que se ejecutará cada segundo
var intervalo = setInterval(function() {

  // Obtenemos la fecha y hora actual del equipo

  var fechaActual = new Date().getTime();

  // Calculamos la diferencia en milisegundos entre la fecha actual y la fecha futura
  var diferencia = fechaFutura - fechaActual;

  // Convertimos la diferencia en milisegundos a días, horas, minutos y segundos
  var dias = Math.floor(diferencia / (1000 * 60 * 60 * 24));
  var horas = Math.floor((diferencia % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
  var minutos = Math.floor((diferencia % (1000 * 60 * 60)) / (1000 * 60));
  var segundos = Math.floor((diferencia % (1000 * 60)) / 1000);
  // Actualizamos el contenido del elemento con el nuevo valor del contador
  document.getElementById("contador").innerHTML ='Tiempo Restante: '+ dias +' D:'+horas+' H:'+minutos+' M:'+segundos+' S';

  // Si llegamos a la fecha futura, detenemos el intervalo
  if (diferencia <= 0) {
    var params = window.location.search;
    params = params.substring(1);
    var paramsArray = params.split('=');

// Ahora puedes acceder a los valores de los parámetros por su nombre

  var url = baseurl +"actualizarSubasta.php?subasta=" + paramsArray[1];
     
  $.get(url);

    clearInterval(intervalo);
    contador.innerHTML = '¡La fecha futura ha llegado!';
  }

}, 1000); // Intervalo de 1 segundo