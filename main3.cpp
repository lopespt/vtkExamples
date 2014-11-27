#include <vtkImageData.h>
#include <vtkContourFilter.h>
#include <vtkDoubleArray.h>
#include <math.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkWarpScalar.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkTessellatorFilter.h>

void teste3(){
    vtkImageData *img = vtkImageData::New();
    img->SetDimensions(100,100,1);
    vtkDoubleArray *array = vtkDoubleArray::New();
    array->SetName("valor");
    for(int j=0;j<100;j++){
        for(int i=0;i<100;i++){
            //img->SetScalarComponentFromFloat(i,j,0,0, sin(i)+cos(j));
            array->InsertNextTuple1(sin(i)+cos(j));
        }
    }
    img->GetPointData()->AddArray(array);
    img->GetPointData()->SetActiveScalars("valor");

    vtkContourFilter *contour = vtkContourFilter::New();
    contour->SetInputData(img);
    contour->GenerateValues(10, -1,1);
    contour->Update();

    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(contour->GetOutputPort());
    mapper->SetScalarModeToUsePointData();


    vtkImageDataGeometryFilter *geoFilter = vtkImageDataGeometryFilter::New();
    geoFilter->SetInputData(img);
    vtkWarpScalar *scalar = vtkWarpScalar::New();
    scalar->SetInputConnection(geoFilter->GetOutputPort());


    vtkPolyDataMapper* mapper2 = vtkPolyDataMapper::New();
    mapper2->SetInputConnection(scalar->GetOutputPort());


    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);

    vtkActor *actor2 = vtkActor::New();
    actor2->SetMapper(mapper2);
    actor2->GetProperty()->SetInterpolationToFlat();
    actor2->GetProperty()->SetInterpolationToGouraud();

    vtkRenderWindow *win = vtkRenderWindow::New();
    vtkRenderer *render = vtkRenderer::New();
    vtkRenderWindowInteractor *inter = vtkRenderWindowInteractor::New();
    render->GetActiveCamera()->SetPosition(0,0,10);
    render->GetActiveCamera()->SetFocalPoint(50,30,0);
    render->GetActiveCamera()->SetViewUp(0,0,1);
    win->SetInteractor(inter);
    win->AddRenderer(render);
    render->AddActor(actor2);
    win->Render();
    inter->Start();

    array->Delete();
    inter->Delete();
    render->Delete();
    win->Delete();
    actor->Delete();
    mapper->Delete();
    contour->Delete();
    img->Delete();
}
