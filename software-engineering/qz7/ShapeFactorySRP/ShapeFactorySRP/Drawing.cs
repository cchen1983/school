using System;
using System.Collections.Generic;

namespace ShapeFactorySRP
{
	public class Drawing
	{
		private void DrawCircle(Circle c) { 
			Console.WriteLine("1. Top left pivot: " + c.PivotX + ", " + c.PivotY);
			Console.WriteLine("2. Center of circle is: " + (c.PivotX + c.Radius) + ", " + (c.PivotY + c.Radius));
			Console.WriteLine("3. Start from point: " + (c.PivotX + c.Radius) + ", " + c.PivotY);
			Console.WriteLine("4. Draw circle in clockwise direction");
		}


		private void DrawPolygon(Polygon poly)
		{
			// center point of polygon
			Int32 r = (Int32)poly.Radius;
			Int32 a = poly.PivotX + r;
			Int32 b = poly.PivotY + r;
			var vertX = new List<Int32>();
			var vertY = new List<Int32>();
			for (int i = 1; i <= poly.Sides; i++) {
				//x[k] = a + r * sin(pi / n + k * 2pi / n)
				//y[k] = b - r * cos(pi / n + k * 2pi / n)

				Int32 x = a + (Int32)(r * Math.Sin((Math.PI / poly.Sides) + (i * 2 * Math.PI / poly.Sides)));
				Int32 y = b - (Int32)(r * Math.Cos((Math.PI / poly.Sides) + (i * 2 * Math.PI / poly.Sides)));
				vertX.Add(x);
				vertY.Add(y);
			}

			Console.WriteLine("1. Top left pivot: " + poly.PivotX + ", " + poly.PivotY);
			for (int i = 1; i <= poly.Sides; i++)
			{
				Int32 fromX = vertX[i - 1];
				Int32 fromY = vertY[i - 1];
				int to = i;

				if (to == poly.Sides) {
					to = 0;
				}

				Int32 toX = vertX[to];
				Int32 toY = vertY[to];
				Console.WriteLine((i + 1) + ". Draw a line from: " + fromX + "," + fromY  + " to " + toX + "," + toY + " of length " + poly.EdgeLength());

			}
		}


		public void Draw(IShape Shape)
		{
			Type type = Shape.GetType();

			if (type == typeof(Circle)) {
				DrawCircle((Circle)Shape);
			}
			else if (type == typeof(Polygon)) {
				DrawPolygon((Polygon)Shape);
			}
		}
	}
}
