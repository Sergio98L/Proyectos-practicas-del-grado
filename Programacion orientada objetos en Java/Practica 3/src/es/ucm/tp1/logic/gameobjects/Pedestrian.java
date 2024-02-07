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
	
	public String getObjectInfo(int x, int y) // Devuelve la informacion del objeto
	{
		String texto="";
		String direccion = "";
		
		if(bajar) {
			direccion = "Up";
		}else {
			direccion = "Down";
		}
		
		texto += toString() + " ("+this.x+", "+this.y+") " + direccion + "\n";
		return texto;
	}
	@Override
	public void update() {

		if(this.y ==(game.getRoadWidth()-1)) {
			this.bajar = false;
		}else if(this.y == 0) {
			this.bajar = true;
		}
		
		if(this.bajar) {
			y++;
		}else {
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
		this.receiveThunder();
		return true;
	}
}