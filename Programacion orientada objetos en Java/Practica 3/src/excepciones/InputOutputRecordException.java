package excepciones;

public class InputOutputRecordException extends CommandExecuteException
{
	
	private static final long serialVersionUID = -5828526463614667312L;
	
	public InputOutputRecordException()
	{ 
		super(); 
	}
	public InputOutputRecordException(String message)
	{
		super(message); 
	}
	public InputOutputRecordException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public InputOutputRecordException(Throwable cause)
	{ 
		super(cause); 
	}
	InputOutputRecordException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
