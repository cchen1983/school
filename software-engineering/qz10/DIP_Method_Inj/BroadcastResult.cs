using System;
namespace DIP
{
	public class BroadcastResult
	{
		public void Broadcast(IMsg Msg, String Message) {
			try
			{
				Msg.Broadcast(Message);
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
