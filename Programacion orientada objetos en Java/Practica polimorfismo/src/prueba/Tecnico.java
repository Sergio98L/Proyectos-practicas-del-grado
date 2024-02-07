package prueba;

public class Tecnico extends Jefatura {

	public Tecnico(String nombre, String dni, int sueldo, String departamento) {
		super(nombre, dni, sueldo, departamento);
		
	}
	public void mostrarDondeEstoy() {
		System.out.println("Metodo de la clase tecnico");
	}
}
