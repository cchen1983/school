using System;
namespace DIP
{
	public class DIPException: Exception
	{
		public DIPException()
		{
		}

		public DIPException(string msg): base(msg)
		{
		}

		public DIPException(string msg, Exception inner):base(msg, inner)
		{
		}
	}
}
