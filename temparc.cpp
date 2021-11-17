#include "temparc.h"
#include "qmath.h"
#include "acpanel.h"
#include <QDebug>

static AcPanel *pacpanel = nullptr;

TempArc::TempArc(QWidget *parent) : QWidget(parent)
{
    pacpanel = (AcPanel*)this->parentWidget();
    m_startAngle = 240;  //0刻度的起始角度
    m_endAngle = 300;
    m_foreground = Qt::white;
    m_background = Qt::black; //定义背景颜色
    m_minValue = 18;
    m_maxValue = 30;
    m_scaleMajor = 12;//刻度
    m_scaleMinor = 2; //每个刻度分成2个分度
    m_units = "℃";
    m_title = "温度表";
    m_cvalue = 30; //默认的当前温度
    m_svalue = 23; //默认的设置温度
    arcWidth = 6;  //弧线宽度
    m_showsvalue = false;
    resize(200, 200);
}

TempArc::~TempArc()
{
}

void TempArc::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); 	/* 使用反锯齿(如果可用) */
    painter.translate(width() / 2, height() / 2);	/* 坐标变换为窗体中心 */
    int side = qMin(width(), height());
    //qDebug() << "-----paintevent  size:" << width() << height() << endl;
    painter.scale(side / 200.0, side / 200.0);		/* 比例缩放 */
    drawCrown(&painter);
    //drawScale(&painter);
    drawArc(&painter);
    //drawScaleNum(&painter);
    //drawScale(&painter);
    drawNumericValue(&painter);				    	/* 画数字显示 */
}

void TempArc::mousePressEvent(QMouseEvent *event)
{
    if (!m_showsvalue) return;
    m_presspoint = event->pos();
}

void TempArc::mouseReleaseEvent(QMouseEvent *event)
{
    bool grow = false;
    double value;

    if (!m_showsvalue) return;

    m_releasepoint = event->pos();
    double deltax = m_releasepoint.x() - m_presspoint.x();
    double deltay = m_releasepoint.y() - m_presspoint.y();
    double distant = qSqrt(deltax * deltax + deltay * deltay);

    /* 判断鼠标的移动是在按圆弧顺时针(增加温度设置值)还是逆时针*/
    if (m_releasepoint.x() < width() / 2) {
        if (deltay < 0) {
            grow = true;
        }
        if (m_presspoint.x() > width() / 2) {
            grow = false;
        }
    } else if (m_releasepoint.x() > width() / 2) {
        if (deltay > 0) {
            grow = true;
        }
        if (m_presspoint.x() < width() / 2) {
            grow = true;
        }
    }
    if (grow) {
        value = m_svalue + (distant / (2 * 3.14 * 84 * 5 / 6)) * m_scaleMajor * m_scaleMinor;
    } else {
        value = m_svalue - (distant / (2 * 3.14 * 84 * 5 / 6)) * m_scaleMajor * m_scaleMinor;
    }
    /* 只取到0.5 */
    if (value - (int)value > 0.5) {
        value = (int)value + 0.5;
    } else {
        value = (int)value;
    }
    if (value > m_maxValue) value = m_maxValue;
    if (value < m_minValue) value = m_minValue;
    updateAngle_S(value);
    pacpanel->updateSettedTemp(value);
}

void TempArc::drawCrown(QPainter *painter)
{
    painter->save();
    int radius = 100;

    //painter->setBrush(QColor(0x87, 0xce, 0xfd, 0x64));
    painter->setBrush((Qt::white));
    //painter->setPen(Qt::gray);
    //painter->drawEllipse(-radius, -radius, radius << 1, radius << 1);
    QPen pen;
    pen.setColor(QColor(0xdcdcdc));
    pen.setWidthF(14);
    painter->setPen(pen);
    //painter->drawEllipse(-92, -92, 184, 184);
    painter->drawEllipse(-(radius - 10), -(radius - 10), 2 * (radius - 10), 2 * (radius - 10));
    //painter->drawEllipse(-(radius - 2), -(radius - 2), 2 * (radius - 2), 2 * (radius - 2));

    QRectF rect = QRectF(-(radius - 2), -(radius - 2), 2 * (radius - 2), 2 * (radius - 2));
    painter->setPen(QColor(0x64, 0x95, 0xed));
    painter->drawArc(rect, 90 * 16, 90 *16);
    painter->drawArc(rect, 270 * 16, 100 *16);
    painter->restore();
}

