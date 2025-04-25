#include "gamewindow.h"
#include "./ui_gamewindow.h"
#include <fstream>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
    , timer(new QTimer(this))
    , main_scene(this)
    , second_scene(this)
{
    ui->setupUi(this);

    QToolTip::setFont(QFont("Arial", 12, QFont::Bold));

#ifdef TE_TRIS
    unactivateItem(ui->gamesList->item(1));
#endif
#ifdef S_SNAKE
    unactivateItem(ui->gamesList->item(0));
#endif

    for(int i=ACT_GAMES_AMO+1;i<GAMES_AMO;i++){
        unactivateItem(ui->gamesList->item(i));
    }

    firstWorkSpaceInitial();

    qApp->installEventFilter(this);

}

void GameWindow::unactivateItem (QListWidgetItem* item){
    QFont strikeTFont=item->font();
    strikeTFont.setStrikeOut(true);
    item->setFont(strikeTFont);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    item->setForeground(QColor(192, 191, 188));
}

GameWindow::~GameWindow()
{
    delete timer;
    delete ui;
}

void GameWindow::on_gamesList_itemClicked(QListWidgetItem *item)
{
    textIndication("Item " + item->text()+" - CLICKED ");       //debug
}


void GameWindow::on_gamesList_itemDoubleClicked(QListWidgetItem *item)
{
    textIndication("Item " + item->text()+" - DOUBLE CLICKED ");       //debug
    active_game=ui->gamesList->row(item);
    if(active_game<0 || active_game>ACT_GAMES_AMO)
        textIndication("Error in game defigning: restart the game.");
    else {
        if(isFromFirstGroup(item))
            ui->workSpaces->setCurrentIndex(1);
    }   
}

bool GameWindow::isFromFirstGroup(const QListWidgetItem *item) const{
    return ui->gamesList->row(item)==1 || ui->gamesList->row(item)==0;
}


void GameWindow::on_workSpaces_currentChanged(int arg1)
{
    textIndication(QString("Changed to workSpace #%1").arg(arg1));      //debug
    switch (arg1) {
    case 0:
        firstWorkSpaceInitial();
        break;
    case 1:
        secondWorkSpaceInitial();
        break;
    case 2:
        thirdWorkSpaceInitial();
        break;
    default:
        firstWorkSpaceInitial();///change here!!!! add message!
        break;
    }
}
void GameWindow::setNoteFile(){
    note_file=nullptr;
    switch (active_game)
    {
    case 0:
        note_file=TTT_ctrl_file;
        break;
    case 1:
        note_file=TSS_ctrl_file;
        break;
    default:
        note_file="nan";
        break;
    }
}


void GameWindow::firstWorkSpaceInitial()
{
    active_game=-1;
    winNameSetter();
    ui->infoPoint->setToolTip("Double click to select game");
}
void GameWindow::secondWorkSpaceInitial()
{
    ui->controlesTable->show();
    ui->controlesTable->setRowCount(0);
    ui->controlesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->controlesTable->setSelectionMode(QAbstractItemView::NoSelection);


    winNameSetter();
    ui->infoPoint->setToolTip("Press Start button to start");

    int cur_row=0;
    setNoteFile();
    std::ifstream ifs(note_file);
    if (ifs.is_open()){
        std::string input_str;
        while(!ifs.eof()){
            getline(ifs,input_str);
            if(input_str.empty())
                continue;
            ui->controlesTable->insertRow(cur_row);
            ui->controlesTable->setItem(cur_row,0,new QTableWidgetItem(input_str.c_str()));
            // ui->controlesTable->item(cur_row,0)->setFlags(Qt::ItemIsEnabled);
            getline(ifs,input_str);
            ui->controlesTable->setItem(cur_row,1,new QTableWidgetItem(input_str.c_str()));
            // ui->controlesTable->item(cur_row,1)->setFlags(Qt::ItemIsEnabled);
            cur_row++;
        }
        ifs.close();
    }
    else
        ui->controlesTable->hide();
}
void GameWindow::thirdWorkSpaceInitial(){
    
    QString str;
    std::ifstream ifs(note_file);
    if (ifs.is_open()){
        std::string input_str;
        while(!ifs.eof()){
            getline(ifs,input_str);
            if(input_str.empty())
                continue;
            str+=input_str.c_str();
            str+=" - ";
            getline(ifs,input_str);
            str+=input_str.c_str();
            if(!ifs.eof())
                str+="\n";
        }
        ifs.close();
    }
    else
        str=NOINFO;    

    ui->infoPoint->setToolTip(str);

    getViewReady();
    
}

