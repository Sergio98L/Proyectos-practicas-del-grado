package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Turbo extends GameObject {

	private static final String Symbol = ">>>";
	private static final String Info = "[TURBO] pushes the car: 3 columns";
	private static final int posicionesAvanzadas = 3;

	
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
		return false;
	}

	@Override
	public boolean receiveCollision(Player player) {
		
		player.getTurbo(posicionesAvanzadas);
		return false;
	}

	@Override
	public void onEnter() {
	}

	@Override
	public void update() {
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
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean receiveWave() {
		x++;
		return true;
	}

	@Override
	public boolean receiveRay() {
		// TODO Auto-generated method stub
		return false;
	}
}