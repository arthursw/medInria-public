// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "itkDataTensorImageReaderPlugin.h"
#include "itkNrrdDataTensorImageReader.h"
#include "itkNiftiDataTensorImageReader.h"
#include "itkMetaDataTensorImageReader.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// itkDataTensorImageReaderPluginPrivate
// /////////////////////////////////////////////////////////////////

class itkDataTensorImageReaderPluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// itkDataTensorImageReaderPlugin
// /////////////////////////////////////////////////////////////////

itkDataTensorImageReaderPlugin::itkDataTensorImageReaderPlugin(QObject *parent) : dtkPlugin(parent), d(new itkDataTensorImageReaderPluginPrivate)
{

}

itkDataTensorImageReaderPlugin::~itkDataTensorImageReaderPlugin(void)
{
    delete d;

    d = NULL;
}

bool itkDataTensorImageReaderPlugin::initialize(void)
{
    if(!itkMetaDataTensorImageReader::registered())  dtkWarning() << "Unable to register itkMetaDataTensorImageReader type";
    if(!itkNiftiDataTensorImageReader::registered()) dtkWarning() << "Unable to register itkNiftiDataTensorImageReader type";
    if(!itkNrrdDataTensorImageReader::registered())  dtkWarning() << "Unable to register itkNrrdDataTensorImageReader type";
  
    return true;
}

bool itkDataTensorImageReaderPlugin::uninitialize(void)
{
    return true;
}

QString itkDataTensorImageReaderPlugin::name(void) const
{
    return "itkDataTensorImageReaderPlugin";
}

QString itkDataTensorImageReaderPlugin::description(void) const
{
    return "ITK tensor data image readers";
}

QStringList itkDataTensorImageReaderPlugin::tags(void) const
{
    return QStringList() << "itk" << "data" << "tensor" << "image" << "reader";
}

QStringList itkDataTensorImageReaderPlugin::types(void) const
{
    return QStringList() << "itkMetaDataTensorImageReader"
			 << "itkNiftiDataTensorImageReader"
			 << "itkNrrdDataTensorImageReader";
}

Q_EXPORT_PLUGIN2(itkDataTensorImageReaderPlugin, itkDataTensorImageReaderPlugin)
