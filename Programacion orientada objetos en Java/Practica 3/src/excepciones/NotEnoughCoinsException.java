package excepciones;

public class NotEnoughCoinsException extends CommandExecuteException
{
	/**
	 * 
	 */
	private static final long serialVersionUID = -2835957304026948200L;

	public NotEnoughCoinsException()
	{ 
		super(); 
	}
	public NotEnoughCoinsException(String message)
	{
		super(message); 
	}
	public NotEnoughCoinsException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public NotEnoughCoinsException(Throwable cause)
	{ 
		super(cause); 
	}
	NotEnoughCoinsException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
