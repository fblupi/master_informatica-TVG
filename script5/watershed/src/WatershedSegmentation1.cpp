#include "itkVectorGradientAnisotropicDiffusionImageFilter.h"
#include "itkVectorGradientMagnitudeImageFilter.h"
#include "itkWatershedImageFilter.h"

#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkVectorCastImageFilter.h"
#include "itkScalarToRGBPixelFunctor.h"

#include "QuickView.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 7) {
		cerr << "Missing Parameters " << endl;
		cerr << "Usage: " << argv[0];
		cerr << " inputImage conductanceTerm diffusionIterations lowerThreshold outputScaleLevel gradientMode " << endl;
		return EXIT_FAILURE;
	}

	float conductance = atof(argv[2]);
	int iters = atoi(argv[3]);
	float threshold = atof(argv[4]);
	float level = atof(argv[5]);
	int gradientMode = atoi(argv[6]);

	typedef itk::RGBPixel<unsigned char> RGBPixelType;
	typedef itk::Image<RGBPixelType, 2> RGBImageType;
	typedef itk::Vector<float, 3> VectorPixelType;
	typedef itk::Image<VectorPixelType, 2> VectorImageType;
	typedef itk::Image<itk::IdentifierType, 2> LabeledImageType;
	typedef itk::Image<float, 2> ScalarImageType;

	typedef itk::ImageFileReader<RGBImageType> FileReaderType;
	typedef itk::VectorCastImageFilter<RGBImageType, VectorImageType> CastFilterType;
	typedef itk::VectorGradientAnisotropicDiffusionImageFilter<VectorImageType, VectorImageType> DiffusionFilterType;
	typedef itk::VectorGradientMagnitudeImageFilter<VectorImageType> GradientMagnitudeFilterType;
	typedef itk::WatershedImageFilter<ScalarImageType> WatershedFilterType;

	FileReaderType::Pointer reader = FileReaderType::New();
	reader->SetFileName(argv[1]);

	CastFilterType::Pointer caster = CastFilterType::New();
	caster->SetInput(reader->GetOutput());

	DiffusionFilterType::Pointer diffusion = DiffusionFilterType::New();
	diffusion->SetInput(caster->GetOutput());
	diffusion->SetNumberOfIterations(iters);
	diffusion->SetConductanceParameter(conductance);
	diffusion->SetTimeStep(0.125);

	GradientMagnitudeFilterType::Pointer gradient = GradientMagnitudeFilterType::New();
	gradient->SetInput(diffusion->GetOutput());
	gradient->SetUsePrincipleComponents(gradientMode);

	WatershedFilterType::Pointer watershed = WatershedFilterType::New();
	watershed->SetInput(gradient->GetOutput());
	watershed->SetLevel(level);
	watershed->SetThreshold(threshold);

	typedef itk::Functor::ScalarToRGBPixelFunctor<unsigned long> ColorMapFunctorType;
	typedef itk::UnaryFunctorImageFilter<LabeledImageType, RGBImageType, ColorMapFunctorType> ColorMapFilterType;
	ColorMapFilterType::Pointer colormapper = ColorMapFilterType::New();
	colormapper->SetInput(watershed->GetOutput());

	QuickView viewer;

	string description;

	description = "Watershed\nConductance: " + to_string(conductance) + ", Iters: " + to_string(iters) + "\nThreshold: " + to_string(threshold) + ", Level: " + to_string(level) + "\nGradient Mode: " + to_string(gradientMode);
	viewer.AddImage(colormapper->GetOutput(), true, description);
	description = "Original";
	viewer.AddImage(reader->GetOutput(), true, description);
	viewer.Visualize();

	return EXIT_SUCCESS;
}