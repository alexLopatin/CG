using System;
using System.Diagnostics;
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
using System.Windows.Media.Media3D;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace lab3
{
    public static class MeshExtension
    {
        static int index = 0;
        public static void SetIndexZero(this MeshGeometry3D mesh)
        {
            index = 0;
        }
        public static void AddTriangle(this MeshGeometry3D mesh, Point3D first, Point3D second, Point3D third, Vector3D normal)
        {
            mesh.Positions.Add(first);
            mesh.Positions.Add(second);
            mesh.Positions.Add(third);
            mesh.Normals.Add(normal);
            mesh.Normals.Add(normal);
            mesh.Normals.Add(normal);
            mesh.TriangleIndices.Add(index++);
            mesh.TriangleIndices.Add(index++);
            mesh.TriangleIndices.Add(index++);
        }
    }
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {
        Point3D lightPos = new Point3D(-0.5, 2, 0);
        AmbientLight Alight = new AmbientLight(Color.FromRgb(100, 100, 100));
        public string LightX
        {
            get
            {
                return lightPos.X.ToString();
            }
            set
            {
                double i = 0;
                if (Double.TryParse(value, out i))
                    lightPos.X = i;
                OnPropertyChanged("LightX");
                GPointLight.Position = lightPos;
            }
        }
        public string LightY
        {
            get
            {
                return lightPos.Y.ToString();
            }
            set
            {
                double i = 0;
                if (Double.TryParse(value, out i))
                    lightPos.Y = i;
                OnPropertyChanged("LightY");
                GPointLight.Position = lightPos;
            }
        }
        public string LightZ
        {
            get
            {
                return lightPos.Z.ToString();
            }
            set
            {
                double i = 0;
                if (Double.TryParse(value, out i))
                    lightPos.Z = i;
                OnPropertyChanged("LightZ");
                GPointLight.Position = lightPos;
            }
        }
        public string lightRefl
        {
            get
            {
                return "";
            }
            set
            {
                double i = 0;
                if (Double.TryParse(value, out i))
                {
                    if (i > 3)
                        i = 3;
                    if (i < 0)
                        i = 0;
                    double t = i * 255 / 3;
                   byte c = (byte)(t);
                    Alight.Color = Color.FromRgb(c, c, c);
                    GPointLight.Color = Color.FromRgb(c, c, c);
                    OnPropertyChanged("lightRefl");
                }
                
            }
        }
        public string tessLevel
        {
            get
            {
                return "";
            }
            set
            {
                int i = 0;
                if (int.TryParse(value, out i))
                {
                    if (i > 1000)
                        i = 1000;
                    if (i < 3)
                        i = 2;
                    ModelsGroup.Children.Remove(CubeGeometryModel);
                    Brush brush = Brushes.ForestGreen;
                    CubeGeometryModel = new GeometryModel3D(GenerateObject(i), new DiffuseMaterial(brush));
                    CubeGeometryModel.Transform = transforms;
                    ModelsGroup.Children.Add(CubeGeometryModel);
                    OnPropertyChanged("tessLevel");
                }

            }
        }
        Vector3D CalculateNormal(Point3D a, Point3D b, Point3D c)
        {
            Vector3D dir = Vector3D.CrossProduct(b - a, c - a);
            dir.Normalize();
            return dir;
        }


        MeshGeometry3D GenerateObject(int stepsCount = 5)
        {
            MeshGeometry3D mesh = new MeshGeometry3D();
            mesh.SetIndexZero();
            double a = 0.5;
            double b = 0.25;
            double x = -a;
            double y = 0;
            double z = -0.5;
            for (int i = 1; i <= stepsCount; i++)
            {
                y = b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                Point3D first = new Point3D(x, y, z);
                Point3D second = new Point3D(-a , 0, z);
                x += 2 * a / stepsCount;
                y = b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                Point3D third = new Point3D(x, y, z);
                mesh.AddTriangle(first, third, second, new Vector3D(0, 0, -1));
                x -= 2 * a / stepsCount;
                //======================
                first = new Point3D(-a, 0, z);
                y = -b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                second = new Point3D(x, y, z);
                x += 2 * a / (double)stepsCount;
                y = -b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                third = new Point3D(x, y, z);
                mesh.AddTriangle(first, third, second, new Vector3D(0, 0, -1));
            }
            mesh.AddTriangle(new Point3D(-a, 0, z), new Point3D(x, y, z), new Point3D(x, -y, z), new Vector3D(0, 0, -1));
            a *= 0.6;
            b *= 0.6;
            z = 0.5;
            x = -a;
            for (int i = 1; i <= stepsCount; i++)
            {
                y = b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                Point3D first = new Point3D(x, y, z);
                Point3D second = new Point3D(-a, 0, z);
                x += 2 * a / stepsCount;
                y = b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                Point3D third = new Point3D(x, y, z);
                mesh.AddTriangle(first, second, third, new Vector3D(0, 0, -1));
                x -= 2 * a / stepsCount;
                //======================
                first = new Point3D(-a, 0, z);
                y = -b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                second = new Point3D(x, y, z);
                x += 2 * a / (double)stepsCount;
                y = -b * Math.Sqrt(Math.Abs(1 - x * x / (a * a)));
                third = new Point3D(x, y, z);
                mesh.AddTriangle(first, second, third, new Vector3D(0, 0, -1));
            }
            mesh.AddTriangle(new Point3D(-a, 0, z), new Point3D(x, y, z), new Point3D(x, -y, z), new Vector3D(0, 0, -1));
            a = 0.5;
            b = 0.25;
            double xU = -a * 0.6;
            double xD = -a;
            double yU = 0;
            double yD = 0;
            z = 0.5;

            for (int i = 1; i <= stepsCount; i++)
            {
                Point3D first = new Point3D(xU, yU, z);
                Point3D second = new Point3D(xD, yD, -z);
                xU += 2 * a * 0.6 / stepsCount;
                yU = 0.6 * b * Math.Sqrt(Math.Abs(1 - xU * xU / (a * a * 0.6 * 0.6)));
                Point3D third = new Point3D(xU, yU, z);
                //QVector3D normal = CalculateNormal(first, second, third);
                mesh.AddTriangle(first, third, second, CalculateNormal(first, third, second));
                first = new Point3D(xD, yD, -z);

                xD += 2 * a / stepsCount;
                yD = b * Math.Sqrt(Math.Abs(1 - xD * xD / (a * a)));
                second = new Point3D(xD, yD, -z);
                third = new Point3D(xU, yU, z);
                mesh.AddTriangle(first, third, second, CalculateNormal(first, third, second));
            }
            xU = -a * 0.6;
            xD = -a;
            yU = 0;
            yD = 0;
            for (int i = 1; i <= stepsCount; i++)
            {
                Point3D first = new Point3D(xU, yU, z);
                Point3D second = new Point3D(xD, yD, -z);
                xU += 2 * a * 0.6 / stepsCount;
                yU = -0.6 * b * Math.Sqrt(Math.Abs(1 - xU * xU / (a * a * 0.6 * 0.6)));
                Point3D third = new Point3D(xU, yU, z);
                //QVector3D normal = CalculateNormal(first, second, third);
                mesh.AddTriangle(first, second, third, CalculateNormal(first, second, third));
                first = new Point3D(xD, yD, -z);

                xD += 2 * a / stepsCount;
                yD = -b * Math.Sqrt(Math.Abs(1 - xD * xD / (a * a)));
                second = new Point3D(xD, yD, -z);
                third = new Point3D(xU, yU, z);
                mesh.AddTriangle(first, second, third, CalculateNormal(first, second, third));
            }

            return mesh;
        }

        public MainWindow()
        {
            InitializeComponent();
            
            ModelVisual3D GModelVisual3D = new ModelVisual3D();


            MeshGeometry3D mesh = GenerateObject();
            
            PerspectiveCamera Camera = new PerspectiveCamera();
            Camera.Position = new Point3D(0, 0, 2);
            Camera.LookDirection = new Vector3D(0, 0, -2);
            viewport.Camera = Camera;

            GPointLight = new PointLight();
            GPointLight.Color = Colors.DarkGray;
            
            GPointLight.Position = lightPos;
            ModelsGroup.Children.Add(GPointLight);
            
            ModelsGroup.Children.Add(Alight);
            Brush brush = Brushes.ForestGreen;
            CubeGeometryModel = new GeometryModel3D(mesh, new DiffuseMaterial(brush));
            CubeGeometryModel.BackMaterial = new DiffuseMaterial(Brushes.AliceBlue);
            transforms = new Transform3DGroup();
            transforms.Children.Add(new ScaleTransform3D(0.5, 0.5, 0.5));
            CubeGeometryModel.Transform = transforms;

            ModelsGroup.Children.Add(CubeGeometryModel);
            GModelVisual3D.Content = ModelsGroup;
            viewport.Children.Add(GModelVisual3D);
        }
        Model3DGroup ModelsGroup = new Model3DGroup();
        PointLight GPointLight = new PointLight();
        GeometryModel3D CubeGeometryModel;
        double mouseX = 0;
        double mouseY = 0;
        Transform3DGroup transforms;
        private void viewport_MouseMove(object sender, MouseEventArgs e)
        {
            double deltaX = mouseX - e.GetPosition(this).X;
            double deltaY = mouseY - e.GetPosition(this).Y;
            mouseX = e.GetPosition(this).X;
            mouseY = e.GetPosition(this).Y;
            
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                transforms.Children.Add(new RotateTransform3D(new AxisAngleRotation3D(new Vector3D(0, -1, 0), deltaX / 10)));
                transforms.Children.Add(new RotateTransform3D(new AxisAngleRotation3D(new Vector3D(-1, 0, 0), deltaY / 10)));
            }
        }

        private void Window_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            if(e.Delta > 0)
                transforms.Children.Add(new ScaleTransform3D(1.01, 1.01,1.01));
            if (e.Delta < 0)
                transforms.Children.Add(new ScaleTransform3D(1/1.01, 1/1.01, 1/1.01));

        }
        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged([CallerMemberName]string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {
            if(transforms != null) 
            {
                transforms.Children.Clear();
                transforms.Children.Add(new ScaleTransform3D(0.5, 0.5, 0.5));
            }
            
        }

        private void RadioButton_Checked_1(object sender, RoutedEventArgs e)
        {
            if (transforms != null)
            {
                transforms.Children.Clear();
                transforms.Children.Add(new ScaleTransform3D(0.5, 0.5, 0.5));
                transforms.Children.Add(new RotateTransform3D(new AxisAngleRotation3D(new Vector3D(0, 1, 0), 45)));
                transforms.Children.Add(new RotateTransform3D(new AxisAngleRotation3D(new Vector3D(1, 0, 0), 35.5)));
            }
        }

        private void RadioButton_Checked_2(object sender, RoutedEventArgs e)
        {
            if (transforms != null)
            {
                transforms.Children.Clear();
                transforms.Children.Add(new ScaleTransform3D(0.5, 0.5, 0));
            }
        }
    }
}
