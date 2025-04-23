#pragma once

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>


namespace GridConstants{
    enum PixelSize_c{
        ps_Small=20,
        ps_Medium=25,
        ps_Big=50
    } ;

    enum ItemKind_c{
        ik_Unknown=-1,
        ik_Square=0,
        ik_Circle=1,
        ik_Cross=2,
        ik_Ring=3
    };

    class Colors_c{
        private:
            static constexpr int color_number=12;
            static const QColor color_table[color_number];
        public:
        enum Numeration{
            cl_BackGround=0,
            cl_First,
            cl_Second,
            cl_Third,
            cl_Fourth,
            cl_Fifth,
            cl_Default=10,
            cl_GridEdge=11
        };
        /*
        inline static QColor color(int index=cl_Default){
            QColor output=Qt::black;
            switch (index)
            {
            case cl_First:
                output=Qt::green;
                break;
            case cl_Second:
                output=Qt::red;
                break;
            case cl_Third:
                output=Qt::blue;
                break;
            case cl_Fourth:
                output=Qt::darkCyan;
                break;
            case cl_Fifth:
                output=Qt::darkRed;
                break;
            case cl_BackGround:
                output=Qt::white;
                break;
            case cl_GridEdge:
                output=Qt::black;
                break;
            }
            return output;
        }
        */
        inline static QColor color(int index);
        inline static Numeration number (QColor color);
        /*
        inline static Numeration number (QColor color=Qt::black) {
            Numeration output=cl_Default;
            if(color==Qt::green)
                output=cl_First;
            else if(color==Qt::red)
                output=cl_Second;
            else if(color==Qt::blue)
                output=cl_Third;
            else if(color==Qt::darkCyan)
                output=cl_Fourth;
            else if(color==Qt::darkRed)
                output=cl_Fifth;
            else if(color==Qt::white)
                output=cl_BackGround;
            else if(color==Qt::black)
                output=cl_GridEdge;
            return output;           
        }
        */
    };
    #include "Colors_c.tpp"
}


class GridScene_{
    private:
        QGraphicsScene* scene;
        int gr_width=0,gr_height=0, pixel_size=0;
        QGraphicsItem*** grid=nullptr;

        void deleteGrid();
        void allocateGrid();
        void setBackGroundItem(int x, int y) noexcept;
        void setSquareItem(int x, int y) noexcept;
        void setCircleItem(int x, int y) noexcept;
    public:
        GridScene_(QMainWindow* parent);
        GridScene_(QMainWindow* parent, int grid_width, int grid_height, GridConstants::PixelSize_c pixel);
        ~GridScene_();

        void setupScene(int grid_width, int grid_height, GridConstants::PixelSize_c pixel);
        void cleanScene();
        void gridItemCheck(int x, int y) const;

        int getPixelSize() const;
        int getWidth() const;
        int getHeight() const;
        const QGraphicsScene* getScene();
        QGraphicsItem* operator()(int x, int y);

        QColor getItemColorQt(int x, int y) const;
        bool isItemBackGround(int x, int y) const;
        GridConstants::ItemKind_c getItemKind(int x, int y) const;
        bool isItemSquare(int x, int y) const;
        bool isItemCircle(int x, int y) const;
        void cleanItem(int x, int y);
        void setItemColor(int x, int y, QColor color);
        void setItemSquare(int x, int y);
        void setItemCircle(int x, int y);
        /*
        Note for 2 following functions:
        Item code system:
        How it will work:
        item_code is a number from 0 to 39 passed from the game library to UI.
        item_code is used to determine the type of item and it's color.
        It is set separately for every element of the fame field matrix.
        Dozens determin the type of the item, units - colors.
        How it works now:
        item_code is a number from 0 to 9 passed from the game library to UI.
        It is used to determine the type of the item.
        It is set separately for every element of the fame field matrix.
        0 - empty square cell, 1 - circle with color #1, 2 - color #2 circle. 
        */
        void setItem(int x, int y, int item_code);
        int getItemCode(int x, int y) const;


};

GridConstants::PixelSize_c pixelSizeDecoder( const int relativeSize_from_gameLib);

