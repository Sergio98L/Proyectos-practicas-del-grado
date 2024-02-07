package es.ucm.tp1.view;

import es.ucm.tp1.logic.Game;


public abstract class View {
	
	protected static final String SPACE = " ";

	protected static final String ROAD_BORDER_PATTERN = "═";

	protected static final String LANE_DELIMITER_PATTERN = "─";

	protected static final int CELL_SIZE = 7;

	protected static final int MARGIN_SIZE = 2;

	protected static final String CRASH_MSG = String.format("Player crashed!%n");

	protected static final String WIN_MSG = String.format("Player wins!%n");

	protected static final String DO_EXIT_MSG = "Player leaves the game";

	protected static final String GAME_OVER_MSG = "[GAME OVER] ";

	protected static final String SUPERCOIN_PRESENT = "Supercoin is present";

	protected static final String DISTANCE_MSG = "Distance: ";

	protected static final String COINS_MSG = "Coins: ";

	protected static final String CYCLE_MSG = "Cycle: ";
	
	protected static final String LEVEL_MSG = "Level: ";

	protected static final String TOTAL_OBSTACLES_MSG = "Total obstacles: ";

	protected static final String TOTAL_COINS_MSG = "Total coins: ";
	
	protected static final String GAME_OBJECTS_MSG = "Game Objects: ";

	protected static final String ELAPSED_TIME_MSG = "Elapsed Time: ";

	protected static final String NEW_RECORD_MSG = "New record!: ";

	protected static final String RECORD_MSG = "Record: ";

	protected static final String SERIALIZE_MSG = "---- ROAD FIGHTER SERIALIZED ----";

	protected static String formatTime(long t) {
		return String.format("%.2f s", t / 1000.0);
	}
	
	protected Game game;
	
	public View(Game game) {
		this.game = game;
	}
	
	public abstract String getInfo();
	public abstract String toString();
	
}
