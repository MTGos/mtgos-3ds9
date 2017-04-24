#include <tty.hpp>
TTY::TTY(int width, int height): x(0), y(0), width(width), height(height), curColor(WHITE), rgbColor(0xFFFFFF), useRGB(false), Kobject(KobjectType::TTY) {}
TTY::~TTY() {}
auto TTY::plotChar(int x, int y, int c) -> void {}
auto TTY::rgbSupport() -> bool {return true;}
auto TTY::setColor(Color c) -> void {
    curColor = c;
    useRGB=false;
}
auto TTY::setColor(unsigned int c) -> void {
    rgbColor = c;
    useRGB=true;
}
auto TTY::putChar(int c) -> void {
    auto scroll = [this]()->void {
        for(int x=0;x<this->width;x++)
            for(int y=0;y<this->height;y++)
               this->plotChar(x,y,0);
        this->x=this->y=0;
    };
    switch(c) {
        case '\n':
            x=0;
            y++;
            if(y>=height)
                scroll();
            break;
        default:
            plotChar(x,y,c);
            x++;
            if(x>width)
                y++;
            if(y>=height)
                scroll();
    }
}
auto TTY::puts(const char *str) -> void {
    for(int i=0;str[i];i++) {
        //Decode UTF-8
        int character=0;
        if(str[i]<0x80) {
            character=str[i];
        }
        //UTF-8 character
        if((str[i]&0b11000000)==0b10000000) {
            character=0xFFFD; //ILLEGAL SEQUENCE
        }
        //Now count how many bytes follow
        int bytesToFollow=0;
        if((str[i]&0b11100000)==0b11000000) {
            bytesToFollow=1;
            character=str[i]&0b11111;
        } else if((str[i]&0b11110000)==0b11100000) {
            bytesToFollow=2;
            character=str[i]&0b1111;
        } else if((str[i]&0b11111000)==0b11110000) {
            bytesToFollow=3;
            character=str[i]&0b111;
        } else if(!character)
            character=0xFFFD; //ILLEGAL SEQUENCE
        while(bytesToFollow) {
            i++;
            if(!str[i]) {
                putChar(0xFFFD); //Incomplete
                return;
            }
            if((str[i]&0b11000000)!=0b10000000) {
                putChar(0xFFFD); //ILLEGAL SEQUENCE
                break;
            }
            character <<= 6;
            character |= str[i] & 0b111111;
            bytesToFollow--;
        }
        if(!bytesToFollow)
            putChar(character);
    }
}
