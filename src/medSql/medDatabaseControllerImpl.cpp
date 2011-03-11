#include "medDatabaseControllerImpl.h"

#include <QtCore>
#include <QtGui>

#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractDataReader.h>
#include <dtkCore/dtkAbstractDataWriter.h>
#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <medCore/medMessageController.h>
#include <medCore/medStorage.h>

#include "medDatabaseImporter.h"
#include "medDatabaseExporter.h"
#include "medDatabaseReader.h"


QSqlDatabase *medDatabaseControllerImpl::database(void)
{
    return &m_database;
}

bool medDatabaseControllerImpl::createConnection(void)
{
    medStorage::mkpath(medStorage::dataLocation() + "/");

    if (this->m_database.databaseName().isEmpty())
        this->m_database = QSqlDatabase::addDatabase("QSQLITE");
    this->m_database.setDatabaseName(medStorage::dataLocation() + "/" + "db");

    if (!m_database.open()) {
        qDebug() << DTK_COLOR_FG_RED << "Cannot open database: Unable to establish a database connection." << DTK_NO_COLOR;
        return false;
    }
    else
    {
        qDebug() << "Database opened at: " << m_database.databaseName();
        m_isConnected = true;
    }

    createPatientTable();
    createStudyTable();
    createSeriesTable();
    createImageTable();

    return true;
}

bool medDatabaseControllerImpl::closeConnection(void)
{
    m_database.close();
    m_isConnected = false;
    return true;
}

medDataIndex medDatabaseControllerImpl::indexForPatient(int id)
{
    return medDataIndex(id);
}

medDataIndex medDatabaseControllerImpl::indexForStudy(int id)
{
    QSqlQuery query(m_database);

    QVariant patientId = -1;

    query.prepare("SELECT patient FROM study WHERE id = :id");
    query.bindValue(":id", id);
    if(!query.exec())
        qDebug() << DTK_COLOR_FG_RED << query.lastError() << DTK_NO_COLOR;

    if(query.first())
        patientId = query.value(0);

    return medDataIndex(patientId.toInt(), id);
}

medDataIndex medDatabaseControllerImpl::indexForSeries(int id)
{
    QSqlQuery query(m_database);

    QVariant patientId = -1;
    QVariant   studyId = -1;

    query.prepare("SELECT study FROM series WHERE id = :id");
    query.bindValue(":id", id);
    if(!query.exec())
        qDebug() << DTK_COLOR_FG_RED << query.lastError() << DTK_NO_COLOR;

    if(query.first())
        studyId = query.value(0);

    query.prepare("SELECT patient FROM study WHERE id = :id");
    query.bindValue(":id", studyId);
    if(!query.exec())
        qDebug() << DTK_COLOR_FG_RED << query.lastError() << DTK_NO_COLOR;

    if(query.first())
        patientId = query.value(0);

    return medDataIndex(patientId.toInt(), studyId.toInt(), id);
}

medDataIndex medDatabaseControllerImpl::indexForImage(int id)
{
    QSqlQuery query(m_database);

    QVariant patientId = -1;
    QVariant   studyId = -1;
    QVariant  seriesId = -1;

    query.prepare("SELECT series FROM image WHERE id = :id");
    query.bindValue(":id", id);
    if(!query.exec())
        qDebug() << DTK_COLOR_FG_RED << query.lastError() << DTK_NO_COLOR;

    if(query.first())
        seriesId = query.value(0);

    query.prepare("SELECT study FROM series WHERE id = :id");
    query.bindValue(":id", seriesId);
    if(!query.exec())
        qDebug() << DTK_COLOR_FG_RED << query.lastError() << DTK_NO_COLOR;

    if(query.first())
        studyId = query.value(0);

    query.prepare("SELECT patient FROM study WHERE id = :id");
    query.bindValue(":id", studyId);
    if(!query.exec())
        qDebug() << DTK_COLOR_FG_RED << query.lastError() << DTK_NO_COLOR;

    if(query.first())
        patientId = query.value(0);

    return medDataIndex(patientId.toInt(), studyId.toInt(), seriesId.toInt(), id);
}

medDataIndex medDatabaseControllerImpl::import(const QString& file)
{
    Q_UNUSED(file);

    emit(updated(medDataIndex()));

    return medDataIndex();
}

medDataIndex medDatabaseControllerImpl::import( const dtkAbstractData& data )
{
    Q_UNUSED(data);

    return medDataIndex();
}

QSharedPointer<dtkAbstractData> medDatabaseControllerImpl::read(const medDataIndex& index) const
{
    QScopedPointer<medDatabaseReader> reader(new medDatabaseReader(index));

    connect(reader.data(), SIGNAL(progressed(int)), medMessageController::instance(), SLOT(setProgress(int)));
    connect(reader.data(), SIGNAL(success(QObject *)), medMessageController::instance(), SLOT(remove(QObject *)));
    connect(reader.data(), SIGNAL(failure(QObject *)), medMessageController::instance(), SLOT(remove(QObject *)));
    connect(reader.data(), SIGNAL(success(QObject *)), reader.data(), SLOT(deleteLater()));
    connect(reader.data(), SIGNAL(failure(QObject *)), reader.data(), SLOT(deleteLater()));

    medMessageController::instance()->showProgress(reader.data(), "Opening database item");

    dtkAbstractData* data = reader->run();
    QSharedPointer<dtkAbstractData> ret(data);
    return ret;
}

