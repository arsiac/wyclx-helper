#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);

}

SettingWindow::~SettingWindow()
{
    delete ui;
}

QString SettingWindow::getRewordFontLibrary()
{
    return ui->rewordFontLibraryInput->text();
}

void SettingWindow::setRewordFontLibrary(const QString &path)
{
    ui->rewordFontLibraryInput->setText(path);
}

QString SettingWindow::getDailyFontLibrary()
{
    return ui->dailyFontLibraryLabelInput->text();
}

void SettingWindow::setDailyFontLibrary(const QString &path)
{
    ui->dailyFontLibraryLabelInput->setText(path);
}

int SettingWindow::getDailyFlashDelay()
{
    return ui->dailyFlashDelaySpinBox->value();
}

void SettingWindow::setDailyFlashDelay(int delay)
{
    ui->dailyFlashDelaySpinBox->setValue(delay);
}

bool SettingWindow::getAutoOpenLOG()
{
    return ui->autoOpenLOGCheckBox->checkState() == Qt::Checked;
}

void SettingWindow::setAutoOpenLOG(bool state)
{
    ui->autoOpenLOGCheckBox->setCheckState(state ? Qt::Checked : Qt::Unchecked);
}

void SettingWindow::on_registerPulignButton_clicked()
{
    if (QFile::exists(".\\lib\\dm.dll"))
        {
            ShellExecuteA(NULL, "open", "cmd.exe", "/c regsvr32.exe /s .\\lib\\dm.dll", NULL, SW_HIDE);
            QMessageBox::information(this, "注册", "注册成功，请重启软件");
        }
        else
        {
            QMessageBox::warning(this, "注册", "插件源不存在");
        }
}

void SettingWindow::on_uinstallPulignButton_clicked()
{
    if (QFile::exists(".\\lib\\dm.dll"))
        {
            ShellExecuteA(NULL, "open", "cmd.exe", "/c regsvr32.exe /s /u .\\lib\\dm.dll", NULL, SW_HIDE);
            QMessageBox::information(this, "注销", "注销成功");
        }
        else
        {
            QMessageBox::warning(this, "注销", "插件源不存在");
        }
}
