#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdlib>

// Структура Order
struct Note {
public:
    std::string Name;
    std::string Soname;
    std::string Phone;
    unsigned BirthDay[3];
};

// Обмен значениями между двумя структурами
void SwapNotes(Note &n1, Note &n2) {
    Note t;
    t = n1;
    n1 = n2;
    n2 = t;
}

// Взятие первых чисел
int GetN(const std::string& phone, int n) {
    // Массив для хранения первых n символов
    char fn[64];
    memcpy(fn, phone.c_str(), n + sizeof(char));

    return atoi(fn);
}

// Сортировка массива по возрастанию первых трех чисел
void SortByPhone(Note notes[], unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        for (unsigned j = 0; j < size - 1; j++) {
            if (GetN(notes[j].Phone, 3) > GetN(notes[j+1].Phone, 3)) {
                SwapNotes(notes[j], notes[j+1]);
            }
        }
    }
}

// Конвертация даты в 3-интовом массиве в строку
std::string date2string(const unsigned date[3]) {
    std::stringstream ss;
    ss << date[0] << "/" << date[1] << "/" << date[2];
    return ss.str();
}

// Вывод структуры на экран
void PrintNote(const Note& note) {
    std::cout << note.Name << " "
              << note.Soname << " "
              << note.Phone << " "
              << date2string(note.BirthDay) << std::endl;
}

// определение и вывод на экран записей,
// в которых фамилия совпадает со значением, введенным с клавиатуры,
// либо сообщение об отсутствии таковых.
void Find(Note notes[], unsigned size) {
    std::string soname_to_find;
    std::cout << "Enter soname: ";
    std::cin >> soname_to_find;

    // Поиск в массиве записей с такой же фамилией
    bool found = false;
    for(unsigned i = 0; i < size; i++) {
        if(soname_to_find == notes[i].Soname) {
            found = true;
            PrintNote(notes[i]);
        }
    }

    if(!found) {
        std::cout << "No orders found\n";
    }
}

int main () {
    // Создание нового массива структур
    Note notes[4] = {
        {"Gleb", "Derevlev", "12344444", {5, 6, 1996}},
        {"Dima", "Golovin", "55500001",  {10, 4, 1995}},
        {"Andrei", "Poperechny", "321111011", {1, 6, 1996}},
        {"Alexei", "Kholodinin", "788432455", {5, 10, 1997}}
    };

    // Вывод массива структур
    std::cout << "Notes:\n";
    for(unsigned i = 0; i < 4; i++) {
        PrintNote(notes[i]);
    }

    // Сортировка массива структур и вывод на экран
    std::cout << "\nSorted by number notes:\n";
    SortByPhone(notes, 4);
    for(unsigned i = 0; i < 4; i++) {
        PrintNote(notes[i]);
    }

    // Поиск в массиве структур
    std::cout << std::endl;
    Find(notes, 4);

    return 0;
}
