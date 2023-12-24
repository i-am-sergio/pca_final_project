#ifndef GRAPHER_HPP
#define GRAPHER_HPP
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkAxesActor.h>
#include <vtkStdString.h>
#include <vtkAppendPolyData.h>
#include <vtkLineSource.h>

namespace graph
{

    class Grapher
    {
    protected:
        vtkSmartPointer<vtkRenderer> renderer;
        vtkSmartPointer<vtkRenderWindow> renderWindow;
        vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
        vtkSmartPointer<vtkAxesActor> axes;
        vtkSmartPointer<vtkNamedColors> colors;
        vtkSmartPointer<vtkOrientationMarkerWidget> widget;
        vtkSmartPointer<vtkPoints> points;

    public:
        Grapher();
        ~Grapher();
        void AddPoint(long double x, long double y, long double z);
        void DrawPoints();
        void DrawLine(double x1, double y1, double z1, double x2, double y2, double z2, const char *color);
        void ShowWindow();
    };
}
#endif // GRAPHER_HPP