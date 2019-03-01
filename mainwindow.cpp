#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("%1%2").arg("Untitled").arg(appTitle));
    setupMenu();
    setupToolbar();
    setupStatusbar();
    setupTopCommand();
    setupTable();
    setupSignal();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMenu()//including ContextMenu
{
    ui->actionNew->setIcon(QPixmap(":/images/newfile.png"));
    connect(ui->actionNew,&QAction::triggered,this,&MainWindow::newFile);

    ui->actionOpen->setIcon(QPixmap(":/images/openfile.png"));
    connect(ui->actionOpen,&QAction::triggered,this,&MainWindow::openFile);

    ui->actionSave->setIcon(QPixmap(":/images/savefile.png"));
    connect(ui->actionSave,&QAction::triggered,this,&MainWindow::saveFile);

    ui->actionPrint->setIcon(QPixmap(":/images/print.png"));
    connect(ui->actionPrint,&QAction::triggered,this,&MainWindow::print);

    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::exit);

    ui->actionUndo->setIcon(QPixmap(":/images/undo.png"));
    connect(ui->actionUndo,&QAction::triggered,this,&MainWindow::undo);

    ui->actionRedo->setIcon(QPixmap(":/images/redo.png"));
    connect(ui->actionRedo,&QAction::triggered,this,&MainWindow::redo);

    ui->actionCopy->setIcon(QPixmap(":/images/copy.png"));
    connect(ui->actionCopy,&QAction::triggered,this,&MainWindow::tableCopy);
    addAction(ui->actionCopy);

    ui->actionPaste->setIcon(QPixmap(":/images/paste.png"));
    connect(ui->actionPaste,&QAction::triggered,this,&MainWindow::tablePaste);
    addAction(ui->actionPaste);

    ui->actionScreenShot->setIcon(QPixmap(":/images/screenshot.png"));
    connect(ui->actionScreenShot,&QAction::triggered,this,&MainWindow::screenShot);
    addAction(ui->actionScreenShot);

    ui->actionColor->setIcon(QPixmap(16,16));
    connect(ui->actionColor, &QAction::triggered, this, &MainWindow::selectColor);
    addAction(ui->actionColor);

    ui->actionFont->setIcon(QPixmap(":/images/setfont.png"));
    connect(ui->actionFont,&QAction::triggered,this,&MainWindow::selectFont);
    addAction(ui->actionFont);

    ui->actionAbout->setIcon(QPixmap(":/images/about.png"));
    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::showAbout);

    setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::setupToolbar()
{
    formulaLabel = new QLabel(ui->toolBar);
    formulaLabel->setMinimumSize(80, 0);
    formulaInput = new QLineEdit();
    ui->toolBar->addWidget(formulaLabel);
    ui->toolBar->addWidget(formulaInput);
}

void MainWindow::setupStatusbar()
{
    ;
}

void MainWindow::setupTopCommand()
{
    ui->navCBox->addItem(DESIGNE_TITLE);
    ui->navCBox->addItem(MATERIAL_TITLE);
    ui->navCBox->setCurrentIndex(0);

    QString buttonStyle="\
        QPushButton{\
                    background-color:rgb(230, 230, 230);\
                    color: black;   border-radius: 5px;  \
                    border: 2px groove gray; border-style: outset;} \
        QPushButton:hover{background-color:white; color: black;} \
        QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }";
    ui->calcAllButton->setStyleSheet(buttonStyle);
    ui->calcThicknessButton->setStyleSheet(buttonStyle);
    ui->calcAntiWindButton->setStyleSheet(buttonStyle);
    ui->calcAntiQuakeButton->setStyleSheet(buttonStyle);
    ui->updateButton->setStyleSheet(buttonStyle);
    QFont buttonFont=QFont("仿宋",13,QFont::Bold);
    ui->calcAllButton->setFont(buttonFont);
    ui->calcThicknessButton->setFont(buttonFont);
    ui->calcAntiWindButton->setFont(buttonFont);
    ui->calcAntiQuakeButton->setFont(buttonFont);
    ui->updateButton->setFont(buttonFont);
}

void MainWindow::setupTable()
{
    QStringList heads;
    heads<<"名称"<<"符号"<<"单位"<<"数据来源"<<"数值/计算结果"<<"备注";
    ui->table->setRowCount(ROWS);
    ui->table->setColumnCount(COLUMNS);
    ui->table->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    for(int c=0;c<COLUMNS;c++){
        ui->table->setHorizontalHeaderItem(c,
                                           new QTableWidgetItem(heads.at(c)));
    }
    QFont headFont=ui->table->horizontalHeader()->font();
    headFont.setBold(true);
    ui->table->horizontalHeader()->setFont(headFont);
    ui->table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

    for(int r=0;r<ROWS;r++){
        for(int c=0;c<COLUMNS;c++){
            ui->table->setItem(r,c,new QTableWidgetItem(""));
            ui->table->item(r,c)->setToolTip("储罐计算");//tr("R%1C%2").arg(r).arg(c));
        }
    }
    //ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int c=0;c<2;c++){
        for(int r=0;r<ROWS;r++){
            ui->table->item(r,c)->setFlags((ui->table->item(r,c)->flags()) ^ (Qt::ItemIsEditable));
        }
    }
    QFont titleFont("仿宋",16,QFont::Black|QFont::Bold);
    ui->table->item(DESIGNE_START,0)->setData(Qt::EditRole,DESIGNE_TITLE);
    ui->table->item(DESIGNE_START,0)->setFont(titleFont);
    for(int i=0,r=DESIGNE_START+1;r<ROWS && i<DESIGNES;i++,r++){
        ui->table->item(r,0)->setData(Qt::EditRole,DESIGNE_NAME[i]);
        ui->table->item(r,1)->setData(Qt::EditRole,DESIGNE_SYMBOL[i]);
    }
    ui->table->item(MATERIAL_START,0)->setData(Qt::EditRole,MATERIAL_TITLE);
    ui->table->item(MATERIAL_START,0)->setFont(titleFont);
    for(int i=0,r=MATERIAL_START+1;r<ROWS && i<MATERIALS;i++,r++){
        ui->table->item(r,0)->setData(Qt::EditRole,MATERIAL_NAME[i]);
        ui->table->item(r,1)->setData(Qt::EditRole,MATERIAL_SYMBOL[i]);
    }
}

