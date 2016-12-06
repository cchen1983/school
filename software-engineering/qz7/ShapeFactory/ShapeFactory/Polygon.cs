using System;
namespace ShapeFactory
{
	public class Polygon: IShape
	{
		private string name;
		private int sides;
		private double r;

		public string Name
		{
			get
			{
				return name;
			}

			set
			{
				name = value;
			}
		}

		public int Sides
		{
			get
			{
				return sides;
			}

			set
			{
				sides = value;
			}
		}

		public double Radius
		{
			get
			{
				return r;
			}

			set
			{
				r = value;
			}
		}

		public void Draw()
		{
			Console.WriteLine("1. Start from top left pivot");
			Console.WriteLine("2. The circumradius is " + r);
			for (int i = 1; i <= sides; i++) {
				Console.WriteLine( (i + 2) + ". Draw line of edge number " + i);
			}
		}

		public double Area()
		{
			double angle = Math.PI * (360 / sides) / 180.0;
			return Math.Pow(r, 2) * sides * Math.Sin(angle) / 2;
		}

		public double EdgeLength()
		{
			double angle = Math.PI * (180 / sides) / 180.0;
			return 2 * r * Math.Sin(angle);
		}

		public double Circumference()
		{
			return EdgeLength() * sides;
		}

		public Polygon(string nm)
		{
			name = nm;
		}
	}
}
