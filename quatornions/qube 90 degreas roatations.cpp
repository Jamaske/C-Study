#include <cstdio>

union orientation {
    struct {
        unsigned char k : 1;
        unsigned char w : 1;
        signed char x : 2;
        signed char y : 2;
        signed char z : 2;
    };
    struct {
        unsigned char s : 2;
        unsigned char v : 6;
    };
    unsigned char byte;

    orientation() :byte(0b00000010) {} //reverse bit order coution
    orientation(const orientation* src) :byte(src->byte) {}

    void print() {
        printf("(1/2)^(%d)*(sqrt2)^(%d)*(%d + %di + %dj + %dk)\n\n", (bool)v, k, w, x, y, z);
    }

    void rotate(char rotor) {
        char w, x, y, z;
        orientation copy(this);

        switch (rotor | (++copy.k && (bool)copy.v) << 4) {
        case 0b1000: //+X
            w = copy.w - copy.x;
            x = copy.x + copy.w;
            y = copy.y - copy.z;
            z = copy.z + copy.y;
            break;
        case 0b1001: //-X
            w = copy.w + copy.x;
            x = copy.x - copy.w;
            y = copy.y + copy.z;
            z = copy.z - copy.y;
            break;
        case 0b0100: //+Y
            w = copy.w - copy.y;
            x = copy.x + copy.z;
            y = copy.y + copy.w;
            z = copy.z - copy.x;
            break;
        case 0b0101: //-Y
            w = copy.w + copy.y;
            x = copy.x - copy.z;
            y = copy.y - copy.w;
            z = copy.z + copy.x;
            break;
        case 0b0010: //+Z
            w = copy.w - copy.z;
            x = copy.x - copy.y;
            y = copy.y + copy.x;
            z = copy.z + copy.w;
            break;
        case 0b0011: //-Z
            w = copy.w + copy.z;
            x = copy.x + copy.y;
            y = copy.y - copy.x;
            z = copy.z - copy.w;
            break;

            //div by 2 cases
        case 0b11000: //+X
            w = copy.w - copy.x >> 1;
            x = copy.x + copy.w >> 1;
            y = copy.y - copy.z >> 1;
            z = copy.z + copy.y >> 1;
            break;
        case 0b11001: //-X
            w = copy.w + copy.x >> 1;
            x = copy.x - copy.w >> 1;
            y = copy.y + copy.z >> 1;
            z = copy.z - copy.y >> 1;
            break;
        case 0b10100: //+Y
            w = copy.w - copy.y >> 1;
            x = copy.x + copy.z >> 1;
            y = copy.y + copy.w >> 1;
            z = copy.z - copy.x >> 1;
            break;
        case 0b10101: //-Y
            w = copy.w + copy.y >> 1;
            x = copy.x - copy.z >> 1;
            y = copy.y - copy.w >> 1;
            z = copy.z + copy.x >> 1;
            break;
        case 0b10010: //+Z
            w = copy.w - copy.z >> 1;
            x = copy.x - copy.y >> 1;
            y = copy.y + copy.x >> 1;
            z = copy.z + copy.w >> 1;
            break;
        case 0b10011: //-Z
            w = copy.w + copy.z >> 1;
            x = copy.x + copy.y >> 1;
            y = copy.y - copy.x >> 1;
            z = copy.z - copy.w >> 1;
            break;
        default:
            //wrong rotor
            return;
            break;
        }
        printf("intermidiates       w=%d, x=%d, y=%d, z=%d\n", w, x, y, z);
        if (w < 0) { w = -w; x = -x; y = -y; z = -z; } //angels > 180*deg normalization
        if (!(x || y || z)) { w >>= 1; x >>= 1; y >>= 1; z >>= 1; } //zero degrese case additional bounding ;(
        copy.w = w; copy.x = x; copy.y = y; copy.z = z;
        this->byte = copy.byte;
    }

};


int main() {
    orientation ort;
    //printf("size = %d\n", sizeof(ort));

    //printf("%d\n", 1 >> 1);
    ort.print();
    ort.rotate(0b1001);
    ort.print();
    ort.rotate(0b1001);
    ort.print();
    ort.rotate(0b1001);
    ort.print();
    ort.rotate(0b1001);
    ort.print();
    return 0;
}
