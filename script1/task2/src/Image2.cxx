#include "itkImage.h"
#include "itkImageFileReader.h"

int main(int, char * argv[])
{
  const char * filename = argv[1];
  const unsigned int Dimension = 3;

  typedef unsigned char PixelType;
  typedef itk::Image<PixelType, Dimension> ImageType;
  typedef itk::ImageFileReader<ImageType>  ReaderType;
  
  ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName(filename);
  reader->Update();

  ImageType::Pointer image = reader->GetOutput();

  return EXIT_SUCCESS;
}
