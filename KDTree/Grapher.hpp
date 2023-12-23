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

#include <array>
#include <vector>
using namespace std;

namespace graph {

    class Grapher {
        protected:
            vtkNew<vtkRenderer> renderer;
            vtkNew<vtkRenderWindow> renderWindow;
            vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
            vtkNew<vtkNamedColors> colors;
            vtkNew<vtkAxesActor> axes;
            vtkNew<vtkOrientationMarkerWidget> widget;
            vtkSmartPointer<vtkOrientationMarkerWidget> widget2;
            vtkSmartPointer<vtkPoints> points;
            vector<vtkSmartPointer<vtkPolyData>> cubes;
            
        public:
            Grapher() { 
                points = vtkSmartPointer<vtkPoints>::New(); 
                // axes->SetShaftTypeToCylinder();
                axes->SetXAxisLabelText("X");
                axes->SetYAxisLabelText("Y");
                axes->SetZAxisLabelText("Z");
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
                pointActor->GetProperty()->SetColor(colors->GetColor3d("GreenYellow").GetData());
                pointActor->GetProperty()->SetPointSize(2);

                renderer->AddActor(pointActor);
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
