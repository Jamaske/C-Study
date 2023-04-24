#include<iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
const string InputPath = "C:\\Users\\User\\data\\my_scripts\\C++\\inp1.txt";

int main(){

    ifstream fin;
    fin.open(InputPath);
    if (!fin.is_open()) {
        cout << "file can't open file";
        return 1;
    }

    //считаем количество слов и максимальную длину слова
    string s;
    int WordCounter = 0, MaxWordLen = -1;
    while(!fin.eof()){WordCounter++; fin >> s; MaxWordLen = max(MaxWordLen, (int) s.length());}
    fin.seekg(0,ios_base::beg);//сдвигаем каретку в начало

    //создаём массив для подсчёта количества слов разных длин заполним его со сдвигом 1 в право
    string* words = new string[WordCounter];
    int* wordLenMap = new int[MaxWordLen + 1];

    for(int i = 0; i <= MaxWordLen; i++) {wordLenMap[i] = 0;}

    int wordLen;
    while (!fin.eof()){
        fin >> s;
        wordLen = s.length();
        if (wordLen < MaxWordLen) wordLenMap[s.length() + 1]++;
    }
    fin.seekg(0,ios_base::beg);//сдвигаем каретку в начало

    //камулетивно наращиваем количество слов и получаем индексы на которых данный набор кончается со сдвигом 1 вправо
    for(int i = 1; i <= MaxWordLen; i++) wordLenMap[i] += wordLenMap[i - 1];

    //читаем файл в последний раз и расставляем слова по своим местам.
    while(!fin.eof()){
        fin >> s;
        wordLen = s.length();
        words[wordLenMap[wordLen]++] = s;
    }
    //причём после этого число по индексу длинны слов в группе будет ссылаться на индекс конца этой группы. То-есть сдвиг вправо будет невелирован


/*
    for(int i = 0; i < WordCounter; i++){
        cout << words[i] << ' ';
    }
    cout << endl;
    for(int i = 0; i < MaxWordLen  + 1; i++){

        cout << wordLenMap[i] << ' ';
    }
    cout << endl;
    */

    //создаём буквенную маску слова
    unsigned long long lattermask[WordCounter];
    int latter_code;
    for(int j,  i = 0; i < WordCounter; i++){
        lattermask[i] = 0;
        s = words[i];
        wordLen = s.length();
        for(j = 0; j < wordLen; j++){
            latter_code = s[j];
            if (65 <= latter_code && latter_code <91) latter_code -= 65;
            if (97 <= latter_code && latter_code <123) latter_code -= 97;
            switch (latter_code) {
                case 34: latter_code = 26; break;
                case 38: latter_code = 27; break;
                case 39: latter_code = 28; break;
                case 45: latter_code = 29; break;
                case 46: latter_code = 30; break;
            }

            lattermask[i] = lattermask[i] | (1 << latter_code);
        }
    }


    //перебираем сумму длин пар слов с наибольшей возможной
    int first_word_len, second_word_len,i,j, total_length;
    for(total_length = MaxWordLen << 1; total_length >= 2; total_length--){
        //среди всех доступных длин слов выбираем длины, которые в сумме дают заданную длину
        for(first_word_len = min(total_length - 1, MaxWordLen) ; (first_word_len << 1)  >= total_length - 1; first_word_len--){
            second_word_len = total_length - first_word_len;
            //среди групп попарно перебираем все пары
            for(i = wordLenMap[first_word_len - 1]; i < wordLenMap[first_word_len]; i++){
                for(j = wordLenMap[second_word_len - 1]; j < wordLenMap[second_word_len]; j++){
                    if(! (lattermask[i] & lattermask[j])){
                        cout << "answer are words: "<< words[i] << " , " << words[j] << endl << "with " << total_length << " latter sum" << endl;
                        return 0;
                    }
                }
            }
        }
    }

}

/*
template <typename T>
struct list {
    T* arr = new T[10];
    unsigned short elementSize = sizeof (T);
    unsigned  short  size = 0;
    unsigned  short buffer = 2;

    void append(T element){
        if (size < buffer) arr[size++] = element;
        else {
            unsigned short oldbuffer = buffer;
            T* oldarr = arr;//утечки не происходит

            unsigned short buffer = oldbuffer * 3 / 2 + 1;//а почему бы и нет
            T* arr = new T[buffer];
            memcpy(arr, oldarr, size * elementSize);//ух, страшно - опасно
            arr[size++] = element;

            delete[] oldarr;
        }
    }
};



template <typename elType>
void Swap( elType *arr, int i, int j) {
    elType tmp = arr[j];
    arr[j] = arr[i];
    arr[i] = tmp;
}

void PrintArr(int* arr, int len){
    for(int i = 0; i < len; i++) cout << arr[i];
}

bool stringLengthCompare(string a, string b){
    return a.length() < b.length();
}

template <typename arrelType>
void HEAP_sort(arrelType* arr, unsigned int start, unsigned int end, bool(*sortCondition)(arrelType, arrelType) = NULL) {
    //arr - массив для сортировки
    //sortCondition - функция принимаю щая два значения и возращающяя bool значения по которому будет вестись сортировка (первый "меньше" второго?)
    //start - индекс первого элемента - (вводить 0)
    //end - индекс следующий за последним (вводить длину arr)
}

template <typename arrelType>
void HEAP_sort(arrelType* &arr, unsigned int len) {

    unsigned int block_size = 1, block_start, block_sep, block_end;
    arrelType* arr2 = new arrelType[len];
    bool cur_arr= false;//in what array the latest full versions is contained. false for first, true for second
    unsigned int i, j, k;

    while(true){
        if (block_size >= len){
            //delete[] arr2;
            break;
        }

        block_end = 0;
        //сортируем все блоки из arr в arr2
        do{
            //сортируем конкретные два блока
            block_start = block_end;
            block_sep = min(block_start + block_size, len);
            block_end = min(block_sep + block_size, len);
            for(i = block_start, j = block_sep, k = block_start; i < block_sep && j < block_end;){
                if(arr[i] < arr[j]) arr2[k++] = arr[i++];
                else arr2[k++]  = arr[j++];
            }
            if (i < block_sep) memcpy(arr2 + k, arr + i, (block_sep - i) * sizeof(arrelType));
            else if (j < block_end) memcpy(arr2 + k, arr + j, (block_end - j) * sizeof(arrelType));

        }while(block_end != len);
        block_size *=2;

        if (block_size >= len) {
            //delete[] arr;
            arr = arr2;
            break;
        }

        block_end = 0;
        //сортируем все блоки из arr2 в arr
        do{
            //сортируем конкретные два блока
            block_start = block_end;
            block_sep = min(block_start + block_size, len);
            block_end = min(block_sep + block_size, len);
            for(i = block_start, j = block_sep, k = block_start; i < block_sep && j < block_end;){
                if(arr2[i] < arr2[j]) arr[k++] = arr2[i++];
                else arr[k++]  = arr2[j++];
            }
            if (i < block_sep) memcpy(arr + k, arr2 + i, (block_sep - i) * sizeof(arrelType));
            else if (j < block_end) memcpy(arr + k, arr2 + j, (block_end - j) * sizeof(arrelType));

        }while(block_end != len);
        block_size *= 2;
    }
}
*/