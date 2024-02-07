package prueba;

public class Jefatura extends Empleado {

	private int empleadosAcargo;
	
		public Jefatura(String nombre, String dni,int sueldo,String departamento) {
			super(nombre,dni,sueldo,departamento);
			empleadosAcargo = 0;
		}
		
		public void mostrarDondeEstoy() {
			System.out.println("Metodo de la clase Jefatura");
		}
		public void jefatura() {
			System.out.println("Solo en clase jefatura");
		}
}
