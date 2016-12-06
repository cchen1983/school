using System;
namespace DIP
{
	public class ScreenMsg
	{
		public void ToScreen(string msg) {
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
