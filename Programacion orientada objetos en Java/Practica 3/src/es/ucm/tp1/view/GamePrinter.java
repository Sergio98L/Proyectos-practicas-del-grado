package es.ucm.tp1.view;

import es.ucm.tp1.control.Level;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.gameobjects.Coin;
import es.ucm.tp1.logic.gameobjects.Grenade;
//import es.ucm.tp1.logic.gameobjects.Grenade;
import es.ucm.tp1.logic.gameobjects.Obstacle;
import es.ucm.tp1.logic.gameobjects.Pedestrian;
import es.ucm.tp1.logic.gameobjects.SuperCoin;
import es.ucm.tp1.logic.gameobjects.Truck;
import es.ucm.tp1.logic.gameobjects.Turbo;
import es.ucm.tp1.logic.gameobjects.Wall;
//import es.ucm.tp1.logic.gameobjects.Pedestrian;
//import es.ucm.tp1.logic.gameobjects.SuperCoin;
//import es.ucm.tp1.logic.gameobjects.Truck;
//import es.ucm.tp1.logic.gameobjects.Turbo;
//import es.ucm.tp1.logic.gameobjects.Wall;
import es.ucm.tp1.utils.StringUtils;

public class GamePrinter extends View{

	
	private String indentedRoadBorder;

	private String indentedLanesSeparator;

	private String margin;

	public GamePrinter(Game game) {
		super(game);

		margin = StringUtils.repeat(SPACE, MARGIN_SIZE);

		String roadBorder = ROAD_BORDER_PATTERN
				+ StringUtils.repeat(ROAD_BORDER_PATTERN, (CELL_SIZE + 1) * game.getVisibility());
		indentedRoadBorder = String.format("%n%s%s%n", margin, roadBorder);

		String laneDelimiter = StringUtils.repeat(LANE_DELIMITER_PATTERN, CELL_SIZE);
		String lanesSeparator = SPACE + StringUtils.repeat(laneDelimiter + SPACE, game.getVisibility() - 1)
				+ laneDelimiter + SPACE;

		indentedLanesSeparator = String.format("%n%s%s%n", margin, lanesSeparator);
	}

	public String getInfo() {
		StringBuilder buffer = new StringBuilder();
		/* @formatter:off */
		buffer.append(DISTANCE_MSG).append(game.distanceToGoal()).append(StringUtils.LINE_SEPARATOR).append(COINS_MSG)
				.append(game.playerCoins()).append(StringUtils.LINE_SEPARATOR).append(CYCLE_MSG).append(game.getCycle())
				.append(StringUtils.LINE_SEPARATOR).append(TOTAL_OBSTACLES_MSG)
				.append(Obstacle.getObstaculosEnTablero()).append(StringUtils.LINE_SEPARATOR).append(TOTAL_COINS_MSG)
				.append(Coin.getMonedasEnTablero());
		/* @formatter:on */
		if (game.getLevel().hasAdvancedObjects()) {
			if (SuperCoin.hasSuperCoin()) {
				buffer.append(StringUtils.LINE_SEPARATOR).append(SUPERCOIN_PRESENT);
			}
		}

		if (!game.isTestMode()) {
			/* @formatter:off */
			buffer.append(StringUtils.LINE_SEPARATOR).append(ELAPSED_TIME_MSG).append(formatTime(game.elapsedTime()));
			/* @formatter:on */
		}

		return buffer.toString();
	}

	@Override
	public String toString() {
		StringBuilder str = new StringBuilder();

		// Game Status

		str.append(getInfo());

		// Paint game

		str.append(indentedRoadBorder);

		String verticalDelimiter = SPACE;

		for (int y = 0; y < game.getRoadWidth(); y++) {
			str.append(this.margin).append(verticalDelimiter);
			for (int x = 0; x < game.getVisibility(); x++) {
				str.append(StringUtils.centre(game.positionToString(x, y), CELL_SIZE)).append(verticalDelimiter);
			}
			if (y < game.getRoadWidth() - 1) {
				str.append(this.indentedLanesSeparator);
			}
		}
		str.append(this.indentedRoadBorder);

		return str.toString();
	}

	public String endMessage() {

		StringBuilder buffer = new StringBuilder(GAME_OVER_MSG);

		if (game.isUserExit()) {
			return buffer.append(DO_EXIT_MSG).toString();
		}

		if (game.hasArrived()) {
			buffer.append(WIN_MSG);
			if (!game.isTestMode()) {
				if (game.isNewRecord()) {
					buffer.append(NEW_RECORD_MSG).append(formatTime(game.elapsedTime()));
				} else {
					buffer.append(RECORD_MSG).append(formatTime(game.getRecord()));
				}
			}
		} else {
			buffer.append(CRASH_MSG);
		}

		return buffer.toString();
	}

	public static String description(Level level) {
		StringBuilder buffer = new StringBuilder("[Car] the racing car");
		/* @formatter:off */
		buffer.append(StringUtils.LINE_SEPARATOR).append(Coin.getInfo()).append(StringUtils.LINE_SEPARATOR)
				.append(Obstacle.getInfo());
		/* @formatter:on */

		if (level.hasAdvancedObjects()) {
			/* @formatter:off */
			 buffer
			 .append(StringUtils.LINE_SEPARATOR).append(Grenade.getInfo())
			 .append(StringUtils.LINE_SEPARATOR).append(Wall.getInfo())
			 .append(StringUtils.LINE_SEPARATOR).append(Turbo.getInfo())
			 .append(StringUtils.LINE_SEPARATOR).append(SuperCoin.getInfo())
			 .append(StringUtils.LINE_SEPARATOR).append(Truck.getInfo())
			 .append(StringUtils.LINE_SEPARATOR).append(Pedestrian.getInfo())
			 ;
			/* @formatter:on */
		}

		return buffer.toString();
	}
}
