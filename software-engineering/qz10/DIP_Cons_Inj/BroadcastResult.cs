using System;
namespace DIP
{
	public class BroadcastResult
	{
		IMsg Msg = null;

		public void Broadcast(String Message) {
			try
			{
				Msg.Broadcast(Message);
			}
			catch (Exception e) {
				throw new DIPException("BroadcastResult Error: " + e.Message);
			}
		}

		public BroadcastResult(IMsg M)
		{
			Msg = M;
		}
	}
}
