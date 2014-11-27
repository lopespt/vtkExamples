
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyData.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkSliderWidget.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkCommand.h>
#include <stdio.h>
#include <vtkSphereSource.h>
#include <vtkCamera.h>
class call: public vtkCommand{
public:
    vtkSphereSource *source;

    static call* New(vtkSphereSource *source){
        call * n = new call;
        n->source = source;
        return n;
    }

   void Execute(vtkObject *caller, unsigned long eventId, void *callData){
      vtkSliderWidget *sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);
        vtkSliderRepresentation2D* rep = static_cast<vtkSliderRepresentation2D*>(sliderWidget->GetSliderRepresentation());
        this->source->SetRadius(rep->GetValue()/100.);
  }



};


void teste4(){
    vtkSphereSource *sphere = vtkSphereSource::New();
    vtkPolyDataMapper *mapper =  vtkPolyDataMapper::New();
    mapper->SetInputConnection(sphere->GetOutputPort());
    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);

    vtkSliderRepresentation2D *slider = vtkSliderRepresentation2D::New();
    slider->SetMaximumValue(100);
    slider->SetMinimumValue(0);
    slider->GetPoint1Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    slider->GetPoint1Coordinate()->SetValue(0,0);
    slider->GetPoint2Coordinate()->SetCoordinateSystemToNormalizedDisplay();
    slider->GetPoint2Coordinate()->SetValue(1,0);

    vtkSliderWidget *sl = vtkSliderWidget::New();
    sl->SetRepresentation(slider);
    call* cal = call::New(sphere);
    sl->AddObserver(vtkCommand::InteractionEvent, cal);

    vtkRenderer *render = vtkRenderer::New();
    vtkRenderWindow *window  =  vtkRenderWindow::New();
    vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
    window->AddRenderer(render);
    window->SetInteractor(interactor);
    window->FullScreenOn();
    sl->SetInteractor(interactor);
    sl->SetAnimationModeToAnimate();
    sl->EnabledOn();

    render->AddActor(actor);

    interactor->Initialize();
    window->Render();
    interactor->Start();

    render->Delete();
    window->Delete();

}
