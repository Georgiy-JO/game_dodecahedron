
#pragma once

    
Colors_c::Numeration Colors_c::number (QColor color=Qt::black) {
    Numeration output=cl_Default;
    int i=0;
    for(auto cl:color_table){
        if(cl==color)
            output=(Numeration)i;
        i++;
    }
    return output;
}
QColor Colors_c::color(int index=cl_Default) {
    QColor output=Qt::black;
    if(index<0 || index>=color_number)
        output=color_table[index];
    return output;
}


inline const QColor Colors_c::color_table[color_number]={Qt::white,
    Qt::green,
    Qt::red,
    Qt::blue,
    Qt::darkCyan,
    Qt::darkRed,
    Qt::black,
    Qt::black,
    Qt::black,
    Qt::black,
    Qt::darkYellow, 
    Qt::black };