QSharedPointer<dtkAbstractData> medDatabaseControllerImpl::read(int patientId, int studyId, int seriesId)
{
    return read(medDataIndex(patientId, studyId, seriesId));
}

QSharedPointer<dtkAbstractData> medDatabaseControllerImpl::read(int patientId, int studyId, int seriesId, int imageId)
{
    return read(medDataIndex(patientId, studyId, seriesId, imageId));
}

void medDatabaseControllerImpl::createPatientTable(void)
{
    QSqlQuery query(*(this->database()));
    query.exec(
        "CREATE TABLE patient ("
        " id       INTEGER PRIMARY KEY,"
        " name        TEXT,"
        " thumbnail   TEXT,"
        " birthdate   TEXT,"
        " gender      TEXT"
        ");"
        );
}

void medDatabaseControllerImpl::createStudyTable(void)
{
    QSqlQuery query(*(this->database()));

    query.exec(
        "CREATE TABLE study ("
        " id        INTEGER      PRIMARY KEY,"
        " patient   INTEGER," // FOREIGN KEY
        " name         TEXT,"
        " uid          TEXT,"
        " thumbnail    TEXT"
        ");"
        );
}

void medDatabaseControllerImpl::createSeriesTable(void)
{
    QSqlQuery query(*(this->database()));
    query.exec(
        "CREATE TABLE series ("
        " id       INTEGER      PRIMARY KEY,"
        " study    INTEGER," // FOREIGN KEY
        " size     INTEGER,"
        " name            TEXT,"
        " path            TEXT,"
        " uid             TEXT,"
        " orientation     TEXT,"
        " seriesNumber    TEXT,"
        " sequenceName    TEXT,"
        " sliceThickness  TEXT,"
        " rows            TEXT,"
        " columns         TEXT,"
        " thumbnail       TEXT,"
        " age             TEXT,"
        " description     TEXT,"
        " modality        TEXT,"
        " protocol        TEXT,"
        " comments        TEXT,"
        " status          TEXT,"
        " acquisitiondate TEXT,"
        " importationdate TEXT,"
        " referee         TEXT,"
        " performer       TEXT,"
        " institution     TEXT,"
        " report          TEXT"
        ");"
        );
}

void medDatabaseControllerImpl::createImageTable(void)
{
    QSqlQuery query(*(this->database()));
    query.exec(
        "CREATE TABLE image ("
        " id         INTEGER      PRIMARY KEY,"
        " series     INTEGER," // FOREIGN KEY
        " size       INTEGER,"
        " name          TEXT,"
        " path          TEXT,"
        " instance_path TEXT,"
        " thumbnail     TEXT,"
        " slice      INTEGER"
        ");"
        );
}

bool medDatabaseControllerImpl::moveDatabase( QString newLocation)
{
    bool res = true;

    QString oldLocation = medStorage::dataLocation();

    // now copy all the images and thumbnails
    QStringList sourceList;
    medStorage::recurseAddDir(QDir(oldLocation), sourceList);

    // create destination filelist
    QStringList destList;
    if (!medStorage::createDestination(sourceList,destList,oldLocation, newLocation))
    {
        res = false;
    }
    else
    {
        // now copy
        if (!medStorage::copyFiles(sourceList, destList, emitter))
            res = false;
    }

    if (res)
        emit copyMessage(tr("copying database: success"), Qt::AlignBottom, QColor((Qt::white)));
    else
        emit copyMessage(tr("copying database: failure"), Qt::AlignBottom, QColor((Qt::red)));


    // only switch to the new location if copying succeeded
    if( res )
    {
        // close connection if necessary
        bool needsRestart = false;
        if (this->isConnected())
        {
            this->closeConnection();
            needsRestart = true;
        }

        // now update the datastorage path and make sure to reconnect
        medStorage::setDataLocation(newLocation);

        // restart if necessary
        if (needsRestart)
        {
            qDebug() << "Restarting connection...";
            this->createConnection();
        }

        // now delete the old archive
        if(medStorage::removeDir(oldLocation, emitter))
            emit copyMessage(tr("deleting old database: success"), Qt::AlignBottom, QColor((Qt::white)));
        else
            emit copyMessage(tr("deleting old database: failure"), Qt::AlignBottom, QColor((Qt::red)));

    }

    if (res)
        emit copyMessage(tr("relocating database successful"), Qt::AlignBottom, QColor((Qt::white)));
    else
        emit copyMessage(tr("relocating database failed"), Qt::AlignBottom, QColor((Qt::red)));
    return res;
}

bool medDatabaseControllerImpl::isConnected()
{
    return m_isConnected;
}

medDatabaseControllerImpl::medDatabaseControllerImpl()
{
    m_isConnected = false;
    emitter = new SigEmitter();
    connect(emitter, SIGNAL(message(QString)), this, SLOT(forwardMessage(QString)));
}

medDatabaseControllerImpl::~medDatabaseControllerImpl()
{
    delete emitter;
}

void medDatabaseControllerImpl::forwardMessage( QString msg)
{
    copyMessage(msg, Qt::AlignBottom, QColor(Qt::white));
}
