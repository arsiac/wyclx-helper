#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(const QString &configFilePath, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dm = new Dm::dmsoft;
    settings = new QSettings(configFilePath, QSettings::IniFormat);
    settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
    wc = new gc::WindowControl("Messiah_Game");
    script = NULL;
    instancesLength = 0;
    stateStopStyle  = "border-width:0;border-radius:5px;background-color:#FF6347;color:#fff;padding:2px 5px;";
    stateStartStyle = "border-width:0;border-radius:5px;background-color:#32CD32;color:#fff;padding:2px 5px;";
    this->scriptThread.start();

    // 是否注册
    QString version = dm->Ver();
    if (version.isEmpty())
    {
        rewordError("前往设置注册插件后重启软件");
    }

    if (!initInstances())
    {
        this->isInitSuccess = false;
    }
    else
    {
        this->isInitSuccess = true;
        initUiData();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dm;
    delete settings;
    if (!script)
    {
        delete script;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    switch (QMessageBox::question(this, "一梦江湖助手", "确定要退出脚本吗?", QMessageBox::No | QMessageBox::Yes))
    {
    case QMessageBox::No:
        event->ignore();
        break;
    case QMessageBox::Yes:
        this->writeSettings();
        this->scriptThread.quit();
        event->accept();
    default:
        break;
    }
}

void MainWindow::clearOutput()
{
    ui->rewordOutputLabel->setText("");
    ui->scanResultOutputLabel->setText("");
}

void MainWindow::rewordNormal(const QString &msg)
{
    QString normalLog = QString(">> ").append(msg);
    ui->rewordOutputLabel->setText(normalLog);
}

void MainWindow::rewordError(const QString &msg)
{
    QString errorMsg = QString("error: ").append(msg);
    ui->rewordOutputLabel->setText(errorMsg);
}

void MainWindow::rewordScanResult(const QString &name, int number, int expect)
{
    ui->scanResultOutputLabel->setText(
                QString("副本: ")
                .append(name)
                .append(", 盒子: ")
                .append(QString::number(number))
                .append(", 预期: ")
                .append(QString::number(expect))
                );
}

void MainWindow::setRewordScriptStateLabel(bool state)
{
    if (state)
    {
        ui->rewordScriptStateLabel->setText("START");
        ui->rewordScriptStateLabel->setStyleSheet(this->stateStartStyle);
    }
    else
    {
        ui->rewordScriptStateLabel->setText("STOP");
        ui->rewordScriptStateLabel->setStyleSheet(this->stateStopStyle);
    }
}


bool MainWindow::initInstances()
{
    // 读取配置文件
//    std::cout << "init instances" << std::endl;
    if (settings->contains("instance/names"))
    {
        QStringList nameList = settings->value("instance/names").toStringList();
        this->instancesLength = nameList.length();
//        std::cout << "names: " << nameList.join(",").toStdString() << ", length: " << this->instancesLength << std::endl;/
        this->instances = new Instance*[this->instancesLength];
        for (int i=0; i<this->instancesLength; i++)
        {
            QStringList instanceObjectList = this->settings->value(QString("instance/").append(nameList.at(i))).toStringList();
            this->instances[i] = Instance::fromInitValue(nameList.at(i), instanceObjectList);
//            std::cout << "instances[" << i << "]: " << instanceObjectList.join(",").toStdString() << std::endl;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::reInitInstance()
{
    for (int i=0; i<this->instancesLength; i++)
    {
        if (this->instances[i]->getKey() == "szhw")
        {
            this->instances[i]->setChecked(ui->szhwRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->szhwRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "jypy")
        {
            this->instances[i]->setChecked(ui->jypyRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->jypyRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "yzhj")
        {
            this->instances[i]->setChecked(ui->yzhjRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->yzhjRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "jhxs")
        {
            this->instances[i]->setChecked(ui->jhxsRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->jhxsRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "xyg")
        {
            this->instances[i]->setChecked(ui->xygRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->xygRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "wjsz")
        {
            this->instances[i]->setChecked(ui->wjszRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->wjszRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "wrg")
        {
            this->instances[i]->setChecked(ui->wrgRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->wrgRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "mysz")
        {
            this->instances[i]->setChecked(ui->myszRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->myszRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "lrmc")
        {
            this->instances[i]->setChecked(ui->lrmcRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->lrmcRewordSpinBox->value());
        }
        else if (this->instances[i]->getKey() == "tyb")
        {
            this->instances[i]->setChecked(ui->tybRewordCheckBox->checkState() == Qt::Checked);
            this->instances[i]->setRewordBox(ui->tybRewordSpinBox->value());
        }
    }
}

void MainWindow::initUiData()
{
    if (settings->contains("reword/scanDelay"))
    {
        ui->scanDelayRewordSpinBox->setValue(settings->value("reword/scanDelay").toInt());
    }

    if (settings->contains("reword/popupDelay"))
    {
        ui->popupDelayRewordSpinBox->setValue(settings->value("reword/popupDelay").toInt());
    }

    if (settings->contains("reword/fontLibrary"))
    {
        ui->settingRewordNumberFontPathLineEdit->setText(settings->value("reword/fontLibrary").toString());
    }

    for (int i=0; i<this->instancesLength; i++)
    {
        if (this->instances[i]->getKey() == "szhw")
        {
            ui->szhwRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->szhwRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "jypy")
        {
            ui->jypyRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->jypyRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "yzhj")
        {
            ui->yzhjRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->yzhjRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "jhxs")
        {
            ui->jhxsRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->jhxsRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "xyg")
        {
            ui->xygRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->xygRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "wjsz")
        {
            ui->wjszRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->wjszRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "wrg")
        {
            ui->wrgRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->wrgRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "mysz")
        {
            ui->myszRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->myszRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "lrmc")
        {
            ui->lrmcRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->lrmcRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
        else if (this->instances[i]->getKey() == "tyb")
        {
            ui->tybRewordCheckBox->setCheckState(this->instances[i]->getChecked() ? Qt::Checked : Qt::Unchecked);
            ui->tybRewordSpinBox->setValue(this->instances[i]->getRewordBox());
        }
    }
}

void MainWindow::initRewordConnect(RewordScript *rscript)
{
    rscript->moveToThread(&scriptThread);
    connect(this, &MainWindow::startScript, rscript, &RewordScript::run);
    connect(rscript, &RewordScript::normal, this, &MainWindow::rewordNormal);
    connect(rscript, &RewordScript::error, this, &MainWindow::rewordError);
    connect(rscript, &RewordScript::scanResult, this, &MainWindow::rewordScanResult);
    connect(rscript, &RewordScript::setUiState, this, &MainWindow::setRewordScriptStateLabel);
}

void MainWindow::writeSettings()
{
//    std::cout << "save user setting" << std::endl;
    QStringList nameList;
    for (int i=0; i<this->instancesLength; i++)
    {
        nameList.append(this->instances[i]->getKey());
        this->instances[i]->iniSave(this->settings);
    }
    if (nameList.length() != 0)
    {
        settings->setValue("instance/names", nameList);
    }
    settings->setValue("reword/scanDelay", ui->scanDelayRewordSpinBox->value());
    settings->setValue("reword/popupDelay", ui->popupDelayRewordSpinBox->value());
    settings->setValue("reword/fontLibrary", ui->settingRewordNumberFontPathLineEdit->text());
}

void MainWindow::on_rewordStartButton_clicked()
{
    if (this->script)
    {
        if (this->script->getScriptState())
        {
            rewordError("已经有脚本在运行");
            return;
        }
    }

    // 配置文件读取是否成功
    if (!this->isInitSuccess)
    {
        rewordError("配置文件重要信息丢失，初始化数据失败");
        return;
    }

    // 是否取得游戏窗口
    if (this->wc->useless())
    {
        wc->fromClassName("Messiah_Game");
        if (this->wc->useless())
        {
            rewordError("无法获取游戏窗口");
            return;
        }
    }

    // 窗口是否符合标准
    if (!wc->clientSize().equal(1184, 661))
    {
        if (!wc->resizeClient(1184, 661))
        {
            rewordError("重置窗口大小失败");
            return;
        }
        if (!wc->move(0, 0))
        {
            rewordError("移动窗口失败");
            return;
        }
    }

    // 绑定窗口
    if (!dm->IsBind((int)wc->getHandle()))
    {
        if (!dm->BindWindow((int)wc->getHandle(),"gdi","normal","normal",0))
        {
            rewordError("绑定窗口失败");
            return;
        }
    }


    RewordScript *rewordScript;
    // 是否属于其他脚本
    if (script)
    {
        if (!dynamic_cast<RewordScript*>(this->script))
        {
            delete this->script;
            this->script = NULL;
        }
        else
        {
            rewordScript = (RewordScript*)script;
        }
    }

    // 脚本是否已经建立
    if (!script)
    {
        // 新建悬赏脚本
          rewordScript = new RewordScript;

         // 挂载到对象变量
         this->script = rewordScript;

         // 读取窗口中用户设置
         this->reInitInstance();

         // 连接信号和槽
         this->initRewordConnect(rewordScript);


          rewordScript->setWc(this->wc);
          rewordScript->setDm(this->dm);
          rewordScript->setInstances(this->instances, this->instancesLength);
    }

    // 设置脚本数据
    reInitInstance();
    rewordScript->setDelay(ui->scanDelayRewordSpinBox->value());
    rewordScript->setPopupDelay(ui->popupDelayRewordSpinBox->value());
    rewordScript->setFontLibrary(ui->settingRewordNumberFontPathLineEdit->text());

    // 启动脚本内循环
    this->script->start();

    // 开始运行
    this->startScript();
}

void MainWindow::on_rewordResetWindowButton_clicked()
{
    if (this->wc->useless())
    {
        wc->fromClassName("Messiah_Game");
        if (this->wc->useless())
        {
            rewordError("无法获取游戏窗口");
            return;
        }
    }
    if (!wc->resizeClient(1184, 661))
    {
        rewordError("重置窗口大小失败");
        return;
    }
    wc->move(0, 0);
}

void MainWindow::on_rewordStopButton_clicked()
{
    if (!this->script)
    {
        rewordError("脚本未启动");
        return;
    }
    if (this->script->getScriptState())
    {
        this->script->stop();
        rewordNormal("脚本停止");
    }
    else
    {
        rewordError("脚本未启动");
    }
}



void MainWindow::on_registerPulignButton_clicked()
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

void MainWindow::on_uinstallPulignButton_clicked()
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
