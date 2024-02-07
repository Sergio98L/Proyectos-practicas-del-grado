package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;

public class Wall extends GameObject {

	private static final String Symbol = "░";
	private static final String Symbol2 = "▒";
	private static final String Symbol3 = "█";
	private static final String Info = "[WALL] hard obstacle";
	private int resistencia;

	public Wall(Game g, int f, int c) {
		super(g, f, c);
		this.symbol = Symbol3;
		this.resistencia = 3;
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
		player.setDeadPlayer();
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
		int monedas = 5;
		game.addWallCoins(monedas);

	}
	
	public String getObjectInfo(int x, int y) // Devuelve la informacion del objeto
	{
		String texto="";
		texto += toString() + " ("+this.x+", "+this.y+") " + this.resistencia + "\n";
		return texto;
	}
	@Override
	public boolean receiveShoot() {

		this.resistencia--;

		switch (this.resistencia) {
		case 2:
			this.symbol = Symbol2;
			break;
		case 1:
			this.symbol = Symbol;
			break;
		case 0:
			this.alive = false;
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