#include <stdio.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkImageData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkImageMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkPoints.h>
#include <vtkDelaunay2D.h>
#include <vtkPolyData.h>
#include <math.h>
#include <time.h>
#include <vtkElevationFilter.h>
int teste2(){

    vtkSphereSource* sphere = vtkSphereSource::New();
    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(sphere->GetOutputPort());

    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);

    srand(time(NULL));
    //Cria Malha
    vtkPoints *points = vtkPoints::New();
    vtkPolyData *polyData = vtkPolyData::New();
    points->Allocate(10000);
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            points->InsertNextPoint(i,j, (i-50 + j-50)*(sin(i/M_PI)+cos(j/M_PI)) );
        }
    }
    polyData->SetPoints(points);

    vtkDelaunay2D *del = vtkDelaunay2D::New();
    del->AddInputData(polyData);

    vtkPolyDataMapper *mapperImg = vtkPolyDataMapper::New();
    vtkElevationFilter *elev = vtkElevationFilter::New();
    elev->SetInputConnection(del->GetOutputPort());
    elev->SetLowPoint(0,0,-100);
    elev->SetHighPoint(0,0,100);

    vtkActor* actor2 = vtkActor::New();
    mapperImg->SetInputConnection(elev->GetOutputPort());
    mapperImg->Update();
    actor2->SetMapper(mapperImg);


    vtkRenderWindow* window = vtkRenderWindow::New();
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindowInteractor* interactor = vtkRenderWindowInteractor::New();
    window->AddRenderer(renderer);
    window->SetInteractor(interactor);
    vtkProperty* prop = actor->GetProperty();
    prop->SetColor(1,0,0);

    //renderer->AddActor(actor);
    renderer->AddActor(actor2);
    window->Render();
    interactor->Start();

    window->Delete();
    renderer->Delete();
    actor->Delete();
    mapper->Delete();
    sphere->Delete();
    mapperImg->Delete();
    actor2->Delete();

    return 0;
}

