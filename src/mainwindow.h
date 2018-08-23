#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization>

#include <iostream>
#include <cstdint>
using namespace std;
using namespace QtDataVisualization;

#define CLASS_CAPACITY 32

typedef struct
{
    uint8_t *data;
    int32_t size;
    int32_t n;
    int32_t pos_x;
    int32_t pos_y;
    int32_t pos_z;
    int32_t pos_i;
}pc_1d_t;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int loadPCDFile(QString path);

    int load_pcd_file(string path, pc_1d_t *pc);

    QScatter3DSeries pc_sets[CLASS_CAPACITY];
    QScatterDataArray pc_datas[CLASS_CAPACITY];

    // Max number of points set 32
    uint8_t class_pool[CLASS_CAPACITY];

private:
    Q3DScatter *scatter;
    QWidget *wdgScatter;

    pc_1d_t pc_data;

};

#endif // MAINWINDOW_H
