<?php
namespace es\ucm\fdi\aw\subastas;

use es\ucm\fdi\aw\Aplicacion;
use es\ucm\fdi\aw\Formulario;


class ListadoCategorias extends Formulario
{
    
    public function __construct() {
        parent::__construct('formObjeto', ['urlRedireccion' => Aplicacion::getInstance()->resuelve('/index.php')]);
    }

   static function desplegableCategorias(){
            $categorias = \es\ucm\fdi\aw\subastas\Categorias::listarCategorias();
            $html = <<<EOF
            <select name="categoria" id="categoria">
            <option value=''>Elige categoria</option>"
    EOF;
        
       
        foreach($categorias as $categoria2) {  
        
        $html .= "<option value='{$categoria2->getId()}'>{$categoria2->getNombre()}</option>";
        }
    $html .=<<<EOF
        
        </select>
        
    EOF;

    return $html;
}
    

    static function menuCategorias($menuvisible){
        $contadorcategorias=0;
        $categorias = \es\ucm\fdi\aw\subastas\Categorias::listarCategorias();
        $subastas= \es\ucm\fdi\aw\subastas\Subasta::listarSubastas("");
        $contenidoPrincipal="";
        $menuvisible=$menuvisible;

        /*foreach($categorias as $categoria2) { */ 
        for($contadorcategorias;$contadorcategorias<$menuvisible;$contadorcategorias++){
        $contenidoPrincipal .=<<<EOS
            <li><a href="/sw/practica3/vistaSubastaObjeto.php?barra=&categoria={$categorias[$contadorcategorias]->getId()}">{$categorias[$contadorcategorias]->getNombre()}</a> </li>
            EOS;
        }
        $contenidoPrincipal .=<<<EOS
            <li class="dropdown">
                <a href="#">Más categorías</a>
                <ul class="dropdown-content">
        EOS;  
        for($contadorcategorias;$contadorcategorias<count($categorias);$contadorcategorias++){
                $contenidoPrincipal .=<<<EOS
                <li><a href="/sw/practica3/vistaSubastaObjeto.php?barra=&categoria={$categorias[$contadorcategorias]->getId()}">{$categorias[$contadorcategorias]->getNombre()}</a> </li>
                EOS;
  }       
  return $contenidoPrincipal;
        
    }
   static function formularioCategorias($categoriasvisibles){
    $categorias = \es\ucm\fdi\aw\subastas\Categorias::listarCategorias();
    $contenidoPrincipal="";
        for($contador=0;$contador<$categoriasvisibles;$contador++) {
            $contenidoPrincipal .=  parent::formulariosvisiblesindex("Categoria-1.jpg","categoria","/sw/practica3/vistaSubastaObjeto.php","GET",$categorias[$contador]->getId(),$categorias[$contador]->getNombre());
        }
        return $contenidoPrincipal;
        ;
    }

     
}