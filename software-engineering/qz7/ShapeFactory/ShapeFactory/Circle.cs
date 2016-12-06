using System;
namespace ShapeFactory
{
	public class Circle: IShape
	{
		private string name;
		private double r;

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

		public void Draw() { 
			Console.WriteLine("1. Start from top pivot");
			Console.WriteLine("2. Radius of circle is " + r);
			Console.WriteLine("3. Draw circle in clockwise direction");
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
