package excepciones;

public class ShowRecordException extends CommandExecuteException
{
	
	private static final long serialVersionUID = -5882526463614667312L;
	
	public ShowRecordException()
	{ 
		super(); 
	}
	public ShowRecordException(String message)
	{
		super(message); 
	}
	public ShowRecordException(String message, Throwable cause)
	{
		super(message, cause);
	}
	public ShowRecordException(Throwable cause)
	{ 
		super(cause); 
	}
	ShowRecordException(String message, Throwable cause, boolean enableSuppression, boolean writeableStackTrace)
	{
		super(message, cause, enableSuppression, writeableStackTrace);
	}
}
