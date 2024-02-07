package es.ucm.tp1.logic;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.Random;
import es.ucm.tp1.control.Level;
import es.ucm.tp1.logic.gameobjects.GameObject;
import es.ucm.tp1.logic.gameobjects.GameObjectContainer;
import es.ucm.tp1.logic.gameobjects.GameObjectGenerator;
import es.ucm.tp1.logic.gameobjects.Player;
import es.ucm.tp1.logic.gameobjects.Record;
import es.ucm.tp1.view.GameSerializer;
import excepciones.NotEnoughCoinsException;
import excepciones.ShowRecordException;
import excepciones.UnvalidCheatNumberException;
import excepciones.InputOutputRecordException;
import excepciones.InvalidLevelException;
import excepciones.InvalidPositionException;

public class Game {

	private int cycle;
	private Level level;
	private Long seed;
	private Player player;
	private GameObjectContainer objectsContainer;
	private Random rand;
	private boolean endgame;
	private boolean testmode;
	private double tiempoInicial;
	private double tiempoTranscurrido;
	private Record record;

	public Game(Long seed, Level level) {
		this.seed = seed;
		this.level = level;
		this.init();
				
		try {
			this.cargarRecord();
		}catch(InputOutputRecordException x) {
			System.out.println(x.getMessage());
			this.endgame = true;
			
		}
	}

	public void init() {
		player = new Player(this);
		objectsContainer = new GameObjectContainer();
		rand = new Random(seed);
		GameObjectGenerator.generateGameObjects(this, level);
		this.cycle = 0;
		this.tiempoTranscurrido = 0;
		this.testmode = false;
		player.resetPlayerPos();
		record = new Record(this);

	}

	
	public int getVisibility() {
		return this.level.getVisibility();
	}

	public int getRoadLength() {
		return this.level.getDimX();
	}

	public int getRandomLane() {
		return rand.nextInt(level.getDimY());
	}

	public int getRandomCol() {
		return rand.nextInt(level.getVisibility() - 1);
	}

	public void setSeed(long numero) {
		this.seed = numero;
	}

	public void setLevel(String nivel) throws InvalidLevelException {
		Level nuevoNivel = Level.valueOfIgnoreCase(nivel);
		if(nuevoNivel == null) {
			throw new InvalidLevelException("[ERROR] Level must be one of: " + Level.all(", "));
		}
		this.level = nuevoNivel;

	}

	public void tryToAddObject(GameObject objeto, double objectFrequency) {

		if (rand.nextDouble() < objectFrequency && objectsContainer.isPositionEmpty(objeto.getX(), objeto.getY())) {
			this.objectsContainer.add(objeto);
		}
	}

	public void toggleTest() {
		this.testmode = true;
	}
	
	public void checkEnd() // Comprueba si ha llegado al final
	{

		if (level.getDimX() - player.getX() == 0) {
			this.endgame = true;
			System.out.print("\n[GAME OVER] Player wins\n");
			System.out.print("\nNew record!: " + Math.round((this.tiempoTranscurrido / 1000) * 100.0) / 100.0 + " s");	

		} else if (!player.isAlive()) {

			this.endgame = true;
			System.out.print("\n[GAME OVER] Player crashed!\n");
		}

	}

	public boolean getEndGame() {
		return endgame;
	}

	public void exit() // Sale del juego
	{
		endgame = true;
		System.out.println("[GAME OVER] Player leaves the game");
	}

	public boolean movePlayerUp() {

		boolean puedeMover = false;

		if (player.getY() > 0) {
			player.minusY();
			puedeMover = true;
		}

		return puedeMover;
	}

	public boolean movePlayerDown() {

		boolean puedeMover = false;

		if (player.getY() < (level.getDimY() - 1)) {
			player.addY();
			puedeMover = true;
		}

		return puedeMover;
	}

	public void updateGame() // Actualizar el juego
	{
		this.objectsContainer.updateObjects();
		GameObjectGenerator.generateRuntimeObjects(this);
		this.cycle++;

		if (this.cycle == 1) {// cuando realiza un movimiento el jugador empieza el contador de tiempo
			this.tiempoInicial = System.currentTimeMillis();
			
		} else {
			this.tiempoTranscurrido = System.currentTimeMillis() - this.tiempoInicial;
		}
		this.checkDeadObjects();
		this.checkEnd();

	}

	public void comprobarColision() {
		player.doCollision();
	}

	public Collider getObjectInPosition(int x, int y) {

		Collider interfaz = null;

		interfaz = objectsContainer.getObjectInPosition(x, y, interfaz);

		return interfaz;
	}

