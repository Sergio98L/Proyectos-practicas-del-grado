package prueba;

import java.util.ArrayList;

public class Empresa {
	
	private ArrayList <Empleado> miArrayEmpleado;
	public Empresa() {
		miArrayEmpleado=new ArrayList<>();
	}
	
	public void iniciarPrograma() {
		
		String nombre= "pepe";
		String dni ="6372819A";
		int sueldo = 200;
		String departamento = "RRHH";
		pruebaInter interfaz = null;
		
		Empleado jefatura1 = new Jefatura(nombre, dni, sueldo, departamento);
		Empleado tecnico2 = new Tecnico(nombre, dni, sueldo, departamento);
		Empleado empleado3 = new Empleado(nombre, dni, sueldo, departamento);
		
		this.add(jefatura1);
		this.add(tecnico2);
		this.add(empleado3);
		
		interfaz =  this.recorrerArrayList();
		interfaz.mostrarDondeEstoy();
	}
	public void add(Empleado empleado) {	
		miArrayEmpleado.add(empleado);		
	}
	public pruebaInter recorrerArrayList() {	
		pruebaInter interfaz;
		interfaz = miArrayEmpleado.get(0);
		return interfaz;
		
	}
}
