package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Collider;
import es.ucm.tp1.logic.Game;

public class Player extends GameObject {
	private int monedas;

	private static final String Info = "[Car] the racing car";
	// X son las filas
	// Y son las columnas

	public Player(Game g) {
		super(g, 0, 1);
		this.monedas = 5;
	}

	public static String getInfo() {
		return Info;
	}

	public boolean isInThisPosition(int x, int y) {
		// si esta en la coordenada f,c => true
		boolean encontrado = false;

		if (this.x == x && this.y == y) {
			encontrado = true;
		}
		return encontrado;
	}

	public String toString() {
		String simbolo;
		if(this.alive) {
			simbolo = ">";
		}else {
			simbolo= "@";
		}	
		return simbolo;
	}

	public void setMonedasCero() {
		this.monedas = 0;
	}

	
	public boolean restarMonedas(int monedasPerdidas) {
		boolean monedasSuficientes = false;
		
		if(this.monedas >= monedasPerdidas) {
			this.monedas -= monedasPerdidas;
			monedasSuficientes = true;
		}
		
		return monedasSuficientes;
		
	}

	public void resetPlayerPos() {
		this.x = 0;
		this.y = 1;
	}

	public void movePlayerUp() {
		y--;
	}

	public void movePlayerDown() {
		y++;

	}
	public boolean getAlive() {
		return alive;
	}

	public void setDeadPlayer() {
		alive = false;
	}

	public void getSuperCoin() {
		this.monedas += 1000;
	}
	public int getMonedas() {
		return this.monedas;
	}

	public void addCoin() {
		this.monedas++;
	}

	public void getTurbo() {
		game.getTurbo();
	}
	@Override
	public boolean doCollision() {
		Collider other = game.getObjectInPosition(game.getmovJugador(), y);
		if (other != null) {
		return other.receiveCollision (this);
		}
		return false;
	}

	@Override
	public boolean receiveCollision(Player player) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void onEnter() {
		// TODO Auto-generated method stub

	}

	@Override
	public void update() {
		// TODO Auto-generated method stub

	}

	@Override
	public void onDelete() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean receiveShoot() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean receiveExplosion() {
		// TODO Auto-generated method stub
		return false;
	}

}
