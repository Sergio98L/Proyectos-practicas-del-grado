package es.ucm.tp1.logic.gameobjects;

import java.util.ArrayList;
import java.util.List;
import es.ucm.tp1.logic.gameobjects.GameObject;
import es.ucm.tp1.logic.Collider;

public class GameObjectContainer {

	private List<GameObject> gameObjects;

	public GameObjectContainer() {
		gameObjects = new ArrayList<>();
	}

	public void add(GameObject object) // Añadir el objeto en la lista
	{
		gameObjects.add(object);
		object.onEnter();// El objeto entra en juego
	}

	public Collider getObjectInPosition(int x, int y, Collider interfaz) {

		boolean encontrado = false;
		int i = 0;
		while (!encontrado && i < gameObjects.size()) {
			if (gameObjects.get(i).isInthisPosition(x, y)) {
				interfaz = gameObjects.get(i);
				encontrado = true;
			}
			i++;
		}

		return interfaz;
	}

	public boolean isPositionEmpty(int x, int y) // Mira en x e y si hay algo
	{
		boolean vacio = true;
		int i = 0;
		while (vacio && i < gameObjects.size()) {
			if (gameObjects.get(i).isInthisPosition(x, y)) {
				vacio = false;
			}
			i++;
		}
		return vacio;
	}

	public String getPositionToString(int x, int y) {
		String texto = "";

		int i = 0;
		while (i < gameObjects.size()) {
			if (gameObjects.get(i).getX() == x && gameObjects.get(i).getY() == y) {
				texto += gameObjects.get(i).getPositionToString(x, y);

			}
			i++;
		}

		return texto;
	}
	
	public String getObjectInfo(int x, int y) {
		String texto = "";
		
		int i = 0;
		while (i < gameObjects.size()) {
			if (gameObjects.get(i).getX() == x && gameObjects.get(i).getY() == y) {
				texto += gameObjects.get(i).getObjectInfo(x, y);

			}
			i++;
		}
		
		return texto;
	}
	public void removeDead() // Elimina los muertos del tablero
	{
		for (int i = 0; i < gameObjects.size(); i++) {
			if (!gameObjects.get(i).isAlive()) {

				gameObjects.get(i).onDelete();
				gameObjects.remove(i);
				i--;// para que no se salte ninguna posicion ya que si borra un objeto todos los
					// objetos por encima suya bajan una posicion
			}
		}
	}

	public void updateObjects() {
		for (int i = 0; i < gameObjects.size(); i++) {
			gameObjects.get(i).update();
		}
	}

	public void clearObjects(int visibilidad, int filas, int posPlayer) {
		List<GameObject> arrayAux = new ArrayList<>();
		boolean enParteVisible = false;

		for (int i = 0; i < gameObjects.size(); i++) {
			enParteVisible = false;
			//for para recorrer la parte visible
			for (int x = posPlayer; x < visibilidad + posPlayer; x++) {
				for (int y = 0; y < filas; y++) {
					if (x == gameObjects.get(i).getX() && y == gameObjects.get(i).getY()) {
						gameObjects.get(i).onDelete();
						enParteVisible = true;
					}
				}
			}
			// si el objeto no esta en la parte visible se añade al arrayList aux
			if (!enParteVisible) {
				arrayAux.add(gameObjects.get(i));
			}
		}
		this.gameObjects = arrayAux;

	}

	public void borrarUltColumVisible(int x) {
		for (int i = 0; i < gameObjects.size(); i++) {
			if (x == gameObjects.get(i).getX()) {
				gameObjects.get(i).onDelete();
				gameObjects.remove(i);
				i--;
			}
		}

	}
}
