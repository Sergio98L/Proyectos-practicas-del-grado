<?php
namespace es\ucm\fdi\aw\usuarios;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;

class FormularioRegistro extends Formulario
{
    public function __construct() {
        parent::__construct('formRegistro', ['urlRedireccion' => Aplicacion::getInstance()->resuelve('/index.php')]);
    }
    
    protected function generaCamposFormulario(&$datos)
    {
        $nombreUsuario = $datos['nombreUsuario'] ?? '';
        $nombre = $datos['nombre'] ?? '';
        $email=$datos['email'] ?? '';
      

        // Se generan los mensajes de error si existen.
        $htmlErroresGlobales = self::generaListaErroresGlobales($this->errores);
        $erroresCampos = self::generaErroresCampos(['rolUsuario','nombreUsuario', 'nombre','email', 'password', 'password2'], $this->errores, 'span', array('class' => 'error'));

        $html = <<<EOF
        $htmlErroresGlobales
        <div class="center">
        <h1>Crea una cuenta</h1>    

        <div class="radio-buttons">
            <label for="rolParticular">Particular:</label>
            <input id="rolParticular" type="radio" name="rolUsuario" value="2" />
            {$erroresCampos['rolUsuario']}
            <label for="rolEmpresa">Empresa:</label>
            <input id="rolEmpresa" type="radio" name="rolUsuario" value="3" />
            {$erroresCampos['rolUsuario']}
        </div>   
            
            <div class="txt_field">
                <input id="nombreUsuario" type="text"  placeholder="Nombre usuario" name="nombreUsuario" value="$nombreUsuario" /> <span id="validUser"></span>
                {$erroresCampos['nombreUsuario']}
            </div>
            <div class="txt_field">
              
                <input id="nombre" type="text" name="nombre" placeholder="Nombre" value="$nombre" />
                {$erroresCampos['nombre']}
            </div>
            <div class="txt_field">
                <input id="email" type="text" name="email" placeholder="Email" value="$email" /> <span id="validEmail"></span>
                {$erroresCampos['email']}
            </div>

            <div class="txt_field">
                <input id="password" type="password" placeholder="Password" name="password" />
                {$erroresCampos['password']}
            </div>
            <div class="txt_field">
                <input id="password2" type="password" placeholder="Reintroduce el password" name="password2"> <span id="validpassword"></span></input> 
                {$erroresCampos['password2']}
            </div>
            <div>
                <button type="submit" name="registro">Registrar</button>
            </div>
        </div>
        EOF;
        return $html;
    }
    

    protected function procesaFormulario(&$datos)
    {
        $this->errores = [];

        $rolUsuario = trim($datos['rolUsuario'] ?? '');
       

        $nombreUsuario = trim($datos['nombreUsuario'] ?? '');
        $nombreUsuario = filter_var($nombreUsuario, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $nombreUsuario || mb_strlen($nombreUsuario) < 5) {
            $this->errores['nombreUsuario'] = 'El nombre de usuario tiene que tener una longitud de al menos 5 caracteres.';
        }

        $nombre = trim($datos['nombre'] ?? '');
        $nombre = filter_var($nombre, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $nombre || mb_strlen($nombre) < 5) {
            $this->errores['nombre'] = 'El nombre tiene que tener una longitud de al menos 5 caracteres.';
        }
        $email = trim($datos['email'] ?? '');
        $email = filter_var($email, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $email || mb_strlen($email) < 5) {
            $this->errores['email'] = 'El email tiene que tener una longitud de al menos 5 caracteres.';
        }
        $password = trim($datos['password'] ?? '');
        $password = filter_var($password, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $password || mb_strlen($password) < 5 ) {
            $this->errores['password'] = 'El password tiene que tener una longitud de al menos 5 caracteres.';
        }

        $password2 = trim($datos['password2'] ?? '');
        $password2 = filter_var($password2, FILTER_SANITIZE_FULL_SPECIAL_CHARS);
        if ( ! $password2 || $password != $password2 ) {
            $this->errores['password2'] = 'Los passwords deben coincidir';
        }

        if (count($this->errores) === 0) {
            $usuario = Usuario::buscaUsuario($nombreUsuario);
	
            if ($usuario) {
                $this->errores[] = "El usuario ya existe";
            } else {
                $usuario = Usuario::crea($nombreUsuario, $password, $nombre,$email, $rolUsuario);
                $app = Aplicacion::getInstance();
                $app->login($usuario);
            }
        }
    }
}