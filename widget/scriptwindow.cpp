#include "scriptwindow.h"
#include "ui_scriptwindow.h"

ScriptWindow::ScriptWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptWindow)
{
    ui->setupUi(this);

    settings = new Settings("./resource/settings.ini");
    wc = new gc::WindowControl("Messiah_Game");
    dm = new Dm::dmsoft;
    scriptThead = new QThread;
    settingWindow = new SettingWindow(this);
    script = nullptr;
    instances = nullptr;

    scriptControlButtonState = false;
    isSettingWindowOpen = false;
    initlizeDataSuccess = false;
    instanceTotal = 0;
    scriptIndex = 0;
    startButtonStyle = "QPushButton{border-radius:3px;background-color:#1E90FF;color:#FFF;}QPushButton:hover{background-color:#00BFFF;}";
    stopButtonStyle = "QPushButton{border-radius:3px;background-color:#DC143C;color:#FFF;}QPushButton:hover{background-color:#FF4242;}";


    // 从配置文件读取数据，并初始化界面数据
    if (initlizeDataFromSettings())
    {
        initlizeDataSuccess = true;
        initlizeInterfaceFromData();
    }

    // 固定大小
    settingWindow->move(50, 30);
    settingWindow->hide();
    if (isLogAreaOpen)
    {
        this->setFixedSize(600, 700);
    }
    else
    {
        this->setFixedSize(600, 400);
    }
    // 检查插件是否注册
    if (dm->Ver().isEmpty())
    {
        QMessageBox::warning(this, "提示", "插件未注册， 请前往设置注册后重启软件");
    }

}

ScriptWindow::~ScriptWindow()
{
    if (scriptThead->isRunning())
    {
        scriptThead->quit();
    }

    delete ui;
    delete settingWindow;
    delete settings;
    delete wc;
    delete dm;
    if (instances)
    {
        for (int i=0; i<instanceTotal; i++)
        {
            if (instances[i])
            {
                delete instances[i];
            }
        }
        delete instances;
    }
    if (script)
    {
        delete script;
    }
}

void ScriptWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
    if (scriptThead->isRunning())
    {
        scriptThead->quit();
    }
    event->accept();
}

bool ScriptWindow::resizeGameWindow()
{
    if (wc->useless())
    {
        wc->fromClassName("Messiah_Game");
        if (wc->useless())
        {
            QMessageBox::warning(this, "警告", "无法获取游戏窗口!");
            return false;
        }
    }

    if (wc->clientSize().equal(1184, 661))
    {
        return true;
    }

    if (!wc->resizeClient(1184, 661))
    {
        QMessageBox::warning(this, "警告", "重置窗口失败!");
        return false;
    }
    wc->move(0, 0);
    return true;
}

bool ScriptWindow::initlizeDataFromSettings()
{
    QStringList nameList = settings->getInstancesNames();
    instanceTotal = nameList.length();
    if (!instanceTotal)
    {
        return false;
    }
    instances = new Instance*[instanceTotal];
    QString key;
    for (int i=0; i<instanceTotal; i++)
    {
        key = nameList.at(i);
        this->instances[i] = Instance::fromIniValue(key, settings->getInstanceByKey(key));
    }
    rewordFlashDelay = settings->getRewordFlashDelay();
    rewordPopupDelay = settings->getRewordPopupDelay();
    isLogAreaOpen = settings->getAutoOpenLOG();
    return true;
}

