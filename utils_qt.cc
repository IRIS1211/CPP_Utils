/**
 * @file    Code\utils\utils.cc.
 * @copyright   Copyright (c) 2019 IRIS_Chen IRIS Lab
 *
 * @brief   Utilities class 通用组件的实现
 * @changelog   2019/11/25    IRIS_Chen Created.
 */

#include "./utils_qt.h"
#include <QDir>
#include <QString>
#include <QObject>
#include <QDateTime>
#include <QStorageInfo>

/**
 * @fn  std::string Utils_QT::DirBack(const std::string & str)
 *
 * @brief   文件夹后退一层
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param   str The string
 *
 * @return  A std::string
 */
std::string Utils_QT::DirBack(const std::string & str)
{
    // 获取从后往前的 第一个/ 位置
    size_t index = str.find_last_of("/");
    std::string res;
    // 如果最后一个字符 / 则删除之后重新计算/ 位置
    if (index == str.size() - 1)
    {
        res = str.substr(0, index + 1);
        index = res.find_last_of("/");
    }
    res = res.substr(0, index + 1);

    return res;
}

/**
 * @fn  bool Utils_QT::CheckDir(const std::string &path, bool create_ )
 *
 * @brief   判断文件夹是否存在如果存在  根据情况判断是否创建
 *
 * @author  IRIS_Chen
 * @date    2019/11/17
 *
 * @param   path    Full pathname of the file
 * @param   create_ True to flg
 *
 * @return  True if it succeeds, false if it fails
 */
bool Utils_QT::CheckDir(const std::string &path, bool create_ /*= true*/)
{
    QString fullPath = QString::fromStdString(path);
    QDir dir(fullPath);
    if (dir.exists())
    {
        return true;
    }
    else
    {
        if (create_)
            return dir.mkpath(fullPath);    //创建多级目录
        return false;
    }
}

/**
 * @fn  bool Utils_QT::CheckFile(const std::string &path, bool create_ )
 *
 * @brief   Query if 'file' is file exist 判断文件是否存在后 根据 flg 新建
 *
 * @author  IRIS_Chen
 * @date    2019/11/17
 *
 * @param   path    The file
 * @param   create_ True to flg
 *
 * @return  True if it succeeds, false if it fails
 */
bool Utils_QT::CheckFile(const std::string &path, bool create_ /*= true*/)
{
    QString fileFullName = QString::fromStdString(path);
    QFileInfo fileInfo(fileFullName);
    if (fileInfo.isFile())
    {
        return true;
    }
    else
    {
        if (create_)
        {
            ;
        }

        return false;
    }
}

/**
 * @fn  void Utils_QT::ListAllDisk(void)
 *
 * @brief   List all disk 列出所有磁盘的信息
 *
 * @author  IRIS_Chen
 * @date    2019/11/17
 */
void Utils_QT::ListAllDisk(void)
{
    return;
}

/**
 * @fn  int Utils_QT::GetDiskOccupy(const std::string disk )
 *
 * @brief   Gets disk occupy
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 *
 * @param   disk    The disk
 *
 * @return  The disk occupy
 */
int Utils_QT::GetDiskOccupy(const std::string disk /*= "D"*/)
{
    double all = GetDiskAll(disk);
    double used = all - GetDiskFree(disk);

    return (1000 * used / all);   // 计算占用的1000 值 
}

/**
 * @fn  double Utils_QT::GetDiskAll(const std::string disk )
 *
 * @brief   Gets disk all
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 *
 * @param   disk    The disk
 *
 * @return  The disk all
 */
double Utils_QT::GetDiskAll(const std::string disk /*= "D"*/)
{
    //获取所有分区信息
    QList<QStorageInfo> listDisks = QStorageInfo::mountedVolumes();
    //枚举各个分区信息
    int nCount = listDisks.count();
    for (int i = 0; i < nCount; i++)
    {
        QString tmp = listDisks[i].rootPath();
        if (tmp[0] == disk[0])
        {
            //分区的空间信息
            double dblAllGB = 1.0 * listDisks[i].bytesTotal() / (1024 * 1024 * 1024);
            double dblFreeGB = 1.0 * listDisks[i].bytesFree() / (1024 * 1024 * 1024);
            UNREFERENCED_PARAMETER(dblFreeGB);
            return dblAllGB;
        }
    }
    return 0;   // 如果没有找到一致的
}

