#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filestablemodel.h"
#include "filestabledelegate.h"

#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_model(new FilesTableModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(m_model);
    ui->lineEdit->setText(QDir::currentPath());

    ui->tableView->setItemDelegate(new FilesTableDelegate(ui->tableView));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString& path)
{
    if (QDir(path).exists())
    {
        m_lastPath = path;
        m_model->SetPath(path);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, "", m_lastPath);
    ui->lineEdit->setText(path);
}
