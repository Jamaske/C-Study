#include <iostream>
#include <cmath>
using namespace std;
#define dttp double
struct Vector{
    dttp x;
    dttp y;
    dttp z;
    Vector() {
        cin >> x >> y >> z;
    }
    Vector(dttp a,dttp b,dttp c) {
        x = a;
        y = b;
        z = c;
    }
    void print(){
        cout << x << ' ' << y << ' ' << z << endl;
    }

    Vector operator+(const Vector& V){//сумма
        return Vector(x + V.x, y + V.y, z + V.z);
    }

    Vector operator-(const Vector& V){//разность
        return Vector(x - V.x, y - V.y, z - V.z);
    }

    Vector operator-(){//обратный вектор
        return Vector(-x, -y, -z);
    }

    dttp operator*(const Vector &V){//скалярное произведение
        return (x * V.x + y * V.y + z * V.z);
    };

    Vector operator&(const Vector& V){//векторное произведение
        return Vector(y * V.z - V.y * z, x * V.z - V.x * z, x * V.y - V.x * y);
    }

    bool isZero() {//равенство
        return (x == 0) && (y == 0) && (z == 0);
    }

    bool operator||(Vector &V){//коллинеарность
        dttp temp;
        return (V.x * y * z == (temp = x * V.y * z)) && (temp == x * y * V.z);
    }

    dttp len2(){
        return (x*x + y*y + z*z);
    }

    double len1(){
        return sqrt(len2());
    }

    Vector scale(double t){
        return Vector(x * t, y * t, z * t);
    }

    Vector  normalize(){//dttp должен быть дробным
        double coef = 1/sqrt(len2());
        return scale(coef);
    }
};

struct Line{
    Vector Base;
    Vector Dir;
    bool dirIsNormalised;

    Line(dttp pointX, dttp pointY, dttp pointZ, dttp diractionX, dttp diractionY, dttp diractionZ){
        Base.x = pointX;
        Base.y = pointY;
        Base.z = pointZ;
        Dir.x = diractionX;
        Dir.y = diractionY;
        Dir.z = diractionZ;
        dirIsNormalised = (Dir*Dir == 1);
    }

    Line(){
        cin >> Base.x >> Base.y >> Base.z >> Dir.x >> Dir.y >> Dir.z;
        dirIsNormalised = (Dir*Dir == 1);
    }

    Line(Vector Point, Vector Direction){
        Base = Point;
        Dir = Direction;
    }

    void NoramlizeDirectionVector(){
        if(!dirIsNormalised) Dir.normalize();
        dirIsNormalised = true;
    }

    bool isParallel(Line &L){
        return (Dir & L.Dir).isZero();
    }

    double dist1(Vector &V){//расстояние от прямой до точки
        Vector RotationAxis = (V - Base) & Dir;
        double dist;
        if(RotationAxis.x == 0 && RotationAxis.y == 0) dist = RotationAxis.z;
        else dist = RotationAxis.len1();

        if(!dirIsNormalised) dist /= Dir.len1();
        return dist;
    }

    double dist1(Line &L){//расстояние от прямой до прямой
        return (Base - L.Base) * (Dir & L.Dir).normalize();
    }
    
};

struct Plane{
    Vector Base;
    Vector Normal;
    bool normalIsNormalized;
    Plane(dttp pointX, dttp pointY, dttp pointZ, dttp normalX, dttp normalY, dttp normalZ){
        Base.x = pointX;
        Base.y = pointY;
        Base.z = pointZ;
        Normal.x = normalX;
        Normal.y = normalY;
        Normal.z = normalZ;
    }

    Plane(){
        cin >> Base.x >> Base.y >> Base.z >> Normal.x >> Normal.y >> Normal.z;
    }

    void NormalizeNormalVector(){
        if(!normalIsNormalized) Normal = Normal.normalize();
        normalIsNormalized = true;
    }

    bool isParallel(Line &L){
        return (Normal * L.Dir) == 0;
    }

    bool isParallel(Plane &P){
        return (Normal & P.Normal).isZero();
    }

    double dist1(Vector &V){//расстояние от плоскости до прямой
        double dist = V * Normal;
        if(!normalIsNormalized) dist /=Normal.len1();

        return dist;
    }

    double dist1(Line &L){
        if(!isParallel(L)) return 0;
        return dist1(L.Base);
    }

    double dist1(Plane &P){
        if(!isParallel(P)) return 0;
        return dist1(P.Base);
    }

    Vector intersection(Line &L){
        if(isParallel(L)) return Vector(0, 0, 0);//я хз как обрабатывать этот случай
        double t = ((Base - L.Base) * Normal) / (L.Dir * Normal);
        return L.Base + L.Dir.scale(t);
    }

/*
    Line intersection(Plane &P){
        return Line(, Normal & P.Normal)
    }
*/


};

int main() {
    Vector A ;
    Vector B ;
    Vector C ;
    Vector D ;

    Vector AB = B - A;
    Vector BC = C - B;
    Vector CD = D - C;
    if((AB * CD) || ( (AB&CD) * BC)){//проверка на не пересечение или не перпендикулярность
        cout << "Invalid" << endl;
        return 0;
    }

    if( (AB*BC < 0) || (BC*CD < 0) ){//проверка на взаимное расположение
        cout << "Invalid" << endl;
        return 0;
    }

    cout << "Valid" << endl;
    return 0;
}