void TempArc::drawArc(QPainter *painter)
{
    int radius = 84 - arcWidth;
    painter->save();
    painter->setBrush(Qt::NoBrush);

    QPen pen;
    pen.setWidthF(arcWidth);
    pen.setCapStyle(Qt::FlatCap);

    //计算总范围角度,当前值范围角度,剩余值范围角度
    double angleAll = 360.0 - m_endAngle + m_startAngle;
    double angleCurrent = angleAll * ((m_svalue - m_minValue) / (m_maxValue - m_minValue));
    double angleOther = angleAll - angleCurrent;
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    /* 由于画圆弧是逆时针画，而我们使用的仪表进度都是顺时针的
     * 所以这里讨巧一下，实际使用的时候圆弧背景和进度条反着来 */

    //绘制圆弧背景
    pen.setColor(QColor(0x64, 0x95, 0xed));
    painter->setPen(pen);
    painter->drawArc(rect, (m_endAngle ) * 16, angleAll * 16);

    //绘制圆弧进度
    //pen.setColor(Qt::white);
    pen.setColor(QColor(0xdcdcdc));
    painter->setPen(pen);
    if (m_showsvalue) {
        painter->drawArc(rect, (m_endAngle) * 16, angleOther * 16);
    } else {
        painter->drawArc(rect, m_endAngle * 16, angleAll * 16);
    }
    painter->restore();
}

void TempArc::drawScale(QPainter *painter)
{
    painter->save();
    painter->rotate(360 - m_startAngle);
    int steps = (m_scaleMajor * m_scaleMinor); //相乘后的值是分的份数
    double angleStep = (360.0 + m_startAngle - m_endAngle) / steps;  //每一个份数的角度

    QPen pen ;
    double tmpVal;
    //pen.setColor(Qt::green);
    for (int i = 0; i <= steps; i++) {
        tmpVal = 1.0 * i *((m_maxValue - m_minValue) / m_scaleMajor) + m_minValue;
        //to change the color gradually for better visual effect
        pen.setColor(QColor(0 + tmpVal * 3, 0 + tmpVal * 1, 255 - tmpVal * 2));
        if (i % m_scaleMinor == 0) {     //整数刻度显示加粗
            pen.setWidth(1);             //设置线宽
            painter->setPen(pen);
            painter->drawLine(82, 0, 92, 0);
       } else {
           pen.setWidth(0);
           painter->setPen(pen);
           painter->drawLine(87, 0, 92, 0);
       }
       painter->rotate(angleStep);
    }
    painter->restore();
}

void TempArc::drawNumericValue(QPainter *painter)
{
    if (m_showsvalue) {
        QFont font = this->font();
        font.setPointSizeF(28);
        //font.setBold(true);
        painter->setPen(Qt::black);
        painter->setFont(font);

        QString strstemp  =  QString("%1 %2").arg(m_svalue).arg(m_units);
        QRectF stextRect(-100, -30, 100 * 2, 50);
        painter->drawText(stextRect, Qt::AlignCenter, strstemp);

        int radius = 64 - arcWidth * 3 / 2;
        double angle = 25;
        painter->drawLine(-radius * cos(angle * 3.14 / 180), radius * sin(angle * 3.14 / 180), radius * cos(angle * 3.14 / 180), radius * sin(angle * 3.14 / 180));
        QString str  =  QString("室温%1 %2").arg(m_cvalue).arg(m_units);
        //QFont font = this->font();
        font.setPointSizeF(12);
        //QFontMetricsF fm(font);
        //double w = fm.size(Qt::TextSingleLine,str).width();
        painter->setPen(Qt::black);
        painter->setFont(font);
        QRectF textRect(-radius * cos(angle * 3.14 / 180), radius * sin(angle * 3.14 / 180), radius * 2, 20);
        painter->drawText(textRect, Qt::AlignCenter, str);
    } else {
        QFont font = this->font();
        font.setPointSizeF(35);
        painter->setPen(Qt::black);
        painter->setFont(font);

        QString strstemp  =  QString("%1 %2").arg(m_cvalue).arg(m_units);
        QRectF stextRect(-100, -40, 100 * 2, 60);
        painter->drawText(stextRect, Qt::AlignCenter, strstemp);

        QRectF textRect(-100, 10, 100 * 2, 50);
        font.setPointSizeF(15);
        painter->setFont(font);
        QString str = QString("室温");
        painter->drawText(textRect, Qt::AlignCenter, str);
    }
}

void TempArc::updateAngle_C(const double value)
{
    if (value > m_maxValue || value < m_minValue) return;
    m_cvalue = value;
    update();  //repaint
}

void TempArc::updateAngle_S(const double value)
{
    if (value > m_maxValue || value < m_minValue) return;
    m_svalue = value;
    update();  //repaint
}

void TempArc::changeTheme(QColor foreground, QColor background)
{
    m_foreground = foreground;
    m_background = background;
    update();
}

bool TempArc::svalueVisible()
{
    return m_showsvalue;
}

void TempArc::setSvalueVisible(bool visible)
{
    m_showsvalue = visible;
}
