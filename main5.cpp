
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkStructuredGrid.h>
#include <vtkPoints.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkStructuredGridGeometryFilter.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkCellData.h>
#include <vtkIntArray.h>
#include <vtkPointData.h>
#include <vtkGlyph3D.h>
#include <vtkGlyph3DMapper.h>
#include <vtkArrowSource.h>
#include <vtkInteractorStyle.h>
void teste5(){
    srand(time(NULL));
    vtkPoints* points = vtkPoints::New();

    vtkIntArray *pointarr = vtkIntArray::New();
    vtkIntArray *pointarr2 = vtkIntArray::New();
    pointarr->SetNumberOfComponents(3);
    for(int j = 0;j<100;j++){
        for(int i = 0;i<100;i++){
            points->InsertNextPoint(i,j, sin(i/10.)*10);
            pointarr->InsertNextTuple3(rand()%100,rand()%100,rand()%100);
            pointarr2->InsertNextTuple1(i+j);
        }
    }
        vtkIntArray *arr = vtkIntArray::New();

    for(int j=0;j<99;j++){
        for(int i=0;i<99;i++){
            arr->InsertNextTuple1(i+j);
        }
    }

    vtkStructuredGrid *grid = vtkStructuredGrid::New();
    pointarr->SetName("nome2");
    pointarr2->SetName("nome3");
    grid->GetPointData()->AddArray(pointarr);
    grid->GetPointData()->AddArray(pointarr2);
    grid->GetPointData()->SetActiveAttribute("nome2", vtkDataSetAttributes::VECTORS);
    grid->GetPointData()->SetActiveAttribute("nome3", vtkDataSetAttributes::SCALARS);

    arr->SetName("nome");
    grid->GetCellData()->AddArray(arr);
    arr->Delete();
    grid->GetCellData()->SetActiveAttribute("nome", vtkDataSetAttributes::SCALARS);
    grid->SetDimensions(100,100,1);
    grid->SetPoints(points);

    vtkStructuredGridGeometryFilter *geo = vtkStructuredGridGeometryFilter::New();
    geo->SetInputData(grid);
    geo->Update();

    vtkArrowSource *arrow = vtkArrowSource::New();
    vtkGlyph3D *glyp = vtkGlyph3D::New();
    glyp->SetSourceConnection(arrow->GetOutputPort());
    glyp->OrientOn();
    glyp->SetVectorModeToUseVector();
    glyp->SetInputConnection(geo->GetOutputPort());
    glyp->SetScaleModeToScaleByVectorComponents();
    glyp->SetScaleFactor(0.01);
    glyp->SetColorModeToColorByScalar();
    glyp->Update();


    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(glyp->GetOutputPort());
    mapper->SetScalarModeToUseCellData();
    mapper->SetScalarRange(0,200);


    vtkPolyDataMapper *mapper2 = vtkPolyDataMapper::New();
    mapper2->SetInputConnection(geo->GetOutputPort());
    mapper2->SetColorModeToMapScalars();
    mapper2->SetScalarModeToUsePointData();
    mapper2->SetScalarRange(0,200);


    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);

    vtkActor* actor2 = vtkActor::New();
    actor2->SetMapper(mapper2);

    vtkRenderer *render = vtkRenderer::New();
    vtkRenderWindowInteractor *interact = vtkRenderWindowInteractor::New();

    vtkRenderWindow *win = vtkRenderWindow::New();

    win->SetInteractor(interact);
    win->AddRenderer(render);
    render->AddActor(actor);
    render->AddActor(actor2);

    interact->Initialize();
    win->Render();
    interact->Start();


}
