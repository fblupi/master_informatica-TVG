#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkCastImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkNormalizeImageFilter.h"

using namespace std;

int main (int argc, char * argv[])
{
  if (argc < 2) {
    cerr << "Usage: " << endl;
    cerr << argv[0] << "   inputImageFile " << endl;
    return EXIT_FAILURE;
  }

  typedef unsigned char InputPixelType;
  typedef float OutputPixelType;

  typedef itk::Image<InputPixelType, 3> InputImageType;
  typedef itk::Image<OutputPixelType, 3> OutputImageType;

  typedef itk::ImageFileReader<InputImageType> ReaderType;

  typedef itk::CastImageFilter<InputImageType, OutputImageType> CastFilterType;

  typedef itk::RescaleIntensityImageFilter<InputImageType, OutputImageType> RescaleFilterType;

  typedef itk::ShiftScaleImageFilter<InputImageType, OutputImageType> ShiftScaleFilterType;

  typedef itk::NormalizeImageFilter<InputImageType, OutputImageType> NormalizeFilterType;

  ReaderType::Pointer reader = ReaderType::New();

  CastFilterType::Pointer castFilter = CastFilterType::New();
  RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  ShiftScaleFilterType::Pointer shiftFilter = ShiftScaleFilterType::New();
  NormalizeFilterType::Pointer normalizeFilter = NormalizeFilterType::New();

  reader->SetFileName(argv[1]);

  castFilter->SetInput(reader->GetOutput());
  shiftFilter->SetInput(reader->GetOutput());
  rescaleFilter->SetInput(reader->GetOutput());
  normalizeFilter->SetInput(reader->GetOutput());

  rescaleFilter->SetOutputMinimum(10);
  rescaleFilter->SetOutputMaximum(250);

  shiftFilter->SetScale(1.2);
  shiftFilter->SetShift(25);

  castFilter->Update();
  shiftFilter->Update();
  rescaleFilter->Update();
  normalizeFilter->Update();

  return EXIT_SUCCESS;
}
