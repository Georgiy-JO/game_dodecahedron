#include "gridscene_.h"

void GridScene_::deleteGrid(){
    if (grid){
        for(int y=0;y<gr_height;y++){
            delete [] grid[y];
        }
        delete [] grid;
        grid = nullptr;
    }
}
void GridScene_::allocateGrid(){
    if(scene && gr_width && gr_height){
        grid= new QGraphicsItem**[gr_height];
        for(int y=0;y<gr_height;y++){
            grid[y]= new QGraphicsItem*[gr_width];
            for(int x=0;x<gr_width;x++){                        
                setBackGroundItem(x, y);
            }
        }
    }
}

GridScene_::GridScene_(QMainWindow* parent):scene(new QGraphicsScene(parent)){}  
GridScene_::GridScene_(QMainWindow* parent,int grid_width, int grid_height, GridConstants::PixelSize_c pixel=GridConstants::ps_Medium):GridScene_(parent){
    setupScene(grid_width,grid_height,pixel);
}
GridScene_::~GridScene_(){
    deleteGrid();
    if(scene)
        delete scene;
}


void GridScene_::setupScene(int grid_width, int grid_height, GridConstants::PixelSize_c pixel=GridConstants::ps_Medium){
    deleteGrid();
    gr_width=grid_width;
    gr_height=grid_height;
    pixel_size=pixel;
    scene->setSceneRect(0,0,gr_width*pixel_size, gr_height*pixel_size);
    // scene->setBackgroundBrush(QBrush(QColor(GridConstants::Colors_c::color(GridConstants::Colors_c::cl_BackGround))));
    allocateGrid();
}
void GridScene_::cleanScene(){
    deleteGrid();
    scene->clear();
}
void GridScene_::gridItemCheck(int x, int y) const{
    if(x>=gr_width || y>=gr_height)
        throw std::out_of_range("GridScene_: you are callin out of range grid item.");
    if(scene==nullptr || grid==nullptr || grid[y][x]==nullptr)
        throw std::out_of_range("GridScene_: grid item you are trying to call is out of range.");
}

int GridScene_::getPixelSize() const {
    return pixel_size;
}
int GridScene_::getWidth() const{
    return gr_width;
}
int GridScene_::getHeight()const {
    return gr_height;
}
const QGraphicsScene* GridScene_::getScene(){
    return scene;
}
QGraphicsItem* GridScene_::operator()(int x, int y){
    gridItemCheck(x,y);
    return grid[y][x];
}

QColor GridScene_::getItemColorQt(int x, int y) const{
    gridItemCheck(x,y);
    QColor output=GridConstants::Colors_c::color(GridConstants::Colors_c::cl_Default);
    if(isItemSquare(x,y))
        output= dynamic_cast<QGraphicsRectItem*>(grid[y][x])->brush().color();
    else if(isItemCircle(x,y))
        output= dynamic_cast<QGraphicsEllipseItem*>(grid[y][x])->brush().color();
    return output;
}
bool GridScene_::isItemBackGround(int x, int y) const{
    bool output=0;
    if (isItemSquare(x, y) && getItemColorQt(x,y)==GridConstants::Colors_c::color(GridConstants::Colors_c::cl_BackGround))
        output=dynamic_cast<QGraphicsRectItem*>(grid[y][x])->pen().color()==GridConstants::Colors_c::cl_GridEdge;
    return output;
}
GridConstants::ItemKind_c GridScene_::getItemKind(int x, int y) const{
    gridItemCheck(x,y);
    GridConstants::ItemKind_c output=GridConstants::ItemKind_c::ik_Unknown;
    switch (grid[y][x]->type())
    {
    case QGraphicsRectItem::Type:
        output=GridConstants::ItemKind_c::ik_Square;
        break;
    
    case QGraphicsEllipseItem::Type:
        output=GridConstants::ItemKind_c::ik_Circle;
        break;
    }
    return output;
}
bool GridScene_::isItemSquare(int x, int y) const{
    return getItemKind(x,y)==GridConstants::ik_Square;
}
bool GridScene_::isItemCircle(int x, int y) const{
    return getItemKind(x,y)==GridConstants::ik_Circle;
}

