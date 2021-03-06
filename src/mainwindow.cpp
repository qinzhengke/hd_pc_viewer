#include "mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QFile>

#include <fstream>

#include "common.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    memset(class_pool, 0, sizeof(uint8_t)*CLASS_CAPACITY);

    QWidget * centerWidget = new QWidget(this);

    this->setCentralWidget(centerWidget);

    QHBoxLayout *mLayout = new QHBoxLayout();


    scatter = new Q3DScatter();
    wdgScatter = QWidget::createWindowContainer(scatter);
    mLayout->addWidget(wdgScatter);

    centerWidget->setLayout(mLayout);

}

int MainWindow::load_pcd_file(string path, pc_1d_t *pc)
{
    if(!(pc->data))
    {
        free(pc->data);
    }
    pc->size = 12;
    pc->pos_x = 0;
    pc->pos_y = 4;
    pc->pos_z = 8;
    pc->n = -1;

    ifstream ifs(path);
    if(!ifs.is_open())
    {
        PRINT_ERROR("Cannot open file: %s", path.c_str());
        return 1;
    }

    int8_t read_stage = 0;  // 0:Read head, 1: Read data
    int i=0;
    while(!ifs.eof())
    {
        string line;
        std::getline(ifs, line);
        vector<string> words = split_string(line, ' ');
        if(0 == read_stage) // Read Head
        {
            if(2 == words.size())
            {
                if("POINTS" == words[0])
                {
                    pc->n = stoi(words[1].c_str());
                    pc->data = new uint8_t[pc->n*3*sizeof(float)];
                }
                else if("DATA" == words[0])
                {
                    read_stage = 1; // Switch to read data
                }
            }
        }
        else if(1 == read_stage) // Read data
        {
            if(4 > words.size())
            {
                continue;
            }
            if(i<pc->n)
            {
                *((float*)(pc->data+i*pc->size + pc->pos_x)) = stof(words[0]);
                *((float*)(pc->data+i*pc->size + pc->pos_y)) = stof(words[1]);
                *((float*)(pc->data+i*pc->size + pc->pos_z)) = stof(words[2]);

                float x = stof(words[0]);
                float y = stof(words[1]);
                float z = stof(words[2]);

                int id = stoi(words[3]);
                if(CLASS_CAPACITY-1 < id)
                {
                    PRINT_ERROR("points id:%d not must < %d", id, CLASS_CAPACITY);
                    return 1;
                }

                pc_datas[i]<<QVector3D(x, y, z);

            }
            else
            {
                PRINT_ERROR("points is large than descriped:%d", pc->n);
                return 1;
            }

        }
    }

    for(int i=0; i<CLASS_CAPACITY; i++)
    {
        if(pc_datas[i].size() >0 )
        {
            pc_sets[i].dataProxy()->addItems(pc_datas[i]);
            pc_sets[i].setItemSize(0.05);
        }
        this->scatter->addSeries(&(pc_sets[i]));
    }


    return 0;
}

int MainWindow::loadPCDFile(QString path)
{
    load_pcd_file(path.toStdString(), &pc_data);
    return 0;
}

MainWindow::~MainWindow()
{
}
