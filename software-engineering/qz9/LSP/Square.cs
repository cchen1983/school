using System;
namespace LSP
{
	public class Square: Rectangle
	{
		private int height;
		private int width;

		public overide int Height { 
			get {
				return height;
			}

			set {
				height = value;
				width = value;
			}
		}

		public overide int Width
		{
			get
			{
				return width;
			}

			set
			{
				height = value;
				width = value;
			}
		}
	}
}
