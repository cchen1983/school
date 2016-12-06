using System;
namespace ShapeFactory
{
	public class Rectangle : IShape
	{
		private string name;
		private double width;
		private double height;

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

		public double Width
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

		public double Height
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

		public void Draw()
		{
			Console.WriteLine("1. Start from top left pivot");
			Console.WriteLine("2. Draw top edge of length " + width);
			Console.WriteLine("3. Draw right edge of length " + height);
			Console.WriteLine("4. Draw bottom edge of length " + width);
			Console.WriteLine("5. Draw left edge connected back to top left pivot");
		}

		public double Area()
		{
			return width * height;
		}

		public double Circumference()
		{
			return (width + height) * 2;
		}

		public Rectangle(string nm)
		{
			name = nm;
		}
	}
}
