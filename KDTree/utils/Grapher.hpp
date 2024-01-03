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

        vtkSmartPointer<vtkPoints> points1;
        vtkSmartPointer<vtkPoints> points2;
        vtkSmartPointer<vtkPoints> points3;
        vtkSmartPointer<vtkPoints> points4;
        vtkSmartPointer<vtkPoints> points5;
        vtkSmartPointer<vtkPoints> points6;
        vtkSmartPointer<vtkPoints> points7;
        vtkSmartPointer<vtkPoints> points8; 

        vtkSmartPointer<vtkPoints> centroides;

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
            points1 = vtkSmartPointer<vtkPoints>::New();
            points2 = vtkSmartPointer<vtkPoints>::New();
            points3 = vtkSmartPointer<vtkPoints>::New();
            points4 = vtkSmartPointer<vtkPoints>::New();
            points5 = vtkSmartPointer<vtkPoints>::New();
            points6 = vtkSmartPointer<vtkPoints>::New();
            points7 = vtkSmartPointer<vtkPoints>::New();
            points8 = vtkSmartPointer<vtkPoints>::New();
            centroides = vtkSmartPointer<vtkPoints>::New();
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

        void AddCentroide(double x, double y, double z)
        {
            centroides->InsertNextPoint(x, y, z);
        }

        void DrawCentroides()
        {
            vtkNew<vtkPolyData> polyData;
            polyData->SetPoints(centroides);

            vtkNew<vtkVertexGlyphFilter> vertexFilter;
            vertexFilter->SetInputData(polyData);

            vtkNew<vtkPolyDataMapper> mapper;
            mapper->SetInputConnection(vertexFilter->GetOutputPort());

            vtkNew<vtkActor> pointActor;
            pointActor->SetMapper(mapper);
            pointActor->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
            pointActor->GetProperty()->SetPointSize(10);
            pointActor->GetProperty()->SetRepresentationToPoints(); 

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


        void addVector(double x1, double y1, double z1, double x2, double y2, double z2, const char *color)
        {
            auto lineSource = vtkSmartPointer<vtkLineSource>::New();
            lineSource->SetPoint1(x1, y1, z1);
            lineSource->SetPoint2(x2, y2, z2);
            lineSource->Update();
            auto lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            lineMapper->SetInputConnection(lineSource->GetOutputPort());
            auto lineActor = vtkSmartPointer<vtkActor>::New();
            lineActor->SetMapper(lineMapper);
            lineActor->GetProperty()->SetColor(colors->GetColor3d(color).GetData());
            renderer->AddActor(lineActor);
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


        void printClusteres(vector<vector<Point3D>>& clusteres){
            vector<Point3D> cluster1 = clusteres[0];
            vector<Point3D> cluster2 = clusteres[1];
            vector<Point3D> cluster3 = clusteres[2];
            vector<Point3D> cluster4 = clusteres[3];
            vector<Point3D> cluster5 = clusteres[4];
            vector<Point3D> cluster6 = clusteres[5];
            vector<Point3D> cluster7 = clusteres[6];
            vector<Point3D> cluster8 = clusteres[7];

            for(auto &row: clusteres){
                cout<<"size cluster: "<<row.size()<<endl;
            }


            for (auto &row : cluster1)
                points1->InsertNextPoint(row[0], row[1], row[2]);
            for (auto &row : cluster2)
                points2->InsertNextPoint(row[0], row[1], row[2]);
            for (auto &row : cluster3)
                points3->InsertNextPoint(row[0], row[1], row[2]);
            for (auto &row : cluster4)
                points4->InsertNextPoint(row[0], row[1], row[2]);
            for (auto &row : cluster5)
                points5->InsertNextPoint(row[0], row[1], row[2]);
            for (auto &row : cluster6)
                points6->InsertNextPoint(row[0], row[1], row[2]);
            for (auto &row : cluster7)
                points7->InsertNextPoint(row[0], row[1], row[2]);
            for (auto &row : cluster8)
                points8->InsertNextPoint(row[0], row[1], row[2]);

            vtkNew<vtkPolyData> polyData1;
            polyData1->SetPoints(points1);
            vtkNew<vtkVertexGlyphFilter> vertexFilter1;
            vertexFilter1->SetInputData(polyData1);
            vtkNew<vtkPolyDataMapper> mapper1;
            mapper1->SetInputConnection(vertexFilter1->GetOutputPort());
            vtkNew<vtkActor> pointActor1;
            pointActor1->SetMapper(mapper1);
            pointActor1->GetProperty()->SetColor(colors->GetColor3d("Red").GetData());
            pointActor1->GetProperty()->SetPointSize(5);
            pointActor1->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor1);

            vtkNew<vtkPolyData> polyData2;
            polyData2->SetPoints(points2);
            vtkNew<vtkVertexGlyphFilter> vertexFilter2;
            vertexFilter2->SetInputData(polyData2);
            vtkNew<vtkPolyDataMapper> mapper2;
            mapper2->SetInputConnection(vertexFilter2->GetOutputPort());
            vtkNew<vtkActor> pointActor2;
            pointActor2->SetMapper(mapper2);
            pointActor2->GetProperty()->SetColor(colors->GetColor3d("Green").GetData());
            pointActor2->GetProperty()->SetPointSize(5);
            pointActor2->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor2);

            vtkNew<vtkPolyData> polyData3;
            polyData3->SetPoints(points3);
            vtkNew<vtkVertexGlyphFilter> vertexFilter3;
            vertexFilter3->SetInputData(polyData3);
            vtkNew<vtkPolyDataMapper> mapper3;
            mapper3->SetInputConnection(vertexFilter3->GetOutputPort());
            vtkNew<vtkActor> pointActor3;
            pointActor3->SetMapper(mapper3);
            pointActor3->GetProperty()->SetColor(colors->GetColor3d("Blue").GetData());
            pointActor3->GetProperty()->SetPointSize(5);
            pointActor3->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor3);

            vtkNew<vtkPolyData> polyData4;
            polyData4->SetPoints(points4);
            vtkNew<vtkVertexGlyphFilter> vertexFilter4;
            vertexFilter4->SetInputData(polyData4);
            vtkNew<vtkPolyDataMapper> mapper4;
            mapper4->SetInputConnection(vertexFilter4->GetOutputPort());
            vtkNew<vtkActor> pointActor4;
            pointActor4->SetMapper(mapper4);
            pointActor4->GetProperty()->SetColor(colors->GetColor3d("Yellow").GetData());
            pointActor4->GetProperty()->SetPointSize(5);
            pointActor4->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor4);

            vtkNew<vtkPolyData> polyData5;
            polyData5->SetPoints(points5);
            vtkNew<vtkVertexGlyphFilter> vertexFilter5;
            vertexFilter5->SetInputData(polyData5);
            vtkNew<vtkPolyDataMapper> mapper5;
            mapper5->SetInputConnection(vertexFilter5->GetOutputPort());
            vtkNew<vtkActor> pointActor5;
            pointActor5->SetMapper(mapper5);
            pointActor5->GetProperty()->SetColor(colors->GetColor3d("Cyan").GetData());
            pointActor5->GetProperty()->SetPointSize(5);
            pointActor5->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor5);
            
            vtkNew<vtkPolyData> polyData6;
            polyData6->SetPoints(points6);
            vtkNew<vtkVertexGlyphFilter> vertexFilter6;
            vertexFilter6->SetInputData(polyData6);
            vtkNew<vtkPolyDataMapper> mapper6;
            mapper6->SetInputConnection(vertexFilter6->GetOutputPort());
            vtkNew<vtkActor> pointActor6;
            pointActor6->SetMapper(mapper6);
            pointActor6->GetProperty()->SetColor(colors->GetColor3d("Magenta").GetData());
            pointActor6->GetProperty()->SetPointSize(5);
            pointActor6->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor6);

            vtkNew<vtkPolyData> polyData7;
            polyData7->SetPoints(points7);
            vtkNew<vtkVertexGlyphFilter> vertexFilter7;
            vertexFilter7->SetInputData(polyData7);
            vtkNew<vtkPolyDataMapper> mapper7;
            mapper7->SetInputConnection(vertexFilter7->GetOutputPort());
            vtkNew<vtkActor> pointActor7;
            pointActor7->SetMapper(mapper7);
            pointActor7->GetProperty()->SetColor(colors->GetColor3d("White").GetData());
            pointActor7->GetProperty()->SetPointSize(5);
            pointActor7->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor7);
            
            vtkNew<vtkPolyData> polyData8;
            polyData8->SetPoints(points8);
            vtkNew<vtkVertexGlyphFilter> vertexFilter8;
            vertexFilter8->SetInputData(polyData8);
            vtkNew<vtkPolyDataMapper> mapper8;
            mapper8->SetInputConnection(vertexFilter8->GetOutputPort());
            vtkNew<vtkActor> pointActor8;
            pointActor8->SetMapper(mapper8);
            pointActor8->GetProperty()->SetColor(colors->GetColor3d("Black").GetData());
            pointActor8->GetProperty()->SetPointSize(5);
            pointActor8->GetProperty()->SetOpacity(0.8);
            renderer->AddActor(pointActor8);

            cout<<"termino printClusteres"<<endl;

        }
    };

}
