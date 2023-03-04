#include <iostream>
using namespace std;
#include <cmath>

#define dttp double
struct Vector{
    dttp x;
    dttp y;
    dttp z;

    Vector() {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector(dttp a,dttp b,dttp c) {
        x = a;
        y = b;
        z = c;
    }

    void read() {
        cin >> x >> y >> z;
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

    void read(){
        cin >> Base.x >> Base.y >> Base.z >> Dir.x >> Dir.y >> Dir.z;
        dirIsNormalised = (Dir*Dir == 1);
    }

    Line(){
        Base = Vector();
        Dir = Vector();
    }

    Line(Vector Point, Vector Direction){
        Base = Point;
        Dir = Direction;
    }

    void print(){
        cout << "Base: " << Base.x << ' ' << Base.y << ' ' << Base.z << "  Direction: " << Dir.x << ' ' << Dir.y << ' ' << Dir.z << endl;
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
        Base = Vector();
        Normal = Vector();
    }

    Plane(Vector Point, Vector normalVector){
        Base = Point;
        Normal = normalVector;
    }

    void read(){
        cin >> Base.x >> Base.y >> Base.z >> Normal.x >> Normal.y >> Normal.z;
    }

    void print(){
        cout << "Base: " << Base.x << ' ' << Base.y << ' ' << Base.z << "  Normal: " << Normal.x << ' ' << Normal.y << ' ' << Normal.z << endl;
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
        double dist = (V - Base) * Normal;
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

template <typename elType>
void QuickSort(elType *arr, int start, int end,Vector ThePoint){
    /*
     * recursive QuickSort хорошая и простая в написании сортировка
     * сложность:
     *   худшая  O(n^2)
     *   средняя O(n*log(n))
     *   лучшая  O(n*log(n))
     * память O(1)
     */
    if (start>=end){
        return;
    }
    double pivot= arr[end].dist1(ThePoint);
    int SepPointer = start;
    elType temp;
    for(int i = start; i < end; i++){
        if (arr[i].dist1(ThePoint) < pivot){
            temp = arr[i];
            arr[i] = arr[SepPointer];
            arr[SepPointer] = temp;
            SepPointer++;
        }
    }
    temp = arr[end];
    arr[end] = arr[SepPointer];
    arr[SepPointer] = temp;
    QuickSort(arr, start, SepPointer-1, ThePoint);
    QuickSort(arr, SepPointer+1, end, ThePoint);
}

int main(){
    int N;
    cin >> N;
    Plane* PlaneArr = new Plane[N];
    for(int i = 0; i < N; i++){
        PlaneArr[i].read();
    }
    Vector ThePoint;
    ThePoint.read();

    for(int i = 0; i < N; i++){
        PlaneArr[i].print();
        cout << PlaneArr[i].dist1(ThePoint) << endl;
    }

    QuickSort(PlaneArr, 0, N, ThePoint);

    for(int i = 0; i < N; i++){
        PlaneArr[i].print();
    }
}