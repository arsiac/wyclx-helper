#ifndef SCRIPTWINDOW_H
#define SCRIPTWINDOW_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QThread>
#include <QCloseEvent>
#include "settingwindow.h"
#include "settings.h"
#include "dm.h"
#include "window-controller/windowcontrol.h"
#include "script/rewordscript.h"
#include "script/dailytaskscript.h"

namespace Ui {
class ScriptWindow;
}

class ScriptWindow : public QWidget
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event) override;
public:
    explicit ScriptWindow(QWidget *parent = nullptr);
    ~ScriptWindow();


public slots:
    void scriptNormalOutput(const QString &normalMsg);
    void scriptErrorOutput(const QString &normalMsg);
    void rewordOutput(const QString &msg);
    void setScriptControlButtonState(bool state);

private slots:
    void on_resetWindowButton_clicked();

    void on_openOrCloseLogButton_clicked();
    
    void on_startOrStopScriptButton_clicked();

    void on_settingButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_logTextBowser_cursorPositionChanged();

private:
    // ui
    Ui::ScriptWindow *ui;
    // 配置文件数据
    Settings *settings;
    // 初始化是否成功
    bool initlizeDataSuccess;
    // 副本个数
    int instanceTotal;
    // 副本信息
    Instance **instances;
    // 悬赏刷新延迟
    int rewordFlashDelay;
    // 悬赏确认延迟
    int rewordPopupDelay;
    // 窗口控制
    gc::WindowControl *wc;
    // 大漠
    Dm::dmsoft *dm;
    // 开始按钮样式, 停止按钮样式
    QString startButtonStyle, stopButtonStyle;
    // 脚本控制按钮状态
    bool scriptControlButtonState;
    // 脚本
    AbstractScript *script;
    // 日志区是否打开
    bool isLogAreaOpen;
    // 设置窗口
    SettingWindow *settingWindow;
    // 设置窗口是否打开
    bool isSettingWindowOpen;
    // 当前脚本页
    int scriptIndex;
    // 脚本所在线程
    QThread *scriptThead;


    // 重置游戏窗口
    bool resizeGameWindow();
    // 日志输出
    void scriptOutput(const QString &msg);
    // 从配置文件读取数据
    bool initlizeDataFromSettings();
    // 将数据显示到界面上
    void initlizeInterfaceFromData();
    // 从界面读取数据
    void initlizeDataFromInterface();
    // 保存数据
    void saveSettings();
    // 初始化脚本
    void initlizeScript();
};

#endif // SCRIPTWINDOW_H
