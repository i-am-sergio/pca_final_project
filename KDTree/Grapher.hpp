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

namespace graph {

    class Grapher {
        
        protected:
            vtkSmartPointer<vtkRenderer> renderer;
            vtkSmartPointer<vtkRenderWindow> renderWindow;
            vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
            vtkSmartPointer<vtkAxesActor> axes;
            vtkSmartPointer<vtkNamedColors> colors;
            vtkSmartPointer<vtkOrientationMarkerWidget> widget;
            vtkSmartPointer<vtkPoints> points;
            
        public:
            Grapher() { 
                renderer = vtkSmartPointer<vtkRenderer>::New();
                renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
                renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
                points = vtkSmartPointer<vtkPoints>::New(); 
                widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
                colors = vtkSmartPointer<vtkNamedColors>::New();
                axes = vtkSmartPointer<vtkAxesActor>::New();
                DrawLine(-10.0, 0.0, 0.0, 10.0, 0.0, 0.0, "Red"); // X
                DrawLine(0.0, -10.0, 0.0, 0.0, 10.0, 0.0, "Green"); // Y
                DrawLine(0.0, 0.0, -10.0, 0.0, 0.0, 10.0, "Blue"); // Z
            }

            ~Grapher() { }

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

            void DrawLine(double x1, double y1, double z1, double x2, double y2, double z2, const char* color) {
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
    };

}
