#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume16Reader.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkCamera.h>
#include <vtkStripper.h>
#include <vtkLookupTable.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkImageData.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkSmartPointer.h>
#include <vtkImageMapper3D.h>

int main (int argc, char *argv[])
{
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " DATADIR/headsq/quarter" << endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkRenderer> aRenderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(aRenderer);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	aRenderer->SetBackground(.2, .3, .4);
	renWin->SetSize(640, 480);

	// Lector
	vtkSmartPointer<vtkVolume16Reader> v16 = vtkSmartPointer<vtkVolume16Reader>::New();
	// Establece las dimensiones de la imagen imensiones de la imagen
	v16->SetDataDimensions(64, 64);
	// Rango (extensión) de los archivos que se van a leer (el primero y el último)
	v16->SetImageRange(1, 93);
	// Indica que el orden de los bytes que se van a leer está en Little Endian
	v16->SetDataByteOrderToLittleEndian();
	// Indica el prefijo de las imágenes que se va a leer
	v16->SetFilePrefix(argv[1]);
	// Indica el Spacing en X, Y y Z
	v16->SetDataSpacing(3.2, 3.2, 1.5);
	// Actualiza pipeline
	v16->Update();

	// Extrae piel
	vtkSmartPointer<vtkContourFilter> skinExtractor = vtkSmartPointer<vtkContourFilter>::New();
	// Establece la entrada de datos
	skinExtractor->SetInputConnection( v16->GetOutputPort());
	// Agrega un contorno estableciendo el índice y el valor de isosuperficie
	skinExtractor->SetValue(0, 500);
	// Actualiza pipeline
	skinExtractor->Update();

	// Crea normales para el shading de la superficie durante el renderizado
	vtkSmartPointer<vtkPolyDataNormals> skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
	// Establece la entrada de datos
	skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
	// Fija el ángulo para determinar si una arista es afilada o no
	skinNormals->SetFeatureAngle(60.0);
	// Actualiza pipeline
	skinNormals->Update();

	// Crea triángulos de la isosuperficie
	vtkSmartPointer<vtkStripper> skinStripper = vtkSmartPointer<vtkStripper>::New();
	// Establece la entrada de datos
	skinStripper->SetInputConnection(skinNormals->GetOutputPort());
	skinStripper->Update();

	// Mapper de las normales
	vtkSmartPointer<vtkPolyDataMapper> skinMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	// Establece la entrada de datos
	skinMapper->SetInputConnection(skinStripper->GetOutputPort());
	// No se usan los datos escalares (normales) para colorear el objeto
	skinMapper->ScalarVisibilityOff();

	// Actor del volumen
	vtkSmartPointer<vtkActor> skin = vtkSmartPointer<vtkActor>::New();
	// Establace el mapper que pintará el actor
	skin->SetMapper(skinMapper);
	// Color difuso (RGB)
	skin->GetProperty()->SetDiffuseColor(1, .49, .25);
	// Brillo especular
	skin->GetProperty()->SetSpecular(.3);
	// Potencia especular
	skin->GetProperty()->SetSpecularPower(20);

	// Extrae hueso
	vtkSmartPointer<vtkContourFilter> boneExtractor = vtkSmartPointer<vtkContourFilter>::New();
	// Establece la entrada de datos
	boneExtractor->SetInputConnection(v16->GetOutputPort());
	// Agrega un contorno estableciendo el índice y el valor de isosuperficie
	boneExtractor->SetValue(0, 1150);

	// Crea normales para el shading de la superficie durante el renderizado
	vtkSmartPointer<vtkPolyDataNormals> boneNormals = vtkSmartPointer<vtkPolyDataNormals>::New();
	// Establece la entrada de datos
	boneNormals->SetInputConnection(boneExtractor->GetOutputPort());
	// Fija el ángulo para determinar si una arista es afilada o no
	boneNormals->SetFeatureAngle(60.0);

	// Crea triángulos de la isosuperficie
	vtkSmartPointer<vtkStripper> boneStripper = vtkSmartPointer<vtkStripper>::New();
	// Establece la entrada de datos
	boneStripper->SetInputConnection(boneNormals->GetOutputPort());

	// Mapper de las normales
	vtkSmartPointer<vtkPolyDataMapper> boneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	// Establece la entrada de datos
	boneMapper->SetInputConnection(boneStripper->GetOutputPort());
	// No se usan los datos escalares (normales) para colorear el objeto
	boneMapper->ScalarVisibilityOff();

	// Actor del volumen
	vtkSmartPointer<vtkActor> bone = vtkSmartPointer<vtkActor>::New();
	// Establace el mapper que pintará el actor
	bone->SetMapper(boneMapper);
	// Color difuso (RGB)
	bone->GetProperty()->SetDiffuseColor(1, 1, .9412);

	// Borde del volumen
	vtkSmartPointer<vtkOutlineFilter> outlineData = vtkSmartPointer<vtkOutlineFilter>::New();
	// Establece la entrada de datos
	outlineData->SetInputConnection(v16->GetOutputPort());
	// Actualiza pipeline
	outlineData->Update();

	// Mapper del borde
	vtkSmartPointer<vtkPolyDataMapper> mapOutline = vtkSmartPointer<vtkPolyDataMapper>::New();
	// Establece la entrada de datos
	mapOutline->SetInputConnection(outlineData->GetOutputPort());

	// Actor del borde
	vtkSmartPointer<vtkActor> outline = vtkSmartPointer<vtkActor>::New();
	// Establace el mapper que pintará el actor
	outline->SetMapper(mapOutline);
	// Establace el color del borde
	outline->GetProperty()->SetColor(0, 0, 0);

	// Crea una tabla de color HSV (blanco y negro, variando el valor)
	vtkSmartPointer<vtkLookupTable> bwLut = vtkSmartPointer<vtkLookupTable>::New();
	// Rango de valores escalares de la tabla (minimo y máximo)
	bwLut->SetTableRange(0, 2000);
	// Rango de saturación
	bwLut->SetSaturationRange(0, 0);
	// Rango de matiz
	bwLut->SetHueRange(0, 0);
	// Rango de valor
	bwLut->SetValueRange(0, 1);
	// Genera la tabla con los valores dados
	bwLut->Build();

	// Crea una tabla de color HSV (variando el matiz)
	vtkSmartPointer<vtkLookupTable> hueLut = vtkSmartPointer<vtkLookupTable>::New();
	// Rango de valores escalares de la tabla (minimo y máximo)
	hueLut->SetTableRange(0, 2000);
	// Rango de matiz
	hueLut->SetHueRange(0, 1);
	// Rango de saturación
	hueLut->SetSaturationRange(1, 1);
	// Rango de valor
	hueLut->SetValueRange(1, 1);
	// Genera la tabla con los valores dados
	hueLut->Build();

	// Finally, create a lookup table with a single hue but having a range
	// in the saturation of the hue.
	// Crea una tabla de color HSV (variando la saturación)
	vtkSmartPointer<vtkLookupTable> satLut = vtkSmartPointer<vtkLookupTable>::New();
	// Rango de valores escalares de la tabla (minimo y máximo)
	satLut->SetTableRange(0, 2000);
	// Rango de matiz
	satLut->SetHueRange(.6, .6);
	// Rango de saturación
	satLut->SetSaturationRange(0, 1);
	// Rango de valor
	satLut->SetValueRange(1, 1);
	// Genera la tabla con los valores dados
	hueLut->Build();

	// Mapea la tabla de colores que se usará en el plano sagital
	vtkSmartPointer<vtkImageMapToColors> sagittalColors =  vtkSmartPointer<vtkImageMapToColors>::New();
	// Establece la entrada de datos
	sagittalColors->SetInputConnection(v16->GetOutputPort());
	// Establece la tabla de colores
	sagittalColors->SetLookupTable(bwLut);
	// Actualiza pipeline
	sagittalColors->Update();

	// Crea el plano sagital
	vtkSmartPointer<vtkImageActor> sagittal = vtkSmartPointer<vtkImageActor>::New();
	// Establece la entrada de datos
	sagittal->GetMapper()->SetInputConnection(sagittalColors->GetOutputPort());
	// Asigna el "extent" de la imagne (minX, maxX, minY, maxY, minZ, maxZ)
	sagittal->SetDisplayExtent(32, 32, 0, 63, 0, 92);

	// Mapea la tabla de colores que se usará en el plano axial
	vtkSmartPointer<vtkImageMapToColors> axialColors = vtkSmartPointer<vtkImageMapToColors>::New();
	// Establece la entrada de datos
	axialColors->SetInputConnection(v16->GetOutputPort());
	// Establece la tabla de colores
	axialColors->SetLookupTable(hueLut);
	// Actualiza pipeline
	axialColors->Update();

	// Crea el plano axial
	vtkSmartPointer<vtkImageActor> axial = vtkSmartPointer<vtkImageActor>::New();
	// Establece la entrada de datos
	axial->GetMapper()->SetInputConnection(axialColors->GetOutputPort());
	// Asigna el "extent" de la imagne (minX, maxX, minY, maxY, minZ, maxZ)
	axial->SetDisplayExtent(0, 63, 0, 63, 46, 46);

	// Mapea la tabla de colores que se usará en el plano coronal
	vtkSmartPointer<vtkImageMapToColors> coronalColors = vtkSmartPointer<vtkImageMapToColors>::New();
	// Establece la entrada de datos
	coronalColors->SetInputConnection(v16->GetOutputPort());
	// Establece la tabla de colores
	coronalColors->SetLookupTable(satLut);
	// Actualiza pipeline
	coronalColors->Update();

	// Crea el plano coronal
	vtkSmartPointer<vtkImageActor> coronal = vtkSmartPointer<vtkImageActor>::New();
	// Establece la entrada de datos
	coronal->GetMapper()->SetInputConnection(coronalColors->GetOutputPort());
	// Asigna el "extent" de la imagne (minX, maxX, minY, maxY, minZ, maxZ)
	coronal->SetDisplayExtent(0, 63, 32, 32, 0, 92);

	vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer<vtkCamera>::New();
	aCamera->SetViewUp (0, 0, -1);
	aCamera->SetPosition (0, 1, 0);
	aCamera->SetFocalPoint (0, 0, 0);
	aCamera->ComputeViewPlaneNormal();
	aCamera->Azimuth(30.0);
	aCamera->Elevation(30.0);

	aRenderer->AddActor(outline);
	aRenderer->AddActor(sagittal);
	aRenderer->AddActor(axial);
	aRenderer->AddActor(coronal);
	aRenderer->AddActor(skin);
	aRenderer->AddActor(bone);

	// No visualiza los huesos
	bone->VisibilityOff();

	// Actualiza la opacidad de la piel dando un valor semitransparente
	skin->GetProperty()->SetOpacity(0.5);

	aRenderer->SetActiveCamera(aCamera);

	renWin->Render();

	aRenderer->ResetCamera ();
	aCamera->Dolly(1.5);

	aRenderer->ResetCameraClippingRange ();

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}
