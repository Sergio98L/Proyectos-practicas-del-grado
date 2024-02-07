package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Tank extends GameObject {

	private static final String Symbol = "TK";
	private static final String Info = "[Tank] moves towards the player";
	private int resistencia;

	public Tank(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol;
		this.resistencia = 10;
	}

	public static String getInfo() {
		return Info;
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

	}

	@Override
	public void update() {
		this.x--;

	}

	@Override
	public void onDelete() {

	}

	@Override
	public boolean receiveShoot() {	
		return false;
	}

	@Override
	public boolean receiveExplosion() {
		return false;
	}

	@Override
	public boolean receiveThunder() {
		return false;
	}

	@Override
	public boolean receiveWave() {
		x++;
		return true;
	}

	@Override
	public boolean receiveRay() {
		this.alive= false;
		return true;
	}
}