/**
 * @fn  double Utils_QT::GetDiskFree(const std::string disk )
 *
 * @brief   Gets disk free
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 *
 * @param   disk    The disk
 *
 * @return  The disk free
 */
double Utils_QT::GetDiskFree(const std::string disk /*= "D"*/)
{
    //获取所有分区信息
    QList<QStorageInfo> listDisks = QStorageInfo::mountedVolumes();
    //枚举各个分区信息
    int nCount = listDisks.count();
    for (int i = 0; i < nCount; i++)
    {
        QString tmp = listDisks[i].rootPath();
        if (tmp[0] == disk[0])
        {
            //分区的空间信息
            double dblAllGB = 1.0 * listDisks[i].bytesTotal() / (1024 * 1024 * 1024);
            double dblFreeGB = 1.0 * listDisks[i].bytesFree() / (1024 * 1024 * 1024);
            UNREFERENCED_PARAMETER(dblAllGB);
            return dblFreeGB;
        }
    }
    return 0;   // 如果没有找到一致的
}

/**
 * @fn  double Utils_QT::GetDiskUsed(const std::string disk )
 *
 * @brief   Gets disk used
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 *
 * @param   disk    The disk
 *
 * @return  The disk used
 */
double Utils_QT::GetDiskUsed(const std::string disk /*= "D"*/)
{
    //获取所有分区信息
    QList<QStorageInfo> listDisks = QStorageInfo::mountedVolumes();
    //枚举各个分区信息
    int nCount = listDisks.count();
    for (int i = 0; i < nCount; i++)
    {
        QString tmp = listDisks[i].rootPath();
        if (tmp[0] == disk[0])
        {
            //分区的空间信息
            double dblAllGB = 1.0 * listDisks[i].bytesTotal() / (1024 * 1024 * 1024);
            double dblFreeGB = 1.0 * listDisks[i].bytesFree() / (1024 * 1024 * 1024);
            return dblAllGB - dblFreeGB;
        }
    }
    return 0;   // 如果没有找到一致的
}


/**
 * @fn  QByteArray Utils_QT::Str2QByteArray(const std::string &str, int flg_space)
 *
 * @brief   2 q byte array
 *
 * @author  IRIS_Chen
 * @date    2019/12/27
 *
 * @param   str         The string
 * @param   flg_space   The flg space
 *
 * @return  A QByteArray
 */
QByteArray Utils_QT::Str2QByteArray(const std::string &str, int flg_space)
{
    size_t n = str.size();
    if (n < 2) return QByteArray();
    QByteArray res;
    if (flg_space)
    {
        res.resize(static_cast<int>((n + 1) / 3));
        for (int i = 0; i < ((n + 1) / 3); i++)
        {
            res[i] = Utils_String::Hex2Uchar(str.substr(static_cast<size_t>(i * 3), 2));
        }
    }
    else
    {
        res = QByteArray::fromHex(QByteArray::fromStdString(str));
    }

    return res;
}

/**
 * @fn  bool Utils_QT::ReleaseThread(QThread *qthread)
 *
 * @brief   停止进程并同时 删除对象 // 循环进程 使用 isInterruptionRequested 做while 循环条件 避免 无法退出
 *          https://blog.csdn.net/caoshangpa/article/details/62421334
 *
 * @author  IRIS_Chen
 * @date    2019/6/17
 *
 * @param [in,out]  qthread If non-null, the qthread
 *
 * @return  True if it succeeds, false if it fails
 */
bool Utils_QT::ReleaseThread(QThread *qthread)
{
    if (qthread == nullptr)
    {
        return false;
    }
    try
    {
        qthread->requestInterruption();
        qthread->quit();
        qthread->wait();
        delete qthread;
    }
    catch (const std::exception &e)
    {
        qDebug() << "Thread Quit Error!" << e.what();
        return false;
    }

    return true;

}