void ScriptWindow::initlizeInterfaceFromData()
{
    //settingWindow
    settingWindow->setAutoOpenLOG(isLogAreaOpen);
    settingWindow->setRewordFontLibrary(settings->getRewordFontLibrary());
    settingWindow->setDailyFlashDelay(settings->getDailyFlashDelay());
    settingWindow->setDailyFontLibrary(settings->getDailyFontLibrary());
    // data
    ui->flashDelayRewordSpinBox->setValue(rewordFlashDelay);
    ui->popupDelayRewordSpinBox->setValue(rewordPopupDelay);
    for (int i=0; i<this->instanceTotal; i++)
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

void ScriptWindow::initlizeDataFromInterface()
{
    this->rewordFlashDelay = ui->flashDelayRewordSpinBox->value();
    this->rewordPopupDelay = ui->popupDelayRewordSpinBox->value();
    for (int i=0; i<this->instanceTotal; i++)
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

void ScriptWindow::saveSettings()
{
    settings->saveInstances(instances, instanceTotal);
    settings->saveRewordFlashDelay(rewordFlashDelay);
    settings->saveRewordPopupDelay(rewordPopupDelay);
    settings->saveAutoOpenLOG(settingWindow->getAutoOpenLOG());
}

void ScriptWindow::rewordOutput(const QString &msg)
{
    ui->rewordResultLabel->setText(msg);
}

void ScriptWindow::setScriptControlButtonState(bool state)
{
    if (state)
    {
        ui->startOrStopScriptButton->setText("停止");
        ui->startOrStopScriptButton->setStyleSheet(stopButtonStyle);
        scriptControlButtonState = true;
    }
    else
    {
        ui->startOrStopScriptButton->setText("开始");
        ui->startOrStopScriptButton->setStyleSheet(startButtonStyle);
        scriptControlButtonState = false;
    }
}

void ScriptWindow::scriptOutput(const QString &msg)
{
    ui->logTextBowser->append(msg+'\n');
}

void ScriptWindow::scriptNormalOutput(const QString &normalMsg)
{
    scriptOutput(QString("(normal)>> ").append(normalMsg));
}

void ScriptWindow::scriptErrorOutput(const QString &normalMsg)
{
    scriptOutput(QString("(error)>> ").append(normalMsg));
}

// SLOTS
void ScriptWindow::on_resetWindowButton_clicked()
{
    if (resizeGameWindow())
    {
        scriptNormalOutput("窗口重置成功");
    }
}

void ScriptWindow::on_openOrCloseLogButton_clicked()
{
    if (isLogAreaOpen)
    {
        setFixedSize(600, 400);
        isLogAreaOpen = false;
    }
    else
    {
        setFixedSize(600, 700);
        isLogAreaOpen = true;
    }
}

void ScriptWindow::on_settingButton_clicked()
{
    if (settingWindow->isHidden())
    {
        settingWindow->show();
    }
    else
    {
        settingWindow->hide();
    }
}

void ScriptWindow::on_tabWidget_currentChanged(int index)
{
    scriptIndex = index;
    //    scriptOutput(QString("Scrpit Index:").append(QString::number(scriptIndex)));
}

void ScriptWindow::on_logTextBowser_cursorPositionChanged()
{
    ui->logTextBowser->moveCursor(QTextCursor::End);
}

void ScriptWindow::initlizeScript()
{
    if (0 == scriptIndex)
    {
        // 脚本是其他脚本,则清空脚本并设为空指针
        if (script && !dynamic_cast<RewordScript*>(script))
        {
            delete script;
            script = nullptr;
        }
        // 脚本为空，则建立新脚本
        if (!script)
        {
            RewordScript *newScript = new RewordScript;
            script = newScript;
            newScript->setDm(dm);
            newScript->setWc(wc);
            newScript->setInstances(instances, instanceTotal);
            newScript->setRunningThread(scriptThead);
            connect(scriptThead, &QThread::started,newScript, &RewordScript::run);
            connect(newScript, &RewordScript::normal, this, &ScriptWindow::scriptNormalOutput);
            connect(newScript, &RewordScript::error, this, &ScriptWindow::scriptErrorOutput);
            connect(newScript, &RewordScript::scanResult, this, &ScriptWindow::rewordOutput);
            connect(newScript, &RewordScript::changeScriptState, this, &ScriptWindow::setScriptControlButtonState);
            script->moveToThread(scriptThead);
        }
        // 设置脚本数据
        initlizeDataFromInterface();
        RewordScript *rewordScript = (RewordScript*)script;
        rewordScript->setDelay(rewordFlashDelay);
        rewordScript->setPopupDelay(rewordPopupDelay);
        rewordScript->setFontLibrary(settingWindow->getRewordFontLibrary());
    }
    else if (1 == scriptIndex)
    {
        // 脚本是其他脚本,则清空脚本并设为空指针
        if (script && !dynamic_cast<DailyTaskScript*>(script))
        {
            delete script;
            script = nullptr;
        }
        // 脚本为空，则建立新脚本
        if (!script)
        {
            DailyTaskScript *newScript = new DailyTaskScript;
            script = newScript;
            newScript->setDm(dm);
            newScript->setWc(wc);
            newScript->setFlashDelay(settingWindow->getDailyFlashDelay());
            newScript->setRunningThread(scriptThead);
            connect(scriptThead, &QThread::started,newScript, &DailyTaskScript::run);
            connect(newScript, &DailyTaskScript::normal, this, &ScriptWindow::scriptNormalOutput);
            connect(newScript, &DailyTaskScript::error, this, &ScriptWindow::scriptErrorOutput);
            connect(newScript, &DailyTaskScript::changeScriptState, this, &ScriptWindow::setScriptControlButtonState);
            script->moveToThread(scriptThead);
        }
    }
    else
    {
        scriptErrorOutput("这个未完成哦");
        return;
    }

}

void ScriptWindow::on_startOrStopScriptButton_clicked()
{
    // 是否有脚本在运行
    if (script && script->getScriptState())
    {
        script->stop();
        scriptNormalOutput("已停止");
        return;
    }

    // 数据初始化是否成功
    if (!initlizeDataSuccess)
    {
        scriptErrorOutput("配置文件重要信息丢失，初始化数据失败");
        return;
    }

    // 重置游戏窗口
    if (!resizeGameWindow())
    {
        return;
    }

    // 绑定窗口
    if (!dm->IsBind((int)wc->getHandle()))
    {
        if (!dm->BindWindow((int)wc->getHandle(),"gdi","normal","normal",0))
        {
            scriptErrorOutput("绑定窗口失败");
            return;
        }
    }
    initlizeScript();
    script->start();
}
