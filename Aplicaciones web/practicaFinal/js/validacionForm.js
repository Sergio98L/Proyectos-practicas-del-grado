$(document).ready(function() {

	$("#correoOK").hide();
	$("#userOK").hide();

	$("#email").change(function(){                                  
		const campo = $("#email"); // referencia jquery al campo
		campo[0].setCustomValidity(""); // limpia validaciones previas
		// validación html5, porque el campo es <input type="email" ...>
		const esCorreoValido = campo[0].checkValidity();
		if (esCorreoValido && correoValidoComplu(campo.val())) {
			// el correo es válido y acaba por @ucm.es: marcamos y limpiamos quejas
		
			// tu código aquí: coloca la marca correcta
			document.getElementById("validEmail").innerHTML = '&#x2714;';
			campo[0].setCustomValidity("");
		} else {			
			// correo invalido: ponemos una marca y nos quejamos

			// tu código aquí: coloca la marca correcta
			document.getElementById("validEmail").innerHTML = '&#x26a0;';
			campo[0].setCustomValidity(
				"El correo debe ser válido y acabar por @ucm.es");
		}
	});
	$("#password2").change(function(){                                  
		const pass1 = $("#password"); // referencia jquery al campo
		const pass2 = $("#password2");
		pass1[0].setCustomValidity(""); // limpia validaciones previas
		const espassword1valida = pass1[0].checkValidity();
		if (espassword1valida && passwordvalid(pass1.val(),pass2.val())) {
			// el correo es válido y acaba por @ucm.es: marcamos y limpiamos quejas
		
			// tu código aquí: coloca la marca correcta
			document.getElementById("validpassword").innerHTML = '&#x2714;';
			campo[0].setCustomValidity("");
		} else {			
			// correo invalido: ponemos una marca y nos quejamos

			// tu código aquí: coloca la marca correcta
			document.getElementById("validpassword").innerHTML = '&#x26a0;';
			campo[0].setCustomValidity(
				"Las password deben coincidir");
		}
	});
	
	$("#nombreUsuario").change(function(){
		var url = baseurl +"comprobarDatos.php?user=" + $("#nombreUsuario").val();
       
		$.get(url,usuarioExiste);
  });

  function passwordvalid(password,password2) {
	// tu codigo aqui (devuelve true ó false)

	if(password==password2){
		
		return true;
	}else {
		return false;
	}	
}
	function correoValidoComplu(correo) {
		// tu codigo aqui (devuelve true ó false)
		if(correo.endsWith("@ucm.es")){
			return true;
		}else {
			return false;
		}	
}

	function usuarioExiste(data,status) {
	
		if (data=="disponible"){
			document.getElementById("validUser").innerHTML = '&#x2714;';
		}else {
			document.getElementById("validUser").innerHTML = '&#x26a0;';
		}
	}
})