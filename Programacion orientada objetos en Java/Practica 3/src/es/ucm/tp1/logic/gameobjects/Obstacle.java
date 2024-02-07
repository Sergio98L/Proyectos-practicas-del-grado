package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Obstacle extends GameObject {

	private static final String Symbol = "░";
	private static int obstaculosEnTablero;
	private static final String Info = "[Obstacle] hits car";
	private int resistencia;
	
	public Obstacle(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol;
		this.resistencia =1;
	}

	public static String getInfo() {
		return Info;
	}

	public static int getObstaculosEnTablero() {
		return obstaculosEnTablero;
	}

	public static void reset() {
		obstaculosEnTablero = 0;
	}
	
	// La usa GamePrinter:
	public static String getObstacleSymbol() {
		return Symbol;
	}

	@Override
	public boolean doCollision() {
		return false;
	}

	@Override
	public boolean receiveCollision(Player player) {
		player.setDeadPlayer();
		return false;
	}

	@Override
	public void onEnter() {
		obstaculosEnTablero++;

	}

	@Override
	public void update() {
	}

	@Override
	public void onDelete() {
		obstaculosEnTablero--;

	}

	@Override
	public boolean receiveShoot() {
		this.resistencia--;
		if(this.resistencia ==0) {
			this.alive =false;
		}
		return true;
	}

	@Override
	public boolean receiveExplosion() {		
		return this.receiveShoot();
	}

	@Override
	public boolean receiveThunder() {
		this.alive = false;
		return true;
	}

	@Override
	public boolean receiveWave() {
		x++;
		return true;
	}

	@Override
	public boolean receiveRay() {
		this.receiveShoot();
		return true;
	}
}