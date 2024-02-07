package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Pedestrian extends GameObject {

	private static final String Symbol = "☺";
	private static final String Info = "[PEDESTRIAN] person crossing the road up and down";
	private int resistencia;
	private boolean bajar;
	
	public Pedestrian(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol;
		this.resistencia =1;
		bajar= false;
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
		player.setMonedasCero();
		return false;
	}

	@Override
	public void onEnter() {

	}

	@Override
	public void update() {

		if(this.y ==2) {
			this.bajar = false;
			y--;
		}else if(this.y ==0) {
			this.bajar = true;
			y++;
		}else if(this.y ==1 && bajar) {
			y++;
		}
		else if(this.y ==1 && !bajar) {
			y--;
		}

	}

	@Override
	public void onDelete() {
		

	}

	@Override
	public boolean receiveShoot() {
		game.resetMonedasPlayer();
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