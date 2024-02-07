package excepciones;

public class NumberFormatException extends CommandParseException
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 3356660133887508104L;
	
	public NumberFormatException()
	{ 
		super(); 
	}
	public NumberFormatException(String message)
	{
		super(message); 
	}
	public NumberFormatException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public NumberFormatException(Throwable cause)
	{ 
		super(cause); 
	}
	NumberFormatException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
