#include "medSettingsWidget.h"

#include <QWidget>
#include <medCore/medMessageController.h>


class medSettingsWidgetPrivate {

public:
    QWidget* Parent;
    QString section;
    medSettingsWidgetPrivate();
    ~medSettingsWidgetPrivate();
};

medSettingsWidgetPrivate::medSettingsWidgetPrivate()
{
    this->section = QString();
}

medSettingsWidgetPrivate::~medSettingsWidgetPrivate()
{
}

medSettingsWidget::medSettingsWidget(QWidget *parent) : QWidget(parent), d(new medSettingsWidgetPrivate())
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    connect(this,SIGNAL(showError(QObject*,const        QString&,unsigned int)),
        medMessageController::instance(),SLOT(showError (QObject*,const QString&,unsigned int)));

}


bool medSettingsWidget::validate()
{
    return false;
}

bool medSettingsWidget::save()
{
    if (!validate())
    {
        qDebug()<<"validation of section"<< d->section <<
                "failed";
        QString error = "Error in validation of section";
        error.append(d->section);
        emit (showError(this,error,3));
        return false;
    }
    else
    {
        //do the saving
        qDebug()<<"validation of section"<< d->section <<
                "successful";
        return true;
    }
}

void medSettingsWidget::setSection(QString section)
{
    d->section = section;
}

const QString& medSettingsWidget::section()const
{
    return d->section;
}


