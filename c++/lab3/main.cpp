#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

using namespace std;

enum Zodiak {
    Aquarius,
    Pisces,
    Aries,
    Taurus,
    Gemini,
    Cancer,
    Leo,
    Virgo,
    Libra,
    Scorpio,
    Sagittarius
};

const string ZodiakStrings[11] = {
    "Aquarius",
    "Pisces",
    "Aries",
    "Taurus",
    "Gemini",
    "Cancer",
    "Leo",
    "Virgo",
    "Libra",
    "Scorpio",
    "Sagittarius"
};

// Структура Знак
struct Znak {
    public:
        char name[64];
        char soname[64];
        int  sign;
        int  date[3];
};

// Конвертация даты в 3-интовом массиве в строку
std::string date2string(const int date[3]) {
    std::stringstream ss;
    ss << date[0] << "/" << date[1] << "/" << date[2];
    return ss.str();
}

// Конвертация номера знака зодиака в строку
std::string znak2string(int znak) {
    return ZodiakStrings[znak];
}

// Вывод знака
void PrintZnak(const Znak& znak) {
    std::cout << znak.name << " "
              << znak.soname << " "
              << znak2string(znak.sign-1) << " "
              << date2string(znak.date) << std::endl;
}

// Обмен значениями между структурами
void SwapZnaks (Znak &znak1, Znak &znak2) {
    Znak temp;
    temp = znak2;
    znak2 = znak1;
    znak1 = temp;
}

// Сортировка массива ы алфовитном порядке
void SortByZnak(Znak znaks[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (znaks[j].sign > znaks[j+1].sign) {
                SwapZnaks(znaks[j], znaks[j+1]);
            }
        }
    }
}

// Поиск структур
void FindMonth(Znak znaks[], int size, int month) {
    bool found = false;
    for(int i = 0; i < size; i++) {
        if(znaks[i].date[1] == month) {
            PrintZnak(znaks[i]);
            found = true;
        }
    }

    if(!found) {
        std::cout << "No znaks found\n";
    }
}

// Поиск символа в строку
const char* findsym(const char* str, char symbol) {
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        if(*str == symbol) {
            return str;
        }
        str++;
    }
    return NULL;
}

// file -- путь к файлу
// out -- массив, куда нужно записать считанные мтруктуры
// size -- максимальный размер буффера вывода
// n -- указатель, куда записать количество прочитаных структур
void ReadZnaksC(const char* file, Znak* out, int size, int *n) {
    // Открываем файл
    FILE* f = fopen(file, "r");
    if(!f) {
        std::cout << "Error opening file\n";
        exit(1);
    }

    *n = 0;
    char buffer[sizeof(Znak)];

    // Читаем файл, в одной строке по одному описанию структуры.
    while(fgets(buffer, sizeof(Znak), f) != NULL) {
        // Создаем новый знак
        Znak temp = {};

        // Указатель на имя, имя первое в строке
        const char* nptr = buffer;

        // Указатель на фамилию, фамилия -- втрое слово.
        const char* fptr = findsym(buffer, ' ') + 1;

        // Указатель на знак зодиака
        const char* zptr = findsym(fptr, ' ') + 1;

        // Указатели на числа дня рожждения
        const char* dptrd = findsym(zptr, ' ') + 1;
        const char* dptrm = findsym(dptrd, '/') + 1;
        const char* dptry = findsym(dptrm, '/') + 1;

        // Проверяем, если хоть один указатель нулевой, файл неправильный
        if(!nptr  || !fptr  || !zptr
        || !dptrd || !dptrm || !dptry) {
            std::cout << "Error parsing file\n";
            exit(2);
        }

        // Копируем строки
        strncpy(temp.name, nptr, fptr - nptr - 1);
        strncpy(temp.soname, fptr, zptr - fptr - 1);
        temp.sign = static_cast<Zodiak>(atoi(zptr));
        temp.date[0] = atoi(dptrd);
        temp.date[1] = atoi(dptrm);
        temp.date[2] = atoi(dptry);

        // Добавляем в массив
        out[(*n)++] = temp;

        if(*n == (int) size) {
            break;
        }
    }
}

// file -- путь к файлу
// out -- массив, куда нужно записать считанные мтруктуры
// size -- максимальный размер буффера вывода
// n -- указатель, куда записать количество прочитаных структур
void ReadZnaksCPP(const std::string& file, Znak* out, int size, int *n) {
    // Открываем файл
    std::ifstream f(file);

    // Проверяем открыт ли файл
    if(!f.is_open()) {
        std::cout << "Error opening file\n";
        exit(1);
    }

    // Размер массива
    *n = 0;

    // Создаем новый Машрут
    Znak temp;

    char date[10];

    // Читаем файл по слову
    while(f >> temp.name >> temp.soname >> temp.sign >> date) {
        // Парсим date
        sscanf(date, "%i/%i/%i", temp.date, temp.date+1, temp.date+2);

        // Добавляем в массив
        out[(*n)++] = temp;

        if(*n == size) {
            break;
        }
    }
}

int main() {
    // Файл с описаниями структур
    const char* filename_c = "znaks.txt";
    const std::string filename_cpp(filename_c);

    int n = 0;
    Znak znaks[10];

    // Загрузка файла С++
    ReadZnaksCPP(filename_cpp, znaks, 10, &n);

    // Вывод
    std::cout << "C++ file read:\n";
    for(int i = 0; i < n; i++) {
        PrintZnak(znaks[i]);
    }

    // Спрашиваем какой месяц надо найти
    int month;
    std::cout << "\nEnter month to find: ";
    std::cin >> month;

    // Поиск и вывод
    FindMonth(znaks, n, month);

    // Загрузка файла Си
    ReadZnaksC(filename_c, znaks, 10, &n);

    // Вывод
    std::cout << "\nC file read:\n";
    for(int i = 0; i < n; i++) {
        PrintZnak(znaks[i]);
    }

    // Сортировка и вывод
    std::cout << "\nSorted:\n";
    SortByZnak(znaks, n);
    for(int i = 0; i < n; i++) {
        PrintZnak(znaks[i]);
    }

    return 0;
}