void GameWindow::getViewReady(){
    main_scene.setupScene(FieldSize_c::Width, FieldSize_c::Height,pixelSizeDecoder(FieldSize_c::RelativeSize));
    QGraphicsScene* scene = const_cast<QGraphicsScene*>(main_scene.getScene());
    ui->mainView->setScene(scene);
    ui->mainView->setFixedSize(scene->width()+2,scene->height()+2);
    // ui->mainView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

    connect(timer, &QTimer::timeout, this, &GameWindow::displayGameState);
    timer->start(50);
/**/                                                                 //temp
    userInput(UserAction_t::Start,true);
    GameInfo_t info=updateCurrentState();
    
    if(info.next){
        second_scene.setupScene(FieldSize_c::Second_Width, FieldSize_c::Second_Height,pixelSizeDecoder(FieldSize_c::Second_RelativeSize));
        scene = const_cast<QGraphicsScene*>(second_scene.getScene());
        ui->secondView->setScene(scene);
        ui->secondView->setFixedSize(scene->width()+2,scene->height()+2);
    }
    else
        ui->secondView->setVisible(false);
    if(info.score<0){
        ui->scoreDisplay->setVisible(false);
        ui->scoreTitel->setVisible(false);
    }
    if(info.high_score<0){
        ui->recordDisplay->setVisible(false);
        ui->recordTitel->setVisible(false);
    }
    if(info.level<0){
        ui->levelDisplay->setVisible(false);
        ui->levelTitel->setVisible(false);
    }

    displayGameState();
    /**/
}





void GameWindow::textIndication(const QString str){
    ui->indicator->setText(str);
}
void GameWindow::winNameSetter(){
    switch (active_game)
    {
    case 0:
        this->setWindowTitle("The Te-Tris");
        break;
    case 1:
        this->setWindowTitle("The S-Snake (classic)");
        break;
    case 2:
        this->setWindowTitle("The S-Snake (borderless)");
        break;
    case 3:
        this->setWindowTitle("The Big-tac-toe");
        break;
    case 4:
        this->setWindowTitle("The Sudoku-doki");
        break;
    default:        //inc -1
        this->setWindowTitle("Games dodecahedron");
        break;
    }
}




void GameWindow::on_backToGameListButton_pressed()
{
    ui->workSpaces->setCurrentIndex(0);
}


void GameWindow::on_startButton_pressed()
{
    ui->workSpaces->setCurrentIndex(2);
}







void GameWindow::displayGameState(){         //refactor me, Bitch!
    // static unsigned long i=0;
    // textIndication(QString("Timer tick - %1").arg(++i));      //debug

    /**/                                                //temp
    GameInfo_t info=updateCurrentState();
    if(info.field){
        for(int y=0;y<FieldSize_c::Height;y++){
            for(int x=0;x<FieldSize_c::Width;x++){
                main_scene.setItem(x,y,info.field[y][x]);
            }
        }
    }
    else{
        gameOverScreen();
    }
    if(info.next){
        for( int y=0;y<FieldSize_c::Second_Height;y++){
            for(int x=0;x<FieldSize_c::Second_Width;x++){
                second_scene.setItem(x,y,info.next[y][x]);
            }
        }
    }

    ui->scoreDisplay->display(info.score);
    ui->recordDisplay->display(info.high_score);
    ui->levelDisplay->display(info.level);
    /**/
}


