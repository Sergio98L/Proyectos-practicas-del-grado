package prueba;

public class Empleado implements pruebaInter {

	public static int num_Empleados;
	private String nombre;
	private String dni;
	private int sueldo;
	private String departamento;
	
	public Empleado(String nombre, String dni,int sueldo,String departamento){
		num_Empleados++;
		this.nombre = nombre;
		this.dni = dni;
		this.sueldo = sueldo;
		this.departamento = departamento;
	}
	
	public void mostrarDondeEstoy() {
		System.out.println("Metodo de la clase Empleado");
	}
}
