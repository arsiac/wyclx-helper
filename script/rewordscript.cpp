#include "rewordscript.h"

RewordScript::RewordScript()
{
    this->delay = -1;
    this->instances = NULL;
    this->rewordInterface = new RewordInterface;
    this->scriptStart = false;
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
        scanResult("未选择副本");
        error("未选择副本");
        stop();
        return;
    }

    // 检查是否是悬赏界面
    if (!rewordInterface->check(wc))
    {
        scanResult("未打开悬赏界面");
        error("未打开悬赏界面");
        stop();
        return;
    }

    // 设置字库
    if (!dm->SetDict(0, this->fontLibrary))
    {
        scanResult("设置字库失败");
        error("设置字库失败");
        stop();
        return;
    }

    // 刷新按钮坐标
    gc::Point flashPoint = rewordInterface->getPoint("flash"),

            // 接取确认按钮坐标按钮
            takeCheckPoint = rewordInterface->getPoint("take"),
            // 接取悬赏的按钮位置
            *takePoint;

    // 悬赏格子信息
    RewordInstance **instanceInfo = rewordInterface->getRewordInstances(),
            // 当前悬赏格子信息
            *nowInstance;
    // 悬赏接取检查点
    FeaturePoint *checkPoint;
    // 副本颜色特征坐标 ocr坐标
    gc::Point *instanceColorPoint, *ocrPoint;
    // ocr范围
    gc::Size *ocrSize;
    // ocr识别结果 展示结果
    QString ocrResult, showResult;
    // 盒子数
    int boxNumber;
    // 屏幕检查点的颜色
    unsigned long checkColorInScreen,
            // 副本颜色特征坐标处的颜色
            instanceColorInScreen;

    // 是否需要刷新悬赏格子的位置
    bool string2intResult = false;
    while (this->scriptStart)
    {
        wc->leftClick(flashPoint);
        QThread::msleep(this->delay);

        // 刷新悬赏位置
        for (int i = 0; i < 3 ; i++)
        {
            // 获取检查点信息
            checkPoint = instanceInfo[i]->getCheckPoint();
            // 获取屏幕检查点颜色
            checkColorInScreen = wc->getPixel(checkPoint->getLocation().x(), checkPoint->getLocation().y());
            // 对比检查点
            if (checkColorInScreen == checkPoint->getColor())
            {
                // 是第三个检查点，则悬赏接满
                if (i == 2)
                {
                    scanResult("悬赏已接满");
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
        instanceColorPoint = nowInstance->getInstancePoint();

        // 获取屏幕上副本特征点颜色
        instanceColorInScreen = wc->getPixel(instanceColorPoint->x(), instanceColorPoint->y());

        // 判断是哪个副本
        Instance *instance = NULL;
        for (int i=0; i<this->instanceTotal; i++)
        {
            if (this->instances[i]->getRewordColor() == instanceColorInScreen)
            {
                instance = this->instances[i];
                break;
            }
        }
        // 副本指针为空，则没有匹配到已知副本
        if (!instance)
        {
            scanResult(QString("无法识别副本: ").append(QString::number(instanceColorInScreen)));
            continue;
        }
        // 判断用户是否选择此副本
        if (!instance->getChecked())
        {
            scanResult(QString("未选择此副本: ").append(instance->getName()));
            continue;
        }

        // 读取盒子数
        ocrPoint = nowInstance->getOcrPoint();
        ocrSize = nowInstance->getOcrSize();
        ocrResult = dm->Ocr(
                    ocrPoint->x(), ocrPoint->y(),
                    ocrPoint->x() + ocrSize->width(), ocrPoint->y() + ocrSize->height(),
                    "504230-333333", 0.9);

        if (ocrResult.isEmpty() || ocrResult.isNull())
        {
//            error(QString("识别为空"));
            continue;
        }


        boxNumber = ocrResult.toInt(&string2intResult);
        if (!string2intResult)
        {
            scanResult(QString("识别到的不是数字: ").append(ocrResult));
            error(QString("识别到的不是数字: ").append(ocrResult));
            continue;
        }
        // 展示读取到的信息
        showResult = QString("副本:").append(instance->getName())
                .append(", 盒子:").append(QString::number(boxNumber))
                .append(", 预期:").append(QString::number(instance->getRewordBox()));
        scanResult(showResult);
        normal(showResult);
        // 是否满足用户期望， 满足则接取
        if (instance->getRewordBox() <= boxNumber)
        {
            takePoint = nowInstance->getTakePoint();
            wc->leftClick(takePoint->x(), takePoint->y());
            QThread::msleep(popupDelay);
            wc->leftClick(takeCheckPoint);
        }
    }
}

