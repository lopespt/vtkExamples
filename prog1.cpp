
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkElevationFilter.h>
#include <vtkWarpScalar.h>
#include <vtkBooleanOperationPolyDataFilter.h>

void prog1(){
    //Cria o data source
    vtkSphereSource *source = vtkSphereSource::New();
    source->SetRadius(1);
    source->SetPhiResolution(50);
    source->SetThetaResolution(50);

    //Filtro
    vtkElevationFilter *filter = vtkElevationFilter::New();
    filter->SetInputConnection(source->GetOutputPort());
    filter->SetLowPoint(0,0,-1);
    filter->SetHighPoint(0,0,1);

    vtkWarpScalar *filter2 = vtkWarpScalar::New();
    filter2->SetInputConnection(filter->GetOutputPort());
    filter2->SetScaleFactor(2);




    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(filter2->GetOutputPort());

    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);

    //Exibe a janela
    vtkRenderWindow *window = vtkRenderWindow::New();
    vtkRenderer *render = vtkRenderer::New();
    vtkRenderWindowInteractor *interac = vtkRenderWindowInteractor::New();
    window->SetInteractor(interac);
    window->AddRenderer(render);

    render->AddActor(actor);

    interac->Initialize();
    window->Render();
    interac->Start();


    //desaloca tudo
    filter->Delete();
    actor->Delete();
    mapper->Delete();
    source->Delete();
    interac->Delete();
    render->Delete();
    window->Delete();

}
