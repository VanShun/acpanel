#include "winddirbtns_panel.h"
#include "globalsetting.h"
#include "acpanel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

static AcPanel *pacpanel = nullptr;
WindDirBtns_Panel::WindDirBtns_Panel(QWidget *parent) : QWidget(parent)
{
    pacpanel = (AcPanel *)this->parentWidget();
    m_qssmanager = new QssManager();

    m_pBtn_updown = new QPushButton(this);
    m_pBtn_updown->setFixedSize(PBTN_SIZE);
    m_pBtn_updown->setObjectName("m_pBtn_updown");
    //m_pBtn_updown->setStyleSheet("border-image: url(:/resources/images/winddir/windir_updown.png);");
    m_txt_updown = new QLabel(this);
    m_txt_updown->setFixedSize(65, 20);
    m_txt_updown->setText(QString("上下扫风"));
    m_txt_updown->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(m_pBtn_updown);
    vlayout1->addWidget(m_txt_updown);
    vlayout1->setAlignment(m_pBtn_updown, Qt::AlignCenter);

    m_pBtn_leftright = new QPushButton(this);
    m_pBtn_leftright->setFixedSize(PBTN_SIZE);
    m_pBtn_leftright->setObjectName("m_pBtn_leftright");
    //m_pBtn_leftright->setStyleSheet("border-image: url(:/resources/images/winddir/windir_leftright.png);");
    m_txt_leftright = new QLabel(this);
    m_txt_leftright->setFixedSize(65, 20);
    m_txt_leftright->setText(QString("左右扫风"));
    m_txt_leftright->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(m_pBtn_leftright);
    vlayout2->addWidget(m_txt_leftright);
    vlayout2->setAlignment(m_pBtn_leftright, Qt::AlignCenter);

    m_pBtn_cycle = new QPushButton(this);
    m_pBtn_cycle->setFixedSize(PBTN_SIZE);
    m_pBtn_cycle->setObjectName("m_pBtn_cycle");
    //m_pBtn_cycle->setStyleSheet("border-image: url(:/resources/images/winddir/windir_cycle.png);");
    m_txt_cycle = new QLabel(this);
    m_txt_cycle->setFixedSize(PBTN_WIDTH, 20);
    m_txt_cycle->setText(QString("循环"));
    m_txt_cycle->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(m_pBtn_cycle);
    vlayout3->addWidget(m_txt_cycle);

    m_pBtn_hide = new QPushButton(this);
    m_pBtn_hide->setFixedSize(PBTN_WIDTH, 20);
    m_pBtn_hide->setObjectName("m_pBtn_hide");
    //m_pBtn_hide->setStyleSheet("border-image: url(:/resources/images/homepage/hide.png);");


    QHBoxLayout *hlayout = new QHBoxLayout();
    //hlayout->addSpacing(10);
    hlayout->addStretch();
    hlayout->addLayout(vlayout1);
    hlayout->addStretch();
    hlayout->addLayout(vlayout2);
    hlayout->addStretch();
    hlayout->addLayout(vlayout3);
    hlayout->addStretch();
    //hlayout->addSpacing(10);


    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_pBtn_hide);
    vlayout->setAlignment(m_pBtn_hide, Qt::AlignHCenter);
    m_gbox = new QGroupBox(this);
    m_gbox->setFixedSize(780, 140);
    m_gbox->setLayout(vlayout);

    this->setVisible(false);
    connect(m_pBtn_updown, SIGNAL(clicked()), this, SLOT(on_m_pBtn_updown_clicked()));
    connect(m_pBtn_leftright, SIGNAL(clicked()), this, SLOT(on_m_pBtn_leftright_clicked()));
    connect(m_pBtn_cycle, SIGNAL(clicked()), this, SLOT(on_m_pBtn_cycle_clicked()));
    connect(m_pBtn_hide, SIGNAL(clicked()), this, SLOT(on_m_pBtn_hide_clicked()));

    setStyleSheet(m_qssmanager->LoadQssData(":/resources/qss/winddirBtns_panel.qss"));
}

WindDirBtns_Panel::~WindDirBtns_Panel()
{
    delete m_qssmanager;
}

void WindDirBtns_Panel::mousePressEvent(QMouseEvent *event)
{
    m_presspoint = event->pos();
}

void WindDirBtns_Panel::mouseReleaseEvent(QMouseEvent *event)
{
    m_releasepoint = event->pos();
    if (m_releasepoint.y() > m_presspoint.y()) {   //下滑隐藏菜单
        this->hide();
        pacpanel->showHomebtnsPanel();
    }
}

void WindDirBtns_Panel::on_m_pBtn_updown_clicked()
{
    pacpanel->WindDirChanged(AirCondCtrl::WindDir_UpDown);
}

void WindDirBtns_Panel::on_m_pBtn_leftright_clicked()
{
    pacpanel->WindDirChanged(AirCondCtrl::WindDir_LeftRight);
}

void WindDirBtns_Panel::on_m_pBtn_cycle_clicked()
{
    pacpanel->WindDirChanged(AirCondCtrl::WindDir_Auto);
}

void WindDirBtns_Panel::on_m_pBtn_hide_clicked()
{
    this->hide();
    pacpanel->showHomebtnsPanel();
}
