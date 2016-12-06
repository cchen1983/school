using System;
namespace DIP
{
	public class BroadcastResult
	{
		public void Broadcast(bool IsHilaryWin, String Message) {
			try
			{
				IMsg msg;
				if (IsHilaryWin)
				{
					msg = new EmailMsg();
				}
				else {
					msg = new ScreenMsg();
				}

				msg.Broadcast(Message);
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
