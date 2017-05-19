#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume16Reader.h>
#include <vtkVolume.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkCamera.h>

int main (int argc, char *argv[])
{
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " DATADIR/headsq/quarter" << endl;
		return EXIT_FAILURE;
	}

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

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

	// Función de transferencia
	vtkSmartPointer<vtkVolumeRayCastCompositeFunction> rayCastFunction = vtkSmartPointer<vtkVolumeRayCastCompositeFunction>::New();

	// Mapper que usará la función de transferencia
	vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkVolumeRayCastMapper>::New();
	// Establece la entrada de datos
	volumeMapper->SetInputConnection(v16->GetOutputPort());
	// Establece la función de transferencia
	volumeMapper->SetVolumeRayCastFunction(rayCastFunction);

	// Parte de color de la función de transferencia
	// Agrega a valores escalares colores RGB
	vtkSmartPointer<vtkColorTransferFunction>volumeColor = vtkSmartPointer<vtkColorTransferFunction>::New();
	volumeColor->AddRGBPoint(0,    0.0, 0.0, 0.0);
	volumeColor->AddRGBPoint(500,  1.0, 0.5, 0.3);
	volumeColor->AddRGBPoint(1000, 1.0, 0.5, 0.3);
	volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);

	// Parte de opacidad escalar de la función de transferencia
	// Agrega a valores escalares transparencias
	vtkSmartPointer<vtkPiecewiseFunction> volumeScalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeScalarOpacity->AddPoint(0,    0.00);
	volumeScalarOpacity->AddPoint(500,  0.15);
	volumeScalarOpacity->AddPoint(1000, 0.15);
	volumeScalarOpacity->AddPoint(1150, 0.85);

	// Parte de opacidad gradiente de la función de transferencia
	// Da más opacidad a las zonas donde hay un cambio de material
	// Agrega a valores de gradiente transparencias
	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeGradientOpacity->AddPoint(0,   0.0);
	volumeGradientOpacity->AddPoint(90,  0.5);
	volumeGradientOpacity->AddPoint(100, 1.0);

	// Crea el volume property que combina la función de trasferencia y el material
	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	// Establece la parte de color
	volumeProperty->SetColor(volumeColor);
	// Establece la parte de opacidad escalar
	volumeProperty->SetScalarOpacity(volumeScalarOpacity);
	// Establece la parte de opacidad gradiente
	volumeProperty->SetGradientOpacity(volumeGradientOpacity);
	// Interpolación lineal
	volumeProperty->SetInterpolationTypeToLinear();
	// Hace uso de sombras
	volumeProperty->ShadeOn();
	// Componente ambiental del material
	volumeProperty->SetAmbient(0.4);
	// Componente difusa del material
	volumeProperty->SetDiffuse(0.6);
	// Componente especular del material
	volumeProperty->SetSpecular(0.2);

	// Actor del volumen
	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
	// Establece el mapper (con los datos de entrada)
	volume->SetMapper(volumeMapper);
	// Establece las propiedades (con la función de transferencia y los materiales)
	volume->SetProperty(volumeProperty);
	// Agrega el volumen al renderer para su renderizado en el visor
	ren->AddViewProp(volume);

	vtkCamera *camera = ren->GetActiveCamera();
	double *c = volume->GetCenter();
	camera->SetFocalPoint(c[0], c[1], c[2]);
	camera->SetPosition(c[0] + 400, c[1], c[2]);
	camera->SetViewUp(0, 0, -1);

	renWin->SetSize(640, 480);

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;
}
