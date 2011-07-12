#include "msegSeedPointAnnotation.h"

#include "msegSeedPointAnnotationData.h"
#include <QPainter>

namespace mseg {

SeedPointAnnotation::SeedPointAnnotation(QGraphicsItem * parent /* = 0 */) :
    medAnnotationGraphicsObject( parent),
    m_isInitialized(false)
{
}


SeedPointAnnotation::~SeedPointAnnotation(void)
{
}

void SeedPointAnnotation::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget /*= 0 */ )
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if ( !m_isInitialized )
        initializeSceneCoordinates();


    painter->save();

    painter->setPen( seedPointAnnotationData()->color() );
    painter->setRenderHints( 
        QPainter::Antialiasing          |
        QPainter::SmoothPixmapTransform |
        QPainter::TextAntialiasing      );

    qreal radiusScene =seedPointAnnotationData()->radiusScene();
    painter->drawEllipse( QPointF( 0.0, 0.0 ), radiusScene, radiusScene );

    painter->drawLine(-radiusScene,0,radiusScene,0 );
    painter->drawLine(0, -radiusScene, 0,radiusScene);

    painter->restore();
}

void SeedPointAnnotation::initializeSceneCoordinates()
{
    prepareGeometryChange();
    this->setPos( this->worldToScene( seedPointAnnotationData()->centerWorld() ) );
    m_isInitialized = true;
}

QRectF SeedPointAnnotation::boundingRect( void ) const
{
    const qreal penWidth = 1;
    const qreal radiusScene = seedPointAnnotationData()->radiusScene();
    return QRectF(-radiusScene - penWidth / 2, -radiusScene - penWidth / 2,
        radiusScene*2 + penWidth, radiusScene*2 + penWidth);
}

const SeedPointAnnotationData *SeedPointAnnotation::seedPointAnnotationData() const
{
    return qobject_cast<const mseg::SeedPointAnnotationData *>(this->annotationData());
}

QString SeedPointAnnotation::s_description()
{
    static const QString desc = "mseg::SeedPointAnnotation";
    return desc;
}

medAnnotationGraphicsObject * SeedPointAnnotation::s_create()
{
    return new SeedPointAnnotation;
}


} // namespace mseg
