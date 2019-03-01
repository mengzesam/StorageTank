#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QLineEdit;
class QToolBar;
class QTableWidgetItem;
class QTableWidget;
class QResizeEvent;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateStatus(QTableWidgetItem *item);
    void updateColor(QTableWidgetItem *item);
    void updateFormulainput(QTableWidgetItem *item);
    void returnPressed();
    void clear();

    void newFile();
    void openFile();
    void saveFile();
    void print();
    void exit();
    void undo();
    void redo();
    void tableCopy();
    void tablePaste();
    void screenShot();
    void selectColor();
    void selectFont();
    void showAbout();

protected:
    void resizeEvent(QResizeEvent *event);

protected:
    void setupMenu();
    void setupToolbar();
    void setupStatusbar();
    void setupTopCommand();
    void setupTable();
    void setupSignal();

private slots:

    void on_navCBox_activated(int index);

private:
    void scroll2Row(const int row);

private:
    Ui::MainWindow *ui;
    QLabel *formulaLabel;
    QLineEdit *formulaInput;

private: //const
    const QString appTitle="@储罐计算";
    const static int ROWS=201;
    const static int COLUMNS=6;
    const static int DESIGNE_START=0;
    const static int DESIGNES=14;
    const QString DESIGNE_TITLE="设计条件";
    const QString DESIGNE_NAME[DESIGNES]={
        "设计压力","设计温度","容积","直径","拱顶曲率半径","罐体半径","起始角","介质密度","建罐地区基本风压",
        "建罐地区基本雪压","地震设防烈度","设计液位高度","罐壁高度","储液总质量"
    };
    const QString DESIGNE_SYMBOL[DESIGNES]={
        "P","T","V","Di","Rs","ri","θ","ρ","qo","qw","","Hw","H","m1"
    };
    const static int MATERIAL_START=DESIGNE_START+DESIGNES+1;
    const static int MATERIALS=12;
    const QString MATERIAL_TITLE="材料选用";
    const QString MATERIAL_NAME[MATERIALS]={
        "罐壁材料","罐壁材料弹性模量","罐底材料","标准屈服强度下限值","罐顶材料","罐顶材料弹性模量",
        "罐壁材料在设计温度下许用应力","罐壁材料在20℃温度下许用应力","角钢圈","角钢圈","材料弹性模","焊接接头系数"
    };
    const QString MATERIAL_SYMBOL[MATERIALS]={
        "","Eb","","ReL","","Et","[σ]d","[σ]t","[σ]b","[τ]","E","φ"
    };
};







#endif // MAINWINDOW_H
