#include <stdio.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
void teste3();
int teste2();
void teste4();
void teste5();
void prog1();

int teste1(){

    vtkSphereSource* sphere = vtkSphereSource::New();
    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(sphere->GetOutputPort());

    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);

    vtkRenderWindow* window = vtkRenderWindow::New();
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindowInteractor* interactor = vtkRenderWindowInteractor::New();
    window->AddRenderer(renderer);
    window->SetInteractor(interactor);


    vtkProperty* prop = actor->GetProperty();
    prop->SetColor(1,0,0);

    renderer->AddActor(actor);
    window->Render();
    interactor->Start();

    window->Delete();
    renderer->Delete();
    actor->Delete();
    mapper->Delete();
    sphere->Delete();
    return 0;
}

int main(int argc, char* argv[]){
    teste2();
}
