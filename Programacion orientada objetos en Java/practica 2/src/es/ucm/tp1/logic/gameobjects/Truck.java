package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Truck extends GameObject {

	private static final String Symbol = " ←";
	private static final String Info = "[Truck] moves towards the player";
	private int resistencia;
	
	public Truck(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol;
		this.resistencia =1;
	}

	public static String getInfo() {
		return Info;
	}

	@Override
	public boolean doCollision() {
		// TODO Auto-generated method stub
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
}