using System;
namespace LSP
{
	public class AreaCalculator
	{
		public static int CalculateArea(Rectangle r) {
			return r.Width * r.Height;
		}

		public static int CalculateArea(Square s)
		{
			return s.Width * s.Height;
		}
	}
}