GridConstants::PixelSize_c pixelSizeDecoder( const int relativeSize_from_gameLib){
    GridConstants::PixelSize_c output=GridConstants::PixelSize_c::ps_Medium;
    switch (relativeSize_from_gameLib)
    {
    case -1:
        output=GridConstants::PixelSize_c::ps_Small;
        break;
    case 1:
        output=GridConstants::PixelSize_c::ps_Big;
        break;
    }
    return output;
} 

void GridScene_::setBackGroundItem(int x, int y) noexcept{                 //achtung!!!!
    grid[y][x]=(QGraphicsItem*)(scene->addRect(x*pixel_size,y*pixel_size,pixel_size,pixel_size, QPen(GridConstants::Colors_c::color(GridConstants::Colors_c::cl_GridEdge)), QBrush(GridConstants::Colors_c::color(GridConstants::Colors_c::cl_BackGround))));
}
void GridScene_::setSquareItem(int x, int y) noexcept{                 //achtung!!!!
    grid[y][x]=(QGraphicsItem*)(scene->addRect(x*pixel_size,y*pixel_size,pixel_size,pixel_size, QPen(GridConstants::Colors_c::color(GridConstants::Colors_c::cl_GridEdge)), QBrush(GridConstants::Colors_c::color(GridConstants::Colors_c::cl_Default))));
}
void GridScene_::setCircleItem(int x, int y) noexcept{                 //achtung!!!!
    grid[y][x]=(QGraphicsItem*)(scene->addEllipse(x*pixel_size,y*pixel_size,pixel_size,pixel_size, QPen(GridConstants::Colors_c::color(GridConstants::Colors_c::cl_BackGround)), QBrush(GridConstants::Colors_c::color(GridConstants::Colors_c::cl_Default))));
}
void GridScene_::cleanItem(int x, int y){
    gridItemCheck(x,y);
    if(!isItemSquare(x,y)){
        scene->removeItem(grid[y][x]);
        setBackGroundItem(x, y);
    }
    else 
        setItemColor(x,y,GridConstants::Colors_c::color(GridConstants::Colors_c::cl_BackGround));
        

}
void GridScene_::setItemColor(int x, int y, QColor color=GridConstants::Colors_c::color(GridConstants::Colors_c::cl_Default)){
    gridItemCheck(x,y);
    if(isItemSquare(x,y))
        dynamic_cast<QGraphicsRectItem*>(grid[y][x])->setBrush(color);
    else if(isItemCircle(x,y))
        dynamic_cast<QGraphicsEllipseItem*>(grid[y][x])->setBrush(color);
}
void GridScene_::setItemSquare(int x, int y){
    gridItemCheck(x,y);
    if(!isItemSquare(x,y)){
        scene->removeItem(grid[y][x]);
        setSquareItem(x,y);
    }
}
void GridScene_::setItemCircle(int x, int y){
    gridItemCheck(x,y);
    if(!isItemCircle(x,y)){
        scene->removeItem(grid[y][x]);
        setCircleItem(x,y);
    }
}
void GridScene_::setItem(int x, int y, int item_code){
    if(item_code!=getItemCode(x,y)){
        switch (item_code)
        {
        case 0:
            if(!isItemBackGround(x,y))
                cleanItem(x,y);
            break;
        case 1:
            if(isItemSquare(x,y))
                setItemColor(x,y,GridConstants::Colors_c::color(item_code));
            else {
                setItemSquare(x,y);
                setItemColor(x,y,GridConstants::Colors_c::color(item_code));
            }
            break;
        case 2:
        case 3:
            if(isItemSquare(x,y)){
                setItemCircle(x,y);
                setItemColor(x,y,GridConstants::Colors_c::color(item_code));
            }
            else
                setItemColor(x,y,GridConstants::Colors_c::color(item_code));
            break;
        default:
            setItemSquare(x,y);
            break;
        }
    }
}
int GridScene_::getItemCode(int x, int y) const{
    return GridConstants::Colors_c::number(getItemColorQt(x,y));
}

