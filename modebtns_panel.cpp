#include "modebtns_panel.h"
#include "globalsetting.h"
#include "acpanel.h"
#include <QHBoxLayout>

static AcPanel *pacpanel = nullptr;

ModeBtns_Panel::ModeBtns_Panel(QWidget *parent) : QWidget(parent)
{
    pacpanel = (AcPanel*)this->parentWidget();
    m_qssmanager = new QssManager();

    m_pBtn_cold = new QPushButton(this);
    m_pBtn_cold->setFixedSize(PBTN_SIZE);
    m_pBtn_cold->setObjectName("m_pBtn_cold");
    //m_pBtn_cold->setStyleSheet("border-image: url(:/resources/images/mode/mode_cold.png);");
    m_txt_cold = new QLabel(this);
    m_txt_cold->setFixedSize(PBTN_WIDTH, 20);
    m_txt_cold->setText(QString("制冷"));
    m_txt_cold->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addWidget(m_pBtn_cold);
    vlayout1->addWidget(m_txt_cold);

    m_pBtn_blow = new QPushButton(this);
    m_pBtn_blow->setFixedSize(PBTN_SIZE);
    m_pBtn_blow->setObjectName("m_pBtn_blow");
    //m_pBtn_blow->setStyleSheet("border-image: url(:/resources/images/mode/mode_wind.png);");
    m_txt_blow = new QLabel(this);
    m_txt_blow->setFixedSize(PBTN_WIDTH, 20);
    m_txt_blow->setText(QString("送风"));
    m_txt_blow->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addWidget(m_pBtn_blow);
    vlayout2->addWidget(m_txt_blow);

    m_pBtn_heat = new QPushButton(this);
    m_pBtn_heat->setFixedSize(PBTN_SIZE);
    m_pBtn_heat->setObjectName("m_pBtn_heat");
    //m_pBtn_heat->setStyleSheet("border-image: url(:/resources/images/mode/mode_heat.png);");
    m_txt_heat = new QLabel(this);
    m_txt_heat->setFixedSize(PBTN_WIDTH, 20);
    m_txt_heat->setText(QString("制热"));
    m_txt_heat->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addWidget(m_pBtn_heat);
    vlayout3->addWidget(m_txt_heat);

    m_pBtn_dehumid = new QPushButton(this);
    m_pBtn_dehumid->setFixedSize(PBTN_SIZE);
    m_pBtn_dehumid->setObjectName("m_pBtn_dehumid");
    //m_pBtn_dehumid->setStyleSheet("border-image: url(:/resources/images/mode/mode_dehumid.png);");
    m_txt_dehumid = new QLabel(this);
    m_txt_dehumid->setFixedSize(PBTN_WIDTH, 20);
    m_txt_dehumid->setText(QString("除湿"));
    m_txt_dehumid->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout4 = new QVBoxLayout();
    vlayout4->addWidget(m_pBtn_dehumid);
    vlayout4->addWidget(m_txt_dehumid);

    m_pBtn_auto = new QPushButton(this);
    m_pBtn_auto->setFixedSize(PBTN_SIZE);
    m_pBtn_auto->setObjectName("m_pBtn_auto");
    //m_pBtn_auto->setStyleSheet("border-image: url(:/resources/images/mode/mode_auto.png);");
    m_txt_auto = new QLabel(this);
    m_txt_auto->setFixedSize(PBTN_WIDTH, 20);
    m_txt_auto->setText(QString("智享"));
    m_txt_auto->setAlignment(Qt::AlignHCenter);
    QVBoxLayout *vlayout5 = new QVBoxLayout();
    vlayout5->addWidget(m_pBtn_auto);
    vlayout5->addWidget(m_txt_auto);

    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addSpacing(5);
    hlayout->addLayout(vlayout1);
    hlayout->addStretch();
    hlayout->addLayout(vlayout2);
    hlayout->addStretch();
    hlayout->addLayout(vlayout3);
    hlayout->addStretch();
    hlayout->addLayout(vlayout4);
    hlayout->addStretch();
    hlayout->addLayout(vlayout5);
    hlayout->addSpacing(10);

    m_pBtn_hide = new QPushButton(this);
    m_pBtn_hide->setFixedSize(PBTN_WIDTH, 20);
    m_pBtn_hide->setObjectName("m_pBtn_hide");
    //m_pBtn_hide->setStyleSheet("border-image: url(:/resources/images/homepage/hide.png);");

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(m_pBtn_hide);
    vlayout->setAlignment(m_pBtn_hide, Qt::AlignHCenter);
    m_gbox = new QGroupBox(this);
    m_gbox->setFixedSize(800, 140);
    m_gbox->setLayout(vlayout);

    this->setVisible(false);
    connect(m_pBtn_cold, SIGNAL(clicked()), this, SLOT(on_m_pBtn_cold_clicked()));
    connect(m_pBtn_blow, SIGNAL(clicked()), this, SLOT(on_m_pBtn_blow_clicked()));
    connect(m_pBtn_heat, SIGNAL(clicked()), this, SLOT(on_m_pBtn_heat_clicked()));
    connect(m_pBtn_dehumid, SIGNAL(clicked()), this, SLOT(on_m_pBtn_dehumid_clicked()));
    connect(m_pBtn_auto, SIGNAL(clicked()), this, SLOT(on_m_pBtn_auto_clicked()));
    connect(m_pBtn_hide, SIGNAL(clicked()), this, SLOT(on_m_pBtn_hide_clicked()));

    setStyleSheet((m_qssmanager->LoadQssData(":/resources/qss/modeBtns_panel.qss")));
}

ModeBtns_Panel::~ModeBtns_Panel()
{
    delete m_qssmanager;
}

void ModeBtns_Panel::on_m_pBtn_cold_clicked()
{
    pacpanel->CtrlmodeChanged(AirCondCtrl::Cold);
}

void ModeBtns_Panel::on_m_pBtn_blow_clicked()
{
    pacpanel->CtrlmodeChanged(AirCondCtrl::Blow);
}

void ModeBtns_Panel::on_m_pBtn_heat_clicked()
{
    pacpanel->CtrlmodeChanged(AirCondCtrl::Heat);
}

void ModeBtns_Panel::on_m_pBtn_dehumid_clicked()
{
    pacpanel->CtrlmodeChanged(AirCondCtrl::Dehumid);
}

void ModeBtns_Panel::on_m_pBtn_auto_clicked()
{
    pacpanel->CtrlmodeChanged(AirCondCtrl::AutoMode);
}

void ModeBtns_Panel::on_m_pBtn_hide_clicked()
{
    this->hide();
    pacpanel->showHomebtnsPanel();
}
