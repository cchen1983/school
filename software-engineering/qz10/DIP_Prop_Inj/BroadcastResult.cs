using System;
namespace DIP
{
	public class BroadcastResult
	{
		private IMsg msg = null;

		public IMsg Msg { 
			get {
				return msg;
			}

			set {
				msg = value;
			}
		}

		public void Broadcast(String Message) {
			try
			{
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
