package es.ucm.tp1.view;

import es.ucm.tp1.utils.StringUtils;
import es.ucm.tp1.logic.Game;

public class GameSerializer extends View {

	
	public GameSerializer(Game game) {
		super(game);
	}
	
	
	public String getInfo() {
		StringBuilder buffer = new StringBuilder();
		/* @formatter:off */
		buffer.append(SERIALIZE_MSG).append(StringUtils.LINE_SEPARATOR).append(LEVEL_MSG)
				.append(game.getLevel()).append(StringUtils.LINE_SEPARATOR).append(CYCLE_MSG).append(game.getCycle())
				.append(StringUtils.LINE_SEPARATOR).append(COINS_MSG)
				.append(game.getPlayerCoins()).append(StringUtils.LINE_SEPARATOR).append(ELAPSED_TIME_MSG)
				.append(formatTime(game.elapsedTime())).append(StringUtils.LINE_SEPARATOR).append(GAME_OBJECTS_MSG).append(StringUtils.LINE_SEPARATOR);
		/* @formatter:on */
		
		return buffer.toString();
	}
	public String toString() {
		StringBuilder str = new StringBuilder();

		// Game Status

		str.append(getInfo());

		// Paint game

		for (int x = 0; x < game.getRoadLong(); x++) {
			for (int y = 0; y < game.getRoadWidth(); y++) {			
				str.append(game.getObjectInfo(x, y));
			}			
		}
		return str.toString();
	}
}
