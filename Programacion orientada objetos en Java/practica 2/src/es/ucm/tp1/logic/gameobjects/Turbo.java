package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Turbo extends GameObject {

	private static final String Symbol = ">>>";

	
	//private static int obstaculosEnTablero;
	private static final String Info = "[TURBO] pushes the car: 3 columns";

	
	public Turbo(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol;
	}

	public static String getInfo() {
		return Info;
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
		player.getTurbo();
		return false;
	}

	@Override
	public void onEnter() {
		

	}

	@Override
	public void update() {
		// TODO Auto-generated method stub

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
		// TODO Auto-generated method stub
		return false;
	}
}