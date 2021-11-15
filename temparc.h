#ifndef TEMPARC_H
#define TEMPARC_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>

class TempArc : public QWidget
{
    Q_OBJECT
public:
    explicit TempArc(QWidget *parent = nullptr);

    ~TempArc();
public:
    void drawCrown(QPainter *painter);       //draw crown

    void drawArc(QPainter *painter);         //draw arc

    void drawScale(QPainter *painter);

    void drawNumericValue(QPainter *painter);//draw number and unit

    void updateAngle_C(const double value);

    void updateAngle_S(const double value);

    void changeTheme(QColor foreground, QColor background);

    bool svalueVisible();

    void setSvalueVisible(bool visible);
protected:

    virtual void paintEvent(QPaintEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QColor m_crownColor;
    QColor m_foreground;
    QColor m_background;
    QString m_units;
    QString m_title;

    int m_maxValue, m_minValue;
    int m_scaleMajor;
    int m_scaleMinor;
    int m_startAngle,m_endAngle;
    int arcWidth;

    double m_cvalue;   //current value
    double m_svalue;   //set value
    bool m_showsvalue; //when poweroff, no svalue to show

    QPoint m_presspoint, m_releasepoint;
};

#endif // TEMPARC_H
