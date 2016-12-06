using System;

namespace ShapeFactorySRP
{
	public class ShapeFactory {

		public IShape GetShape(string ShapeType, string Name) {
			if (ShapeType == "Circle")
			{
				return new Circle(Name);
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
			Drawing dr = new Drawing();

			try
			{
				Circle circle1 = (Circle)factory.GetShape("Circle", "Circle1");
				circle1.Radius = 4.0;
				circle1.PivotX = 100;
				circle1.PivotY = 100;
				circle1.Width = 8;
				circle1.Height = 8;
				Console.WriteLine("Radius of " + circle1.Name + " is " + circle1.Radius);
				Console.WriteLine("Area of " + circle1.Name + " is " + circle1.Area());
				Console.WriteLine("Circumference of " + circle1.Name + " is " + circle1.Circumference());
				dr.Draw(circle1);

				Console.WriteLine("\n");

				Polygon poly1 = (Polygon)factory.GetShape("Polygon", "Polygon3");
				poly1.Radius = 6.0;
				poly1.Sides = 3;
				poly1.PivotX = 100;
				poly1.PivotY = 100;
				poly1.Width = 12;
				poly1.Height = 12;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				dr.Draw(poly1);

				Console.WriteLine("\n");

				poly1 = (Polygon)factory.GetShape("Polygon", "Polygon4");
				poly1.Radius = 7.0;
				poly1.Sides = 4;
				poly1.PivotX = 100;
				poly1.PivotY = 100;
				poly1.Width = 14;
				poly1.Height = 14;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				dr.Draw(poly1);

				Console.WriteLine("\n");

				poly1 = (Polygon)factory.GetShape("Polygon", "Polygon5");
				poly1.Radius = 8.0;
				poly1.Sides = 5;
				poly1.PivotX = 100;
				poly1.PivotY = 100;
				poly1.Width = 16;
				poly1.Height = 16;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				dr.Draw(poly1);

				Console.WriteLine("\n");

				poly1 = (Polygon)factory.GetShape("Polygon", "Polygon6");
				poly1.Radius = 201.5;
				poly1.Sides = 6;
				poly1.PivotX = 100;
				poly1.PivotY = 100;
				poly1.Width = 403;
				poly1.Height = 403;
				Console.WriteLine("Radius of " + poly1.Name + " is " + poly1.Radius);
				Console.WriteLine("Number of sides of " + poly1.Name + " is " + poly1.Sides);
				Console.WriteLine("Area of " + poly1.Name + " is " + poly1.Area());
				Console.WriteLine("Circumference of " + poly1.Name + " is " + poly1.Circumference());
				dr.Draw(poly1);
			}
			catch (Exception ex) {
				Console.WriteLine("Runtime error: ", ex.Message);
			}

			Console.ReadLine();
			Environment.Exit(0);
		}
	}
}
