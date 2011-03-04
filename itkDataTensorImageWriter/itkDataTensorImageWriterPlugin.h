// /////////////////////////////////////////////////////////////////
// Generated by dtkPluginGenerator
// /////////////////////////////////////////////////////////////////

#ifndef ITKDATATENSORIMAGEWRITERPLUGIN_H
#define ITKDATATENSORIMAGEWRITERPLUGIN_H

#include <dtkCore/dtkPlugin.h>

#include "itkDataTensorImageWriterPluginExport.h"

class ITKDATATENSORIMAGEWRITERPLUGIN_EXPORT itkDataTensorImageWriterPluginPrivate;

class ITKDATATENSORIMAGEWRITERPLUGIN_EXPORT itkDataTensorImageWriterPlugin : public dtkPlugin
{
    Q_OBJECT
    Q_INTERFACES(dtkPlugin)

public:
     itkDataTensorImageWriterPlugin(QObject *parent = 0);
    ~itkDataTensorImageWriterPlugin(void);

    virtual bool initialize(void);
    virtual bool uninitialize(void);

    virtual QString name(void) const;
    virtual QString description(void) const;

    virtual QStringList tags(void) const;
    virtual QStringList types(void) const;

private:
     itkDataTensorImageWriterPluginPrivate *d;
};

#endif
