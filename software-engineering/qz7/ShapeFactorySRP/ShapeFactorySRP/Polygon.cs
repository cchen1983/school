using System;
namespace ShapeFactorySRP
{
	public class Polygon: IShape
	{
		private string name;
		private int sides;
		private double r;

		private Int32 width;
		private Int32 height;
		private Int32 pX;
		private Int32 pY;

		public Int32 Width { 
			get
			{
				return width;
			}

			set 
			{
				width = value;			
			}
		}

		public Int32 Height
		{
			get
			{
				return height;
			}

			set
			{
				height = value;
			}
		}

		public Int32 PivotX
		{
			get
			{
				return pX;
			}

			set
			{
				pX = value;
			}
		}

		public Int32 PivotY
		{
			get
			{
				return pY;
			}

			set
			{
				pY = value;
			}
		}

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
