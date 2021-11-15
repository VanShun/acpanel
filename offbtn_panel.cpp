#include "offbtn_panel.h"
#include <QHBoxLayout>
#include "acpanel.h"

static AcPanel *pacpanel = nullptr;
OffBtn_Panel::OffBtn_Panel(QWidget *parent) : QWidget(parent)
{
    pacpanel = (AcPanel*)this->parentWidget();
    m_pBtn_poweroff = new QPushButton(this);
    m_pBtn_poweroff->setFixedSize(70, 70);
    m_pBtn_poweroff->setStyleSheet("border-image: url(:/resources/images/homepage/poweroff.png);");
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(m_pBtn_poweroff);
    m_gbox = new QGroupBox(this);
    m_gbox->setFixedSize(800, 110);
    m_gbox->setLayout(hlayout);

    connect(m_pBtn_poweroff, SIGNAL(clicked()), this, SLOT(on_m_pBtn_poweroff_clidked()));
}

OffBtn_Panel::~OffBtn_Panel()
{

}

void OffBtn_Panel::on_m_pBtn_poweroff_clidked()
{
    this->hide();
    pacpanel->showHomebtnsPanel();
    //pacpanel->showTimersetPanel(true);
}
