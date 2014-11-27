#include <stdio.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkDataObject.h>
#include <vtkElevationFilter.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkUnsignedCharArray.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkCubeSource.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>
void teste3();
int teste2();
void teste4();
void teste5();
void prog1();

class guiSetAlpha:public vtkDataSetAlgorithm{

public:
    static guiSetAlpha* New(){
        return new guiSetAlpha;
    }

    virtual int RequestData(vtkInformation* info,
                            vtkInformationVector** in,
                            vtkInformationVector* out) {

        vtkDataSet* input = vtkDataSet::GetData(in[0]);
        vtkDataSet* output = vtkDataSet::GetData(out);
        output->ShallowCopy(input);

        vtkPointData* data =  output->GetPointData();
        vtkUnsignedCharArray *array = vtkUnsignedCharArray::New();
        array->SetNumberOfComponents(4);
        array->SetName("tt");
        int points = input->GetNumberOfPoints();
        printf("%ld", points);
        fflush(stdout);
        for(int i=0;i<points;i++){
            //array->InsertNextTuple4(255,1,255,50);
            array->InsertNextTuple4(i*255./points,i*255./points,i*255./points,255);
        }

        data->AddArray(array);
        array->Delete();
        data->SetActiveScalars("tt");
        //data->SetActiveVectors("tt");

        return 1;
    };

};

int teste1(){

    vtkSphereSource* sphere1 = vtkSphereSource::New();
    vtkTriangleFilter *sphere = vtkTriangleFilter::New();
    sphere->SetInputConnection(sphere1->GetOutputPort());

    vtkCubeSource* cube1 = vtkCubeSource::New();
    vtkTriangleFilter *cube2 = vtkTriangleFilter::New();
    cube2->SetInputConnection(cube1->GetOutputPort());
    vtkTransformFilter *cube = vtkTransformFilter::New();
    cube->SetInputConnection(cube2->GetOutputPort());
    vtkTransform* trans = vtkTransform::New();
    trans->Translate(0.3,0.3,0.3);
    cube->SetTransform(trans);

    vtkBooleanOperationPolyDataFilter *b = vtkBooleanOperationPolyDataFilter::New();
    b->SetInputConnection(0,sphere->GetOutputPort());
    b->SetInputConnection(1, cube->GetOutputPort());
    b->SetOperationToUnion();

    guiSetAlpha *alpha = guiSetAlpha::New();
    alpha->SetInputConnection(b->GetOutputPort());

    vtkLinearSubdivisionFilter *l = vtkLinearSubdivisionFilter::New();
    l->SetInputConnection(alpha->GetOutputPort());
    l->SetNumberOfSubdivisions(1);

    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetScalarModeToUsePointFieldData();
    mapper->SetInputConnection(b->GetOutputPort());
    mapper->SelectColorArray("tt");

    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);

    vtkRenderWindow* window = vtkRenderWindow::New();
    vtkRenderer *renderer = vtkRenderer::New();
    vtkRenderWindowInteractor* interactor = vtkRenderWindowInteractor::New();
    window->AddRenderer(renderer);
    window->SetInteractor(interactor);
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
    teste1();
}