	public void checkDeadObjects() // Eliminar objetos muertos el juego
	{
		objectsContainer.removeDead();
	}

	public int getPlayerCoins() {
		return player.getMonedas();
	}
	

	public boolean restarMonedasPlayer(int monedasPerdidas) throws NotEnoughCoinsException {	
		return player.restarMonedas(monedasPerdidas);			
	}

	public void addWallCoins(int monedas) {
		player.addCoin(monedas);
	}

	public int getPlayerY() {
		return player.getY();
	}

	public int get() {
		return player.getY();
	}

	public void addGrenade(GameObject grenade) throws InvalidPositionException {

		int parteVisible = this.getVisibility() + player.getX();

		if (grenade.getX() >= 0 && grenade.getX() < parteVisible && grenade.getY() < level.getDimY()) { // comprobar que
																										// este en la parte visible
			if (objectsContainer.isPositionEmpty(grenade.getX(), grenade.getY())) {
				this.forceAddObject(grenade);
			} else {
				throw new InvalidPositionException("[ERROR]: You cant put a grenade on another object");			
			}
		} else {
			throw new InvalidPositionException ("[ERROR]: You cant put a grenade outside the board");
			}
	}

	public void resetMonedasPlayer() {

		this.player.setMonedasCero();
	}

	// Execute InstantAction:
	public void execute(InstantAction instantAction) {
		instantAction.execute(this);
	}

	// Metodos para cheat
	public void clearCarretera() {
		this.objectsContainer.clearObjects(this.getVisibility(), this.getRoadWidth(), player.getX());

	}

	public void borrarUltColumVisible() {
		this.objectsContainer.borrarUltColumVisible((player.getX() + (this.getVisibility() - 1)));
	}

	public void cheatGame(int cheat) throws UnvalidCheatNumberException {	
		GameObjectGenerator.forceAdvanceObject(this, cheat, (player.getX() + (this.getVisibility() - 1)));
		}

	public void forceAddObject(GameObject o) {
		this.objectsContainer.add(o);
	}
	
	public String serialize() //Execute del Serialize
	{
		String serialized;
		GameSerializer serializer = new GameSerializer(this);
		serialized = serializer.toString();
		return serialized;
	}
	public void save(BufferedWriter salida) throws IOException  //Execute del save
	{
		salida.write(this.serialize());
	}
	
	public void cargarRecord() throws InputOutputRecordException {
		this.record.cargarRecord();
	}
	public void guardarRecord() throws InputOutputRecordException {
		this.record.guardarRecord();
	}
	
	public void showRecord() throws ShowRecordException  {

		long record = this.record.getRecord();
		System.out.println(this.level+" Record is " + Math.round((record/1000.0)* 100.0) / 100.0 +" s");
	}
	
	//Metodo para el GameSerializer:
	public String getObjectInfo(int x, int y) {
		String info = "";
		if(player.isInthisPosition(x, y)) {
			info = player.getAllInfo();
		}
		info += objectsContainer.getObjectInfo(x, y);		
		return info;
	}
	// Metodos para el GamePrinter:

	public String positionToString(int x, int y) {
		String symbolo = "";

		if (player.isInthisPosition(x + player.getX(), y)) {
			symbolo = player.toString();
		}

		symbolo += objectsContainer.getPositionToString(x + player.getX(), y);

		if (x + player.getX() == level.getDimX()) {
			symbolo += "¦";
		}
		return symbolo;
	}
	

	public String distanceToGoal() {
		return "" + (level.getDimX() - player.getX());
	}
	
	public int playerCoins() {
		return player.getMonedas();
	}

	public int getCycle() {
		return this.cycle;
	}

	public Level getLevel() {
		return this.level;
	}

	public boolean isTestMode() {
		return this.testmode;
	}

	public long elapsedTime() {
		return (long) this.tiempoTranscurrido;
	}

	public int getRoadWidth() {
		return this.level.getDimY();
	}
	
	public int getRoadLong() {
		return this.level.getDimX();
	}

	public boolean isUserExit() {
		return this.endgame;
	}

	public boolean hasArrived() {
		boolean hasArrived = false;

		if (level.getDimX() - player.getX() == 0) {
			hasArrived = true;
		}

		return hasArrived;
	}

	public boolean isNewRecord() {
		return false;
	}

	public int getColJugador() {
		return player.getX();
	}

	public void addColJugador() {
		player.addX();
	}

	public void getTurbo(int posicionesAvanzadas) {
		player.addX(posicionesAvanzadas);
	}

	public long getRecord() {
		
		long record = 0;
		try {
			record= this.record.getRecord();
		} catch (ShowRecordException e) {
			System.out.println(e.getMessage());
		}
		return record;
	}

}
