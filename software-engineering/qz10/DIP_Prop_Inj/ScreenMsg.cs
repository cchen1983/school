using System;
namespace DIP
{
	public class ScreenMsg:IMsg
	{
		public void Broadcast(String msg) {
			try
			{
				Console.WriteLine("ToScreen: " + msg);
			}
			catch (Exception e) {
				throw new DIPException("ScreenMsg Error: " + e.Message);
			}
		}

		public ScreenMsg()
		{
		}
	}
}
