package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import instantactions.ExplosionAction;

public class Grenade extends GameObject {

	private static final String Symbol = "ð";
	private static final String Info = "[GRENADE] Explodes in 3 cycles, harming everyone around";
	private static final int Coste = 3;
	
	private int contador=4;
	
	public Grenade(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol + "[" + contador +"]";
	}

	public static String getInfo() {
		return Info;
	}
	public static int getCoste() {
		return Coste;
	}
	// La usa GamePrinter:
	public static String getObstacleSymbol() {
		return Symbol;
	}

	@Override
	public boolean doCollision() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean receiveCollision(Player player) {
		return false;
	}

	@Override
	public void onEnter() {
		

	}

	@Override
	public void update() {
		
		this.contador--;
		this.symbol = Symbol + "[" + contador +"]";
		if(this.contador ==0) {
			this.alive =false;
		}

	}

	@Override
	public void onDelete() {
		game.execute(new ExplosionAction(this.x,this.y));

	}

	@Override
	public boolean receiveShoot() {
		return false;
	}

	@Override
	public boolean receiveExplosion() {
		// TODO Auto-generated method stub
		return false;
	}
}