using System;
namespace ShapeFactorySRP
{
	public class Circle: IShape
	{
		private string name;
		private double r;

		private Int32 width;
		private Int32 height;
		private Int32 pX;
		private Int32 pY;

		public Int32 Width
		{
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

		public string Name { 
			get {
				return name;
			}

			set
			{
				name = value;
			}		
		}

		public double Radius { 
			get {
				return r;
			}

			set {
				r = value;
			}
		}

		public double Area() {
			return Math.PI * Math.Pow(r, 2);
		}

		public double Circumference() {
			return 2 * Math.PI * r;
		}

		public Circle(string nm) {
			name = nm;
		}
	}
}
