using System;
namespace DIP
{
	public class BroadcastResult
	{
		public void Broadcast(bool IsHilaryWin) {
			try
			{
				string Message;
				if (IsHilaryWin)
				{
					Message = "Hilary Won.";
				}
				else {
					Message = "Trump Won.";
				}

				if (IsHilaryWin)
				{
					EmailMsg em = new EmailMsg();
					em.ToSender(Message);
				}
				else {
					ScreenMsg sm = new ScreenMsg();
					sm.ToScreen(Message);
				}
			}
			catch (Exception e) {
				throw new DIPException("BroadcastResult Error: " + e.Message);
			}
		}

		public BroadcastResult()
		{
		}
	}
}