bool GameWindow::eventFilter(QObject *obj, QEvent *event){         //refactor me, Bitch!
    if(event->type()==QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(ui->workSpaces->currentIndex()==1 && (keyEvent->key()==Qt::Key_Enter || keyEvent->key()==Qt::Key_Return))
            ui->workSpaces->setCurrentIndex(2);
        if(ui->workSpaces->currentIndex()==2){
            bool flag=1;
            switch(keyEvent->key()){
                case Qt::Key_Return:
                case Qt::Key_Enter:
                    textIndication("Pressed: - Enter");      //debug
                    userInput(UserAction_t::Start,flag);
                    break;
                case Qt::Key_Shift:
                case Qt::Key_Z:
                case Qt::Key_Space:
                    textIndication("Pressed: - Action");      //debug    
                    userInput(UserAction_t::Action,flag);
                    break;
                case Qt::Key_Up:
                    textIndication("Pressed: - Up");      //debug    
                    userInput(UserAction_t::Up,flag);
                    break;
                case Qt::Key_Down:
                    textIndication("Pressed: - Down");      //debug    
                    userInput(UserAction_t::Down,flag);
                    break;
                case Qt::Key_Left:
                    textIndication("Pressed: - Left");      //debug    
                    userInput(UserAction_t::Left,flag);
                    break;
                case Qt::Key_Right:
                    textIndication("Pressed: - Right");      //debug    
                    userInput(UserAction_t::Right,flag);
                    break;
                case Qt::Key_Escape:
                case Qt::Key_Q:
                    textIndication("Pressed: - Escape");      //debug    
                    userInput(UserAction_t::Terminate,flag);
                    break;
                case Qt::Key_P:
                    textIndication("Pressed: - Pause");      //debug    
                    userInput(UserAction_t::Pause,flag);
                    break;
                default:
                    break;
            }
        }
        return true;  // Prevent other widgets from handling the key
    }
    displayGameState();
    return QMainWindow::eventFilter(obj, event);    // For other events, pass it on
}


/*              //other realization
void GameWindow::keyPressEvent(QKeyEvent *event){
    textIndication(QString("Pressed: - %1").arg(event->key()));      //debug
    if(ui->workSpaces->currentIndex()==1 && (event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return))
        ui->workSpaces->setCurrentIndex(2);
    if(ui->workSpaces->currentIndex()==2){         //refactor me, Bitch!
        bool flag=1;
        switch(event->key()){
            case Qt::Key_Return:
            case Qt::Key_Enter:
                textIndication("Pressed: - Enter");      //debug
                // userInput(UserAction_t::Start,flag);
                break;
            case Qt::Key_Shift:
            case Qt::Key_Z:
            case Qt::Key_Space:
                textIndication("Pressed: - Action");      //debug    
                // userInput(UserAction_t::Action,flag);
                break;
            case Qt::Key_Up:
                textIndication("Pressed: - Up");      //debug    
                // userInput(UserAction_t::Up,flag);
                break;
            case Qt::Key_Down:
                textIndication("Pressed: - Down");      //debug    
                // userInput(UserAction_t::Down,flag);
                break;
            case Qt::Key_Left:
                textIndication("Pressed: - Left");      //debug    
                // userInput(UserAction_t::Left,flag);
                break;
            case Qt::Key_Right:
                textIndication("Pressed: - Right");      //debug    
                // userInput(UserAction_t::Right,flag);
                break;
            case Qt::Key_Escape:
            case Qt::Key_Q:
                textIndication("Pressed: - Escape");      //debug    
                // userInput(UserAction_t::Terminate,flag);
                break;
            case Qt::Key_P:
                textIndication("Pressed: - Pause");      //debug    
                // userInput(UserAction_t::Pause,flag);
                break;
            default:
                break;
        }
    }
}
*/

void GameWindow::gameOverScreen(){
    textIndication(QString("Game Over"));      //debug
}


