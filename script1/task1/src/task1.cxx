#include "itkImage.h"
#include <iostream>

unsing namespace std;

int main()
{
  typedef itk::Image<unsigned short, 3> ImageType;

  ImageType::Pointer image = ImageType::New();

  cout << "ITK Hello World!" << endl;

  return EXIT_SUCCESS;
}