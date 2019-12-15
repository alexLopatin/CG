using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace lab1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public string x1
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[0].X = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }
        public string y1
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[0].Y = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string x2
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[1].X = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string y2
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[1].Y = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string x3
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[2].X = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string y3
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[2].Y = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string x4
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[3].X = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string y4
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[3].Y = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string x5
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[4].X = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        public string y5
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (double.TryParse(value, out i))
                {
                    points[4].Y = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }

        double ToScreenY(double y)
        {
            return viewport.ActualHeight / 2 - y * 80 / coordStep;
        }
        double ToScreenX(double x)
        {
            return viewport.ActualWidth / 2 + x * 80 / coordStep;
        }
        Point[] points;
        double Lagrange(double x)
        {
            double res = 0;
            for (int i = 0; i < points.Count(); i++)
            {
                double l = points[i].Y;
                for (int j = 0; j < points.Count(); j++)
                {
                    if (j == i)
                        continue;
                    l *= (x - points[j].X) / (points[i].X - points[j].X);
                }
                res += l;
            }
            return res;
        }

        double FindMaxY()
        {
            return points.Max(p => Math.Abs(p.Y));
        }
        double FindMaxX()
        {
            return points.Max(p => Math.Abs(p.X));
        }
        void DrawCurve()
        {
            int stepCount = 1000;
            double leftX = -((viewport.ActualWidth / 2 - 20) / 80) * coordStep;
            double x = -leftX;
            for (int i = 0; i < stepCount; i++)
            {
                Line l = new Line();
                l.X1 = ToScreenX(x);
                if (Double.IsNaN(Lagrange(x)) || Double.IsInfinity(Lagrange(x)))
                    l.Y1 = 0;
                else
                    l.Y1 = ToScreenY(Lagrange(x));
                x += leftX*2 / stepCount;
                l.X2 = ToScreenX(x);
                if (Double.IsNaN(Lagrange(x)) || Double.IsInfinity(Lagrange(x)))
                    l.Y2 = 0;
                else
                    l.Y2 = ToScreenY(Lagrange(x));
                l.Stroke = Brushes.ForestGreen;
                viewport.Children.Add(l);

            }
        }
        double coordStep = 1;
        int pow = 0;
        void DrawCoords()
        {
            {
                Line l = new Line();
                l.X1 = viewport.ActualWidth / 2;
                l.Y1 = 0;
                l.X2 = viewport.ActualWidth / 2;
                l.Y2 = viewport.ActualHeight;
                l.Stroke = Brushes.Black;
                viewport.Children.Add(l);

                l = new Line();
                l.X1 = 0;
                l.Y1 = viewport.ActualHeight / 2;
                l.X2 = viewport.ActualWidth;
                l.Y2 = viewport.ActualHeight / 2;
                l.Stroke = Brushes.Black;
                viewport.Children.Add(l);


                l = new Line();
                l.X1 = viewport.ActualWidth - 10;
                l.Y1 = viewport.ActualHeight / 2 - 10;
                l.X2 = viewport.ActualWidth;
                l.Y2 = viewport.ActualHeight / 2;
                l.Stroke = Brushes.Black;
                viewport.Children.Add(l);

                l = new Line();
                l.X1 = viewport.ActualWidth - 10;
                l.Y1 = viewport.ActualHeight / 2 + 10;
                l.X2 = viewport.ActualWidth;
                l.Y2 = viewport.ActualHeight / 2;
                l.Stroke = Brushes.Black;
                viewport.Children.Add(l);

                l = new Line();
                l.X1 = viewport.ActualWidth / 2 - 10;
                l.Y1 = 10;
                l.X2 = viewport.ActualWidth / 2;
                l.Y2 = 0;
                l.Stroke = Brushes.Black;
                viewport.Children.Add(l);
                l = new Line();
                l.X1 = viewport.ActualWidth / 2 + 10;
                l.Y1 = 10;
                l.X2 = viewport.ActualWidth / 2;
                l.Y2 = 0;
                l.Stroke = Brushes.Black;
                viewport.Children.Add(l);
            }
            double curX = 0;
            double step = 80;
            double cur = 0;
            coordStep = 1;
            double m = Math.Max( FindMaxY(), FindMaxX());
            double p = Math.Log10(m);
            pow = (int)Math.Floor(Math.Log10(m));
            if (pow > 0)
                pow = 0;
            coordStep *= Math.Pow(10, pow);
            double rightX = ((viewport.ActualWidth / 2 - 20) / step) * coordStep;
            double topY = ((viewport.ActualHeight / 2 - 20) / step) * coordStep;
            int j = 0;
            while (rightX < m || topY < m)
            {
                if (j % 2 == 0)
                    coordStep *= 2;
                else
                    coordStep *= 5;
                j++;
                rightX = ((viewport.ActualWidth / 2 - 20) / step) * coordStep;
                topY = ((viewport.ActualHeight / 2 - 20) / step) * coordStep;
            }
            //double stepCoord = Math.Ceiling( Math.Max(a, b));
            while (curX < viewport.ActualWidth / 2 - 20)
            {
                if (curX != 0)
                {
                    Line l = new Line();
                    l.X1 = curX + viewport.ActualWidth / 2;
                    l.Y1 = viewport.ActualHeight / 2 + 5;
                    l.X2 = curX + viewport.ActualWidth / 2;
                    l.Y2 = viewport.ActualHeight / 2 - 5;
                    l.Stroke = Brushes.Black;
                    viewport.Children.Add(l);

                    TextBlock textBlock = new TextBlock();
                    textBlock.Text = cur.ToString();
                    Canvas.SetLeft(textBlock, curX + viewport.ActualWidth / 2);
                    Canvas.SetTop(textBlock, viewport.ActualHeight / 2 + 10);
                    viewport.Children.Add(textBlock);

                    l = new Line();
                    l.X1 = -curX + viewport.ActualWidth / 2;
                    l.Y1 = viewport.ActualHeight / 2 + 5;
                    l.X2 = -curX + viewport.ActualWidth / 2;
                    l.Y2 = viewport.ActualHeight / 2 - 5;
                    l.Stroke = Brushes.Black;
                    viewport.Children.Add(l);

                    textBlock = new TextBlock();
                    textBlock.Text = (-cur).ToString();
                    Canvas.SetLeft(textBlock, -curX + viewport.ActualWidth / 2 - 5);
                    Canvas.SetTop(textBlock, viewport.ActualHeight / 2 + 10);
                    viewport.Children.Add(textBlock);
                }
                cur += coordStep;
                curX += step;
            }
            double curY = 0;
            cur = 0;
            while (curY < viewport.ActualHeight / 2 - 20)
            {
                if (curY != 0)
                {
                    Line l = new Line();
                    l.X1 = viewport.ActualWidth / 2 + 5;
                    l.Y1 = curY + viewport.ActualHeight / 2;
                    l.X2 = viewport.ActualWidth / 2 - 5;
                    l.Y2 = curY + viewport.ActualHeight / 2;
                    l.Stroke = Brushes.Black;
                    viewport.Children.Add(l);

                    TextBlock textBlock = new TextBlock();
                    textBlock.Text = cur.ToString();
                    Canvas.SetLeft(textBlock, viewport.ActualWidth / 2 + 10);
                    Canvas.SetTop(textBlock, -curY + viewport.ActualHeight / 2 - 5);
                    viewport.Children.Add(textBlock);




                    l = new Line();
                    l.X1 = viewport.ActualWidth / 2 + 5;
                    l.Y1 = -curY + viewport.ActualHeight / 2;
                    l.X2 = viewport.ActualWidth / 2 - 5;
                    l.Y2 = -curY + viewport.ActualHeight / 2;
                    l.Stroke = Brushes.Black;
                    viewport.Children.Add(l);

                    textBlock = new TextBlock();
                    textBlock.Text = (-cur).ToString();
                    Canvas.SetLeft(textBlock, viewport.ActualWidth / 2 + 10);
                    Canvas.SetTop(textBlock, curY + viewport.ActualHeight / 2 - 5);
                    viewport.Children.Add(textBlock);
                }
                curY += step;
                cur += coordStep;
            }
        }
        public MainWindow()
        {
            points = new Point[5];
            points[0] = new Point(-2, -3);
            points[1] = new Point(-1, 0);
            points[2] = new Point(0, 2);
            points[3] = new Point(2, 3);
            points[4] = new Point(4, 8);
            InitializeComponent();
            
        }

        private void viewport_Loaded(object sender, RoutedEventArgs e)
        {
            DrawCoords();
            DrawCurve();
        }

        private void viewport_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            viewport.Children.Clear();
            DrawCoords();
            DrawCurve();
        }
    }
}
