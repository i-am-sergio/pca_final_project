#pragma once
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
#include "../includes/KDTree.hpp"
using namespace kdt;

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
        vtkSmartPointer<vtkAppendPolyData> linesBlue;
        vtkSmartPointer<vtkAppendPolyData> linesGreen;
        vtkSmartPointer<vtkAppendPolyData> linesRed;

    public:
        Grapher()
        {
            renderer = vtkSmartPointer<vtkRenderer>::New();
            renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
            renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
            points = vtkSmartPointer<vtkPoints>::New();
            widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
            colors = vtkSmartPointer<vtkNamedColors>::New();
            axes = vtkSmartPointer<vtkAxesActor>::New();
            linesBlue = vtkSmartPointer<vtkAppendPolyData>::New();
            linesGreen = vtkSmartPointer<vtkAppendPolyData>::New();
            linesRed = vtkSmartPointer<vtkAppendPolyData>::New();
            DrawLine(-20.0, 0.0, 0.0, 20.0, 0.0, 0.0, "Red");   // X
            DrawLine(0.0, -20.0, 0.0, 0.0, 20.0, 0.0, "Green"); // Y
            DrawLine(0.0, 0.0, -20.0, 0.0, 0.0, 20.0, "Blue");  // Z
        }

        ~Grapher() {}

        void AddPoint(double x, double y, double z)
        {
            points->InsertNextPoint(x, y, z);
        }

        void DrawPoints()
        {
            vtkNew<vtkPolyData> polyData;
            polyData->SetPoints(points);

            vtkNew<vtkVertexGlyphFilter> vertexFilter;
            vertexFilter->SetInputData(polyData);

            vtkNew<vtkPolyDataMapper> mapper;
            mapper->SetInputConnection(vertexFilter->GetOutputPort());

            vtkNew<vtkActor> pointActor;
            pointActor->SetMapper(mapper);
            pointActor->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
            pointActor->GetProperty()->SetPointSize(2);

            renderer->AddActor(pointActor);
        }

        void addLine(double x1, double y1, double z1, double x2, double y2, double z2, const char *color)
        {
            auto lineSource = vtkSmartPointer<vtkLineSource>::New();
            lineSource->SetPoint1(x1, y1, z1);
            lineSource->SetPoint2(x2, y2, z2);
            lineSource->Update();
            if (strcmp(color, "Red") == 0)
                linesRed->AddInputData(lineSource->GetOutput());
            else if (strcmp(color, "Green") == 0)
                linesGreen->AddInputData(lineSource->GetOutput());
            else if (strcmp(color, "Blue") == 0)
                linesBlue->AddInputData(lineSource->GetOutput());
            else
                linesRed->AddInputData(lineSource->GetOutput());
        }

        void DrawLines()
        {
            DrawLinesForColor("Red", linesRed);
            DrawLinesForColor("Green", linesGreen);
            DrawLinesForColor("Blue", linesBlue);
        }

        void DrawLinesForColor(const char *color, vtkSmartPointer<vtkAppendPolyData> lines)
        {
            auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputConnection(lines->GetOutputPort());
            auto lineActor = vtkSmartPointer<vtkActor>::New();
            lineActor->SetMapper(mapper);
            if (strcmp(color, "Red") == 0)
                lineActor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
            else if (strcmp(color, "Green") == 0)
                lineActor->GetProperty()->SetColor(colors->GetColor3d("Green").GetData());
            else if (strcmp(color, "Blue") == 0)
                lineActor->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData());
            renderer->AddActor(lineActor);
        }

        void DrawLine(double x1, double y1, double z1, double x2, double y2, double z2, const char *color)
        {
            auto lineSource = vtkSmartPointer<vtkLineSource>::New();
            lineSource->SetPoint1(x1, y1, z1);
            lineSource->SetPoint2(x2, y2, z2);

            auto lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            lineMapper->SetInputConnection(lineSource->GetOutputPort());

            auto lineActor = vtkSmartPointer<vtkActor>::New();
            lineActor->SetMapper(lineMapper);
            lineActor->GetProperty()->SetColor(colors->GetColor3d(color).GetData());
            renderer->AddActor(lineActor);
        }

        void ShowWindow()
        {
            renderWindow->SetWindowName("Puntos");
            renderWindow->AddRenderer(renderer);
            renderWindow->SetSize(renderWindow->GetScreenSize());
            renderWindowInteractor->SetRenderWindow(renderWindow);

            widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
            widget->SetOrientationMarker(axes);
            widget->SetInteractor(renderWindowInteractor);
            widget->SetViewport(0.0, 0.0, 0.2, 0.2);
            widget->SetEnabled(1);
            widget->InteractiveOn();

            renderer->ResetCamera();
            renderWindow->Render();
            renderWindowInteractor->Initialize();
            renderWindowInteractor->Start();
        }

        void addPointKD(Node *node, int depth = 0, double minX = -20.0, double minY = -20.0, double minZ = -20.0, double maxX = 20.0, double maxY = 20.0, double maxZ = 20.0)
        {
            if (node == nullptr)
                return;
            double currentX = node->point[0];
            double currentY = node->point[1];
            double currentZ = node->point[2];
            AddPoint(currentX, currentY, currentZ);
            if (depth == 0)
                addLine(currentX, currentY, currentZ, currentX, minY, currentZ, "Red"); // Línea X hacia Y
            else if (depth == 1)
                addLine(currentX, currentY, currentZ, currentX, currentY, maxZ, "Green"); // Línea Y hacia Z
            else if (depth == 2)
                addLine(currentX, currentY, currentZ, maxX, currentY, currentZ, "Blue"); // Línea Z hacia X
            addPointKD(node->right, (depth + 1) % 3,
                       depth == 0 ? currentX : minX, depth == 1 ? currentY : minY, depth == 2 ? currentZ : minZ,
                       depth == 0 ? maxX : currentX, depth == 1 ? maxY : currentY, depth == 2 ? maxZ : currentZ);
            addPointKD(node->left, (depth + 1) % 3,
                       depth == 0 ? minX : currentX, depth == 1 ? minY : currentY, depth == 2 ? minZ : currentZ,
                       depth == 0 ? currentX : maxX, depth == 1 ? currentY : maxY, depth == 2 ? currentZ : maxZ);
        }

        void printKD(KDTree<3>& kdtree)
        {
            addPointKD(kdtree.getNode());
        }
    };

}