void MainWindow::setupSignal()
{
    connect(ui->table,&QTableWidget::currentItemChanged,this,&MainWindow::updateStatus);
    connect(ui->table,&QTableWidget::currentItemChanged,this,&MainWindow::updateColor);
    connect(ui->table,&QTableWidget::currentItemChanged,this,&MainWindow::updateFormulainput);
    connect(ui->table,&QTableWidget::itemChanged,this,&MainWindow::updateStatus);
    connect(ui->table,&QTableWidget::itemChanged,this,&MainWindow::updateFormulainput);
    connect(formulaInput,&QLineEdit::returnPressed,this,&MainWindow::returnPressed);
}

void  MainWindow::resizeEvent(QResizeEvent *event)
{
    //ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int width=event->size().width();
    int table_width=ui->table->size().width();
    if(table_width<(int(0.90*width)))
        table_width=int(0.93*width);
    else
        table_width=int(0.93*table_width);
    double wProportions[COLUMNS]={0.25,0.1,0.1,0.2,0.15,0.2};
    for(int i=0;i<COLUMNS;i++){
        ui->table->setColumnWidth(i,int(table_width*wProportions[i]));
    }
    //ui->table->horizontalHeader()->setStretchLastSection(true);
    QWidget::resizeEvent(event);
}

void MainWindow::updateStatus(QTableWidgetItem *item)
{
    if (item && item ==(ui->table->currentItem())) {
        formulaLabel->setText(tr("Cell:(R%1C%2)").arg(ui->table->row(item)+1).arg(ui->table->column(item)+1));
        statusBar()->showMessage(item->data(Qt::StatusTipRole).toString(), 2000);
    }
}

void MainWindow::updateColor(QTableWidgetItem *item)
{
    QPixmap pix(16, 16);
    QColor col;
    if (item)
        col = item->backgroundColor();
    if (!col.isValid())
        col = palette().base().color();

    QPainter pt(&pix);
    pt.fillRect(0, 0, 16, 16, col);

    QColor lighter = col.light();
    pt.setPen(lighter);
    QPoint lightFrame[] = { QPoint(0, 15), QPoint(0, 0), QPoint(15, 0) };
    pt.drawPolyline(lightFrame, 3);

    pt.setPen(col.dark());
    QPoint darkFrame[] = { QPoint(1, 15), QPoint(15, 15), QPoint(15, 1) };
    pt.drawPolyline(darkFrame, 3);

    pt.end();

    ui->actionColor->setIcon(pix);
}

void MainWindow::updateFormulainput(QTableWidgetItem *item)
{
    if (item != ui->table->currentItem())
        return;
    if (item)
        formulaInput->setText(item->data(Qt::EditRole).toString());
    else
        formulaInput->clear();
}

void MainWindow::clear()
{
    foreach (QTableWidgetItem *i, ui->table->selectedItems())
        i->setText("");
}

void MainWindow::returnPressed()
{
    int col = ui->table->currentColumn();
    if(col<2)
        return;//前两列不能编辑
    int row = ui->table->currentRow();
    if(row==DESIGNE_START)
        return;//标题栏不能编辑
    QString text = formulaInput->text();
    QTableWidgetItem *item = ui->table->item(row, col);
    if (!item)
        ui->table->setItem(row, col, new QTableWidgetItem(text));
    else
        item->setData(Qt::EditRole, text);
    ui->table->viewport()->update();
}

void MainWindow::openFile()
{

}

void MainWindow::newFile()
{

}

void MainWindow::saveFile()
{

}

void MainWindow::print()
{
    ;
}

void MainWindow::exit()
{

}

void MainWindow::undo()
{

}

void MainWindow::redo()
{

}

void MainWindow::tableCopy()
{

}

void MainWindow::tablePaste()
{

}

void MainWindow::screenShot()
{

}

void MainWindow::selectColor()
{
    QTableWidgetItem *item = ui->table->currentItem();
    QColor col = item ? item->backgroundColor() : ui->table->palette().base().color();
    col = QColorDialog::getColor(col, this);
    if (!col.isValid())
        return;

    QList<QTableWidgetItem*> selected = ui->table->selectedItems();
    if (selected.count() == 0)
        return;

    foreach (QTableWidgetItem *i, selected) {
        if (i)
            i->setBackgroundColor(col);
    }

    updateColor(ui->table->currentItem());
}

void MainWindow::selectFont()
{
    QList<QTableWidgetItem*> selected = ui->table->selectedItems();
    if (selected.count() == 0)
        return;
    bool ok = false;
    QFont fnt = QFontDialog::getFont(&ok, font(), this);
    if (!ok)
        return;
    foreach (QTableWidgetItem *i, selected) {
        if (i)
            i->setFont(fnt);
    }
}

void MainWindow::showAbout()
{
    ;
}

void MainWindow::scroll2Row(const int row)
{
    if(row<0 || row>=ROWS)
        return;
    ui->table->verticalScrollBar()->setSliderPosition(row);
}

void MainWindow::on_navCBox_activated(int index)
{
    if(index==0)
        scroll2Row(DESIGNE_START);
    else if(index==1)
        scroll2Row(MATERIAL_START);

}