/**
 * @fn  bool Utils_QT::ShowImageOnLable(const cv::Mat &srcImg, QLabel *lb_label, int width, int height)
 *
 * @brief   Shows the image on lable
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param           srcImg      Source image
 * @param [in,out]  lb_label    If non-null, the pound label
 * @param           width       The width
 * @param           height      The height
 *
 * @return  True if it succeeds, false if it fails
 */
bool Utils_QT::ShowImageOnLable(const cv::Mat &srcImg, QLabel *lb_label, int width, int height)
{
    // tCamProc->procMutex.lock(); // 处理线程  锁定
    // #TODO(SChen): 寻找减少转换的方案
    // 首先根据label 大小 缩放对应的图像

    Q_ASSERT(srcImg.rows != 0);

    cv::Mat tmp_img;
    // 进行 图像缩放 进行进一步尺寸限制
    try
    {
        // LDebug("start resize Image {}!",img_cnt);
        // #FIXME 解决图像缩放问题
        // float src_ratio = (float)srcImg.rows / srcImg.cols;
        LDebug("Show Image On Lable Resize Start!");
        cv::resize(srcImg, tmp_img, cv::Size(width, height));
        // tmp_show_img = srcImg(cv::Rect(0, 0, width, height));
        // LDebug("end Image{}", img_cnt);
        // tmp_show_img = srcImg;
    }
    catch (...)
    {
        LError("resize Error!");
    }

    // 将原始图像转换成 QImage
    QImage img = Utils_CV::CvMat2QImage(&tmp_img);

    // 将QImage 转换成 QPixmap
    QPixmap pixmap = QPixmap::fromImage(img);

    // 在相应的lable 上 显示图片
    // pixmap.scaled(QSize(lb_label->width(),lb_label->height ()));
    // lb_label->setScaledContents(true);
    lb_label->setPixmap(pixmap);

    return true;
}


/**
 * @fn  void Utils_QT::RenderNumberOnLabel(QLabel *label, float num)
 *
 * @brief   默认 float 显示一位数据
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param [in,out]  label   If non-null, the label
 * @param           num     Number of
 */
void Utils_QT::RenderNumberOnLabel(QLabel *label, float num)
{
    label->setText(QString::number(num, 'f', 1));
}

/**
 * @fn  void Utils_QT::RenderNumberOnLabel(QLabel * label, int num)
 *
 * @brief   int  直接显示
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param [in,out]  label   If non-null, the label
 * @param           num     Number of
 */
void Utils_QT::RenderNumberOnLabel(QLabel * label, int num)
{
    label->setText(QString::number(num));
}

// 返回 串口列表 形如 COM6 这种形式
std::vector<std::string> Utils_QT::GetAllSerialPort()
{
    std::vector<std::string> res;

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
    {
        res.push_back(info.portName().toStdString());
    }

    return res;
}


/**
 * @fn  QSerialPort * Utils_QT::GetSerialByPortNo(int port_no)
 *
 * @brief   Gets serial by port no
 *
 * @author  IRIS_Chen
 * @date    2019/10/17
 *
 * @exception   Utils_Exception Thrown when the Utilities error condition occurs.
 *
 * @param   port_no The port no
 *
 * @return  Null if it fails, else the serial by port no
 */
QSerialPort * Utils_QT::GetSerialByPortNo(int port_no)
{
    QString port_name;
    QSerialPort *serial_ = nullptr;
#if WIN32 
    port_name = "COM" + QString::number(port_no);
#else
    port_name = "/dev/ttyS" + +QString::number(port_no);;   // #LINUX 存在问题
#endif 

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
    {
        if (info.portName() == port_name)
        {
            serial_ = new QSerialPort(info);
            break;
        }
    }

    // 遍历找到相应的串口端口, 如果串口端口无效 则直接失效
    if (serial_ == nullptr || serial_->portName() != port_name)
    {
        throw Utils_Exception(Error_Serial_PortName_Invalid);
    }
    return serial_;
}



#if 0

/**
 * @def GB
 *
 * @brief   A macro that defines Gigabytes
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 */

#define GB (1024*1024*1024)

