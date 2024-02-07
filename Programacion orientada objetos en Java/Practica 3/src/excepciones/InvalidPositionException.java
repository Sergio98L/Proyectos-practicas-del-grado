package excepciones;

public class InvalidPositionException extends CommandExecuteException
{
	/**
	 * 
	 */
	private static final long serialVersionUID = -5828526463614667312L;

	public InvalidPositionException()
	{ 
		super(); 
	}
	public InvalidPositionException(String message)
	{
		super(message); 
	}
	public InvalidPositionException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public InvalidPositionException(Throwable cause)
	{ 
		super(cause); 
	}
	InvalidPositionException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
