package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;

public abstract class GameObject implements Collider {

	protected int x, y;

	protected Game game;

	protected String symbol;

	protected boolean alive;

	public GameObject(Game game, int x, int y) {
		this.x = x;
		this.y = y;
		this.game = game;
		this.alive = true;
	}

	protected String getSymbol() {
		return symbol;
	}

	@Override
	public String toString() {
		if (isAlive()) {
			return getSymbol();
		}

		return "";
	}

	public boolean isInthisPosition(int f, int c) {
		boolean encontrado = false;

		if (this.x == f && this.y == c) {
			encontrado = true;
		}
		return encontrado;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}
	public void addX() {
		this.x++;
	}

	public boolean isAlive() {
		return alive;
	}

	public String getPositionToString(int x, int y) // Devuelve la informacion del objeto
	{
		return toString();
	}

	public abstract void onEnter();

	public abstract void update();

	public abstract void onDelete();

	// TODO add your code

}