/**
 * @fn  quint64 getDiskSpace(QString iDriver, bool flag)
 *
 * @brief   获取磁盘容量
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param   iDriver Zero-based index of the driver
 * @param   flag    True to flag
 *
 * @return  The disk space
 */

quint64 getDiskSpace(QString iDriver, bool flag)
{
    //iDriver为盘符(例如"C\"),flag为true则求磁盘总容量，为false则求磁盘剩余容量
    LPCWSTR strDriver = reinterpret_cast<LPCWSTR>(iDriver.utf16());
    ULARGE_INTEGER freeDiskSpaceAvailable, totalDiskSpace, totalFreeDiskSpace;

    //调用函数获取磁盘参数(单位为字节Byte),转化为GB，需要除以(1024*1024*1024)
    GetDiskFreeSpaceEx(strDriver, &freeDiskSpaceAvailable, &totalDiskSpace, &totalFreeDiskSpace);
    if (flag)
    {
        return static_cast<quint64>(totalDiskSpace.QuadPart / GB);
    }
    else
    {
        return static_cast<quint64>(totalFreeDiskSpace.QuadPart / GB);
    }
}

/**
 * @fn  QStringList getDiskName()
 *
 * @brief   获取电脑所有盘符名
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @return  The disk name
 */

QStringList getDiskName()
{
    QFileInfoList list = QDir::drives();
    QStringList diskNameList(nullptr);

    for (int i = 0; i < list.count(); i++)
    {

        QString str = list.at(i).absoluteDir().absolutePath();
        diskNameList.append(str);
    }
    return diskNameList;
}

/**
 * @fn  std::string getDiskOccupy(void)
 *
 * @brief   获取本磁盘的占用
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @return  The disk occupy
 */

std::string getDiskOccupy(void)
{
    QStringList diskList = getDiskName();
    QString diskCur = QDir::currentPath().left(1);  // 获取最左侧的字符 一般是 盘符

    quint64 totalSpace = getDiskSpace(diskCur, true);
    quint64 freeSpace = getDiskSpace(diskCur, false);

    char res[20];
    sprintf(res, "%d / %d", static_cast<int>(freeSpace / 0.1f), static_cast<int>(totalSpace / 0.1f));

    return std::string(res);

}

/**
 * @fn  bool GetSysDisk(int& nDiskTotal, int& nDiskUsed)
 *
 * @brief   Gets system disk
 *
 * @author  IRIS_Chen
 * @date    2019/11/5
 *
 * @param [in,out]  nDiskTotal  The disk total
 * @param [in,out]  nDiskUsed   The disk used
 *
 * @return  True if it succeeds, false if it fails
 */

bool GetSysDisk(int& nDiskTotal, int& nDiskUsed)
{
    static char path[_MAX_PATH];//存储当前系统存在的盘符
                                // int curdrive = _getdrive();
    unsigned long lFreeAll = 0UL;
    unsigned long lTotalAll = 0UL;
    for (int drive = 1; drive <= 26; drive++)//遍历所有盘符
    {
        if (!_chdrive(drive))
        {
            sprintf(path, "%c:\\", drive + 'A' - 1);
            ULARGE_INTEGER caller, total, free;
            WCHAR wszClassName[_MAX_PATH];
            memset(wszClassName, 0, sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP, 0, path, static_cast<int>(strlen(path) + 1), wszClassName,
                                sizeof(wszClassName) / sizeof(wszClassName[0]));
            if (GetDiskFreeSpaceEx(wszClassName, &caller, &total, &free) == 0)
            {
                qDebug() << "GetDiskFreeSpaceEx Filed!";
                return false;
            }

            double dTepFree = free.QuadPart / (1024.0*1024.0);
            double dTepTotal = total.QuadPart / (1024.0*1024.0);
            //qDebug()<<"Get Windows Disk Information:"<<path<<"--free:"<<dTepFree<<"--total:"<<dTepTotal;
            lFreeAll += static_cast<unsigned long>(ceil(dTepFree));
            lTotalAll += static_cast<unsigned long>(ceil(dTepTotal));
        }
    }
    nDiskUsed = static_cast<int>(lFreeAll);
    nDiskTotal = static_cast<int>(lTotalAll);
    return true;
}

#endif
