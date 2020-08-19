#include "rewordscript.h"

RewordScript::RewordScript()
{
    this->delay = -1;
    this->instances = NULL;
    this->rewordInterface = new RewordInterface;
}

RewordScript::~RewordScript()
{
    delete this->rewordInterface;
}

void RewordScript::setInstances(Instance **value, int length)
{
    this->instances = value;
    this->instanceTotal = length;
}


void RewordScript::setDelay(int value)
{
    delay = value;
}

QString RewordScript::getFontLibrary() const
{
    return fontLibrary;
}

void RewordScript::setFontLibrary(const QString &value)
{
    fontLibrary = value;
}

void RewordScript::setPopupDelay(int value)
{
    popupDelay = value;
}

void RewordScript::start()
{
    scriptStart = true;
    setUiState(true);
}

void RewordScript::stop()
{
    scriptStart = false;
    setUiState(false);
}

int RewordScript::getDelay() const
{
    return delay;
}

int RewordScript::getPopupDelay() const
{
    return popupDelay;
}

void RewordScript::run()
{

    if (!dm || !wc)
    {
        stop();
        return;
    }

    bool isChooseInstance = false;
    for (int i=0; i<this->instanceTotal; i++)
    {
        if (this->instances[i]->getChecked())
        {
            isChooseInstance = true;
            break;
        }
    }
    if (!isChooseInstance)
    {
        error("未选择副本");
        stop();
        return;
    }

    // 检查是否是悬赏界面
    if (!rewordInterface->check(wc))
    {
        error("未打开悬赏界面");
        stop();
        return;
    }

    // 设置字库
    if (!dm->SetDict(0, this->fontLibrary))
    {
        error("设置字库失败");
        stop();
        return;
    }

    // 刷新按钮坐标
    gc::Point flashPoint = rewordInterface->getPoint("flash"),

            // 接取确认按钮坐标按钮
            takeCheckPoint = rewordInterface->getPoint("take");

    // 悬赏格子信息
    RewordInstance **instanceInfo = rewordInterface->getRewordInstances(),
            // 当前悬赏格子信息
            *nowInstance;

    while (this->scriptStart)
    {
        wc->leftClick(flashPoint);
        QThread::msleep(this->delay);

        // 刷新悬赏位置
        for (int i = 0; i < 3; i++)
        {
            // 获取检查点信息
            FeaturePoint *checkPoint = instanceInfo[i]->getCheckPoint();
            // 获取屏幕检查点颜色
            unsigned long checkColor = wc->getPixel(checkPoint->getLocation().x(), checkPoint->getLocation().y());
            // 对比检查点
            if (checkColor == checkPoint->getColor())
            {
                // 是第三个检查点，则悬赏接满
                if (i == 2)
                {
                    normal("悬赏已接满");
                    stop();
                    return;
                }
            }
            // 找到要接取的悬赏格子后退出
            else
            {
                nowInstance = instanceInfo[i];
                break;
            }
        }

//        std::cout << nowInstance->toQString().toStdString() << std::endl;
        // 获取副本颜色检查点
        gc::Point *instanceColorPoint = nowInstance->getInstancePoint();

        // 获取屏幕上副本特征点颜色
        unsigned long instanceColor = wc->getPixel(instanceColorPoint->x(), instanceColorPoint->y());

        // 判断是哪个副本
        Instance *instance = NULL;
        for (int i=0; i<this->instanceTotal; i++)
        {
            if (this->instances[i]->getRewordColor() == instanceColor)
            {
                instance = this->instances[i];
                break;
            }
        }
        // 副本指针为空，则没有匹配到已知副本
        if (!instance)
        {
            error(QString("无法识别副本: ").append(QString::number(instanceColor)));
            continue;
        }
        // 判断用户是否选择此副本
        if (!instance->getChecked())
        {
            normal(QString("未选择此副本: ").append(instance->getName()));
            continue;
        }
        // 显示读取到的副本名称
        else
        {
            normal(QString("目标副本: ").append(instance->getName()));
        }

        // 读取盒子数
        gc::Point *ocrPoint = nowInstance->getOcrPoint();
        gc::Size *ocrSize = nowInstance->getOcrSize();
        QString boxNumberString = dm->Ocr(
                    ocrPoint->x(), ocrPoint->y(),
                    ocrPoint->x() + ocrSize->width(), ocrPoint->y() + ocrSize->height(),
                    "504230-333333", 0.9);

        if (boxNumberString.isEmpty() || boxNumberString.isNull())
        {
            error(QString("识别为空: ").append(boxNumberString));
            continue;
        }
        else
        {
            // 清空错误输出避免误导用户
            normal("正常");
        }

        int boxNumber = boxNumberString.toInt();
        // 展示读取到的信息
        scanResult(instance->getName(), boxNumber, instance->getRewordBox());
        // 是否满足用户期望， 满足则接取
        if (instance->getRewordBox() <= boxNumber)
        {
            gc::Point *takePoint = nowInstance->getTakePoint();
            wc->leftClick(takePoint->x(), takePoint->y());
            QThread::msleep(popupDelay);
            wc->leftClick(takeCheckPoint);
        }
    }
}

