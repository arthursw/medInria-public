#ifndef MEDVIEWERCONFIGURATIONREGISTRATION_H
#define MEDVIEWERCONFIGURATIONREGISTRATION_H


#include <QtCore>

#include <medViewerConfiguration.h>

class medTabbedViewContainers;
class medViewerConfigurationRegistrationPrivate;

class medViewerConfigurationRegistration : public medViewerConfiguration
{
    Q_OBJECT

public:
     medViewerConfigurationRegistration(QWidget *parent = 0);
    ~medViewerConfigurationRegistration(void);

    virtual QString identifier()  const;
    virtual QString description() const;

    void setupViewContainerStack ();

public slots:
    void patientChanged(int patientId);

private:
    medViewerConfigurationRegistrationPrivate *d;
};

#endif // MEDVIEWERCONFIGURATIONREGISTRATION_H
