using System;

namespace ShapeFactory
{
	public class ShapeFactory {

		public IShape GetShape(string ShapeType, string Name) {
			if (ShapeType == "Circle")
			{
				return new Circle(Name);
			}
			else if (ShapeType == "Rectangle")
			{
				return new Rectangle(Name);
			}
			else if (ShapeType == "Polygon")
			{
				return new Polygon(Name);
			}
			else {
				return null;
			}
		}
	}

	class MainClass
	{
		public static void Main(string[] args)
		{
			ShapeFactory factory = new ShapeFactory();

			try
			{
				Circle circle1 = (Circle)factory.GetShape("Circle", "Circle1");
				circle1.Radius = 4.0;
				Console.WriteLine("Radius of " + circle1.Name + " is " + circle1.Radius);
				Console.WriteLine("Area of " + circle1.Name + " is " + circle1.Area());
				Console.WriteLine("Circumference of " + circle1.Name + " is " + circle1.Circumference());
				circle1.Draw();

				Console.WriteLine("\n");

				Rectangle rect1 = (Rectangle)factory.GetShape("Rectangle", "Rectangle1");
				rect1.Width = 8.0;
				rect1.Height = 4.0;
				Console.WriteLine("Width of " + rect1.Name + " is " + rect1.Width);
				Console.WriteLine("Height of " + rect1.Name + " is " + rect1.Height);
				Console.WriteLine("Area of " + rect1.Name + " is " + rect1.Area());
				Console.WriteLine("Circumference of " + rect1.Name + " is " + rect1.Circumference());
				rect1.Draw();

				Console.WriteLine("\n");

				Polygon poly1 = (Polygon)factory.GetShape("Polygon", "Polygon3");
				poly1.Radius = 6.0;
				poly1.Sides = 3;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				poly1.Draw();

				Console.WriteLine("\n");

				poly1 = (Polygon)factory.GetShape("Polygon", "Polygon4");
				poly1.Radius = 7.0;
				poly1.Sides = 4;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				poly1.Draw();

				Console.WriteLine("\n");

				poly1 = (Polygon)factory.GetShape("Polygon", "Polygon5");
				poly1.Radius = 8.0;
				poly1.Sides = 5;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				poly1.Draw();

				Console.WriteLine("\n");

				poly1 = (Polygon)factory.GetShape("Polygon", "Polygon6");
				poly1.Radius = 201.5;
				poly1.Sides = 6;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				poly1.Draw();
			}
			catch (Exception ex) {
				Console.WriteLine("Runtime error: ", ex.Message);
			}

			Console.ReadLine();
			Environment.Exit(0);
		}
	}
}
