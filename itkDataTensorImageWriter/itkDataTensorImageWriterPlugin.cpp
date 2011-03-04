// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#include "itkMetaDataTensorImageWriter.h"
#include "itkDataTensorImageWriterPlugin.h"

#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// itkDataTensorImageWriterPluginPrivate
// /////////////////////////////////////////////////////////////////

class itkDataTensorImageWriterPluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// itkDataTensorImageWriterPlugin
// /////////////////////////////////////////////////////////////////

itkDataTensorImageWriterPlugin::itkDataTensorImageWriterPlugin(QObject *parent) : dtkPlugin(parent), d(new itkDataTensorImageWriterPluginPrivate)
{

}

itkDataTensorImageWriterPlugin::~itkDataTensorImageWriterPlugin(void)
{
    delete d;

    d = NULL;
}

bool itkDataTensorImageWriterPlugin::initialize(void)
{
    if(!itkMetaDataTensorImageWriter::registered())
    	dtkWarning() << "Unable to register itkMetaDataTensorImageWriter type";

    return true;
}

bool itkDataTensorImageWriterPlugin::uninitialize(void)
{
    return true;
}

QString itkDataTensorImageWriterPlugin::name(void) const
{
    return "itkDataTensorImageWriterPlugin";
}

QString itkDataTensorImageWriterPlugin::description(void) const
{
    return "ITK tensor data image writers";
}

QStringList itkDataTensorImageWriterPlugin::tags(void) const
{
    return QStringList() << "itk" << "data" << "tensor" << "image" << "writers";
}

QStringList itkDataTensorImageWriterPlugin::types(void) const
{
    return QStringList() << "itkMetaDataTensorImageWriter";
}

Q_EXPORT_PLUGIN2(itkDataTensorImageWriterPlugin, itkDataTensorImageWriterPlugin)
