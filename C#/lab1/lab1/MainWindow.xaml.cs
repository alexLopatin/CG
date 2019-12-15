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
        public string A
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
                    if(i != 0)
                    a = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }
        public string B
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
                    b = i;
                    viewport_SizeChanged(null, null);
                }
            }
        }
        double ToScreenY(double y)
        {
            return viewport.ActualHeight / 2 - y * 80/coordStep;
        }
        double ToScreenX(double x)
        {
            return viewport.ActualWidth / 2 + x * 80 / coordStep;
        }
        double a = 156;
        double b = 280;
        void DrawCurve()
        {
            int stepCount = 100;
            double x = -a;
            for(int i = 0; i < stepCount; i++)
            {
                Line l = new Line();
                l.X1 = ToScreenX(x);
                l.Y1 = ToScreenY(b * Math.Sqrt(Math.Abs(1 - (x*x)/(a*a))));
                x += 2 * a / stepCount;
                l.X2 = ToScreenX(x);
                l.Y2 = ToScreenY(b * Math.Sqrt(Math.Abs(1 - (x * x) / (a * a))));
                l.Stroke = Brushes.ForestGreen;
                viewport.Children.Add(l);

            }
            x = -a;
            for (int i = 0; i < stepCount; i++)
            {
                Line l = new Line();
                l.X1 = ToScreenX(x);
                l.Y1 = ToScreenY(-b * Math.Sqrt(Math.Abs(1 - (x * x) / (a * a))));
                x += 2 * a / stepCount;
                l.X2 = ToScreenX(x);
                l.Y2 = ToScreenY(-b * Math.Sqrt(Math.Abs(1 - (x * x) / (a * a))));
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
            double m = Math.Max(a, b);
            double p = Math.Log10(m);
            pow = (int)Math.Floor( Math.Log10(m));
            if (pow > 0)
                pow = 0;
            coordStep *= Math.Pow(10, pow);
            double rightX =((viewport.ActualWidth / 2 - 20) / step ) * coordStep;
            double topY = ((viewport.ActualHeight / 2 - 20) / step) * coordStep;
            int j = 0;
            while (rightX < m || topY < m)
            {
                if(j % 2 == 0)
                    coordStep *= 2;
                else
                    coordStep *= 5;
                j++;
                rightX = ((viewport.ActualWidth / 2 - 20) / step) * coordStep;
                topY = ((viewport.ActualHeight / 2 - 20) / step) * coordStep;
            }
            //double stepCoord = Math.Ceiling( Math.Max(a, b));
            while (curX < viewport.ActualWidth/2 - 20)
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
                    Canvas.SetLeft(textBlock, -curX + viewport.ActualWidth / 2 -5);
                    Canvas.SetTop(textBlock, viewport.ActualHeight / 2 + 10);
                    viewport.Children.Add(textBlock);
                }
                cur+= coordStep;
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
                    l.X2 =  viewport.ActualWidth / 2 - 5;
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
                cur+= coordStep;
            }
        }
        public MainWindow()
        {
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
