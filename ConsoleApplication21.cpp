//
//  main.cpp
//  variant_54
//
//  Created by Rinat on 22.04.2024.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <windows.h>
#include <algorithm>
#include <fstream>

using namespace std;

struct subject {
    string name = "пустой-предмет";
    short mark;
};

class Student {
public:
    string zachetka;
    string surname;
    string name;
    string patronymic;
    short dd;
    short mm;
    short yyyy;
    bool IsMale;
    short entrance_year;
    string institute;
    string kafedra;
    string group;
    subject subjects[9][10];

    Student() {
    }

    Student(string zachetka, string surname, string name, string patronymic, short dd, short mm, short yyyy, bool isMale, short entranceYear, string institute, string kafedra, string group) {
        Student();
        this->zachetka = zachetka;
        this->surname = surname;
        this->name = name;
        this->patronymic = patronymic;
        this->dd = dd;
        this->mm = mm;
        this->yyyy = yyyy;
        this->IsMale = isMale;
        this->entrance_year = entranceYear;
        this->institute = institute;
        this->kafedra = kafedra;
        this->group = group;

    }

    ~Student() {
    }
};

bool check_name(const char name[31])
{
    for (int i = 0; i < 31; i++)
    {
        if (name[i] == '0' || name[i] == '1' || name[i] == '2' || name[i] == '3' || name[i] == '4' || name[i] == '5' || name[i] == '6' || name[i] == '7' || name[i] == '8' || name[i] == '9')
        {
            return false;
        }
    }
    return true;
}

// создание журнала с оценками для каждого студента по сессиям
void init_students_subjects(vector <Student>& students) {
    for (int i = 0; i < students.size(); i++) {
        for (int a = 0; a < 9; a++)
        {
            for (int b = 0; b < 10; b++)
            {
                // Название предмета
                students[i].subjects[a][b].name = "Предмет_" + to_string(b + 1);
                // Случайная оценка от 1 до 6
                students[i].subjects[a][b].mark = ((double)rand() / RAND_MAX) * (6 - 1) + 1;
            }
        }
    }
}

struct StudentWithAvgMark {
    Student student;
    double avgMarkInSession;
};

// Отсортировать группу по успеваемости в каждой сессии или вводимой по требованию пользователя, с поиском среди лиц определенного пола.
void variant_54(vector <Student>& students, string group_name, short session_number, bool IsMale) {
    init_students_subjects(students);

    vector <StudentWithAvgMark> group;

    for (int i = 0; i < students.size(); i++) {
        if (students[i].group == group_name && students[i].IsMale == IsMale) {
            group.push_back({ students[i], 0 });
        }
    }

    if (session_number == 0) {
        // проходим по каждой сессии
        for (int a = 0; a < 9; a++) {
            // подсчитываем среднюю оценку у каждого студента в текущей сессии
            for (int i = 0; i < group.size(); i++) {
                int sumMark = 0;
                // подсчитываем сумму оценок по всем предметам
                for (int b = 0; b < 10; b++) {
                    sumMark += group[i].student.subjects[a][b].mark;
                }
                // вычисляем среднюю оценку
                group[i].avgMarkInSession = sumMark / 10;
            }
            sort(group.begin(), group.end(), [](StudentWithAvgMark x, StudentWithAvgMark y) {
                return x.avgMarkInSession < y.avgMarkInSession;
                });
            cout << "- сессия " << a + 1 << " - успеваемость" << endl;
            for (int i = 0; i < group.size(); i++) {
                cout << group[i].student.zachetka << " / " << group[i].student.surname << " " << group[i].student.name << " / " << group[i].student.institute << " " << group[i].student.group << "/ средняя оценка: " << group[i].avgMarkInSession << endl;
            }
        }
    }
    else {
        // подсчитываем среднюю оценку у каждого студента в текущей сессии
        for (int i = 0; i < group.size(); i++) {
            int sumMark = 0;
            // подсчитываем сумму оценок по всем предметам
            for (int b = 0; b < 10; b++) {
                sumMark += group[i].student.subjects[session_number][b].mark;
            }
            // вычисляем среднюю оценку
            group[i].avgMarkInSession = sumMark / 10;
        }
        sort(group.begin(), group.end(), [](StudentWithAvgMark x, StudentWithAvgMark y) {
            return x.avgMarkInSession < y.avgMarkInSession;
            });
        cout << "- семестр " << session_number << " - успеваемость" << endl;
        for (int i = 0; i < group.size(); i++) {
            cout << group[i].student.zachetka << " / " << group[i].student.surname << " " << group[i].student.name << " / " << group[i].student.institute << " " << group[i].student.group << "/ средняя оценка: " << group[i].avgMarkInSession << endl;
        }
    }
}

void loadFromFile(vector <Student>& students) {
    setlocale(LC_ALL, "ru");
    string path = "students.csv";
    ifstream fin;
    fin.open(path);
    if (!fin.is_open())
    {
        cout << "Ошибка открытия файла" << endl;
    }
    else
    {
        cout << "Файл открыт! " << endl;
        string str;
        int i = 0;
        while (!fin.eof())
        {
            str = "";
            getline(fin, str);


            int cur_pos = 0;
            int glob_pos = 0;
            string st[12];
            for (int j = 0; j < 12; j++) {
                string part = str.substr(glob_pos, str.length()); // возращает подстроку
                cur_pos = part.find(";");
                glob_pos = glob_pos + cur_pos + 1;
                st[j] = part.substr(0, cur_pos);
            }

            Student student;
            student.zachetka = st[0];
            student.surname = st[1];
            student.name = st[2];
            student.patronymic = st[3];
            student.dd = stoi(st[4]);
            student.mm = stoi(st[5]);
            student.yyyy = stoi(st[6]);
            student.IsMale = st[7] == "М";
            student.entrance_year = stoi(st[8]);
            student.institute = st[9];
            student.kafedra = st[10];
            student.group = st[11];
            students.push_back(student);
        }
    }
    fin.close();
}

int main()
{
    SetConsoleCP(1251); SetConsoleOutputCP(1251);

    vector <Student> students;

    loadFromFile(students);
    /*
    students.push_back({ "22Б1234", "Иванов", "Иван", "Иванович", 1, 1, 2004, true, 2022, "ИКБ", "КБ-1", "БАСО-02-22" });
    students.push_back({ "21Б9876", "Смирнов", "Андрей", "Вячеславович", 8, 7, 2003, true, 2021, "ИКБ", "КБ-2", "БАСО-02-22" });
    students.push_back({ "18Т1222", "Раневская", "Светлана", "Петровна", 22, 5, 2002, false, 2018, "ИКБ", "КБ-1", "БАСО-02-22" });
    students.push_back({ "18Т1256", "Контейнеров", "Александр", "Ильич", 9, 12, 2000, true, 2018, "ИКБ", "КБ-1", "БАСО-02-22" });
    students.push_back({ "20Т3671", "Светлакова", "Лариса", "Васильевна", 12, 7, 2001, false, 2020, "ИКБ", "КБ-1", "БАСО-02-22" });
    students.push_back({ "19Т8375", "Казанова", "Юлия", "Сергееевна", 1, 8, 2002, false, 2019, "ИКБ", "КБ-1", "БАСО-02-22" });

    students.push_back({ "22Б7642", "Николаев", "Кондратий", "Авдеевич", 2, 3, 2004, true, 2022, "ИИИ", "ИИИ-3", "ИИСО-01-22" });
    students.push_back({ "22Б1113", "Сергеев", "Харитон", "Эдуардович", 19, 4, 2002, true, 2022, "ИИТ", "ИК-11", "ИИСО-01-22" });
    students.push_back({ "21Б4444", "Пономарёв", "Арсен", "Данилович", 20, 1, 2003, true, 2021, "ИКБ", "КБ-1", "ИИСО-01-22" });
    students.push_back({ "21Б2642", "Владимирова", "Эстелла", "Анатольевна", 2, 3, 2004, false, 2022, "ИИИ", "ИИИ-3", "ИИСО-01-22" });
    students.push_back({ "22Б1223", "Шашкова", "Ирэна", "Эльдаровна", 11, 6, 2004, false, 2022, "ИИТ", "ИК-11", "ИИСО-01-22" });
    students.push_back({ "21Б2321", "Морозова", "Фия", "Петровна", 10, 10, 2003, false, 2021, "ИКБ", "КБ-1", "ИИСО-01-22" });

    students.push_back({ "22Б9235", "Маслов", "Натан", "Геннадьевич", 6, 7, 2004, true, 2022, "ИКБ", "КБ-1", "БСБО-01-22" });
    students.push_back({ "19Б6325", "Блинов", "Степан", "Агафонович", 8, 7, 2001, true, 2019, "ИКБ", "КБ-2", "БСБО-01-22" });
    students.push_back({ "20Б3434", "Федотов", "Кирилл", "Вадимович", 8, 3, 2002, true, 2020, "ИТУ", "ИТУ-2", "БСБО-01-22" });
    students.push_back({ "20Б8888", "Зыков", "Леонард", "Павлович", 19, 12, 2002, true, 2020, "ИКБ", "КБ-2", "БСБО-01-22" });
    students.push_back({ "19Б9325", "Белякова", "Эллада", "Семёновна", 8, 7, 2001, false, 2019, "ИКБ", "КБ-2", "БСБО-01-22" });
    students.push_back({ "20Б3455", "Колесникова", "Лариса", "Тихоновна", 25, 10, 2002, false, 2020, "ИТУ", "ИТУ-2", "БСБО-01-22" });
    students.push_back({ "20Б8899", "Новикова", "Анжелика", "Матвеевна", 12, 11, 2002, false, 2019, "ИКБ", "КБ-2", "БСБО-01-22" });
    */

    short action;
    while (true)
    {
        cout << endl << "------ главное меню ------" << endl;
        cout << "0. выход из программы" << endl;
        cout << "1. печать всех студентов" << endl;
        cout << "2. печать студента" << endl;
        cout << "3. создание студента" << endl;
        cout << "4. изменение успеваемости студента" << endl;
        cout << "5. удаление студента" << endl;
        cout << "6. индивидуальное задание" << endl;
        cout << "7. изменить студента" << endl;
        cout << "выберите действие: ";
        cin >> action;
        while (action < 0 || action > 8)
        {
            cout << "ошибка! такого действия не существует" << endl;
            cout << "выберите действие: ";
            cin >> action;
        }
        if (action == 0)
        {
            system("cls");
            exit(0);
        }
        else if (action == 1)
        {
            cout << endl << "------ печать всех студентов ------" << endl;
            cout << "список всех студентов: " << endl;

            for (int i = 0; i < students.size(); i++)
            {
                cout << students[i].zachetka << " / " << students[i].surname << " " << students[i].name << " " << students[i].patronymic << " / " << students[i].institute << " " << students[i].group << endl;
            }
            cout << endl;
        }
        else if (action == 2)
        {
            string input;
            short temp_short = -1;
            cout << endl << "------ печать студента ------" << endl;
            cout << "напишите номер зачётной книжки студента: ";
            cin >> input;
            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].zachetka == input)
                {
                    temp_short = i;
                }
            }
            if (temp_short >= 0)
            {
                cout << endl << "--- информация о студенте ---" << endl;
                cout << "фио: " << students[temp_short].surname << " " << students[temp_short].name << " " << students[temp_short].patronymic << endl;
                cout << "дата рождения: " << students[temp_short].dd << "." << students[temp_short].mm << "." << students[temp_short].yyyy << endl;
                if (students[temp_short].IsMale)
                {
                    cout << "пол: мужской" << endl;
                }
                else 
                {
                    cout << "пол: женский" << endl;
                }
                cout << "поступил: " << students[temp_short].entrance_year << endl;
                cout << "институт: " << students[temp_short].institute << endl;
                cout << "кафедра: " << students[temp_short].kafedra << endl;
                cout << "группа : " << students[temp_short].group << endl;
                cout << "-- успеваемость студента --" << endl;
                for (int a = 0; a < 9; a++)
                {
                    if (students[temp_short].subjects[a][0].name == "пустой-предмет")
                    {
                        continue;
                    }
                    cout << "- семестр " << a + 1 << " -" << endl;
                    for (int b = 0; b < 10; b++)
                    {
                        cout << students[temp_short].subjects[a][b].name << ": ";
                        if (students[temp_short].subjects[a][b].mark == 0)
                        {
                            cout << "оценки нет" << endl;
                        }
                        else if (students[temp_short].subjects[a][b].mark == 1)
                        {
                            cout << "незачёт" << endl;
                        }
                        else if (students[temp_short].subjects[a][b].mark > 1 && students[temp_short].subjects[a][b].mark < 6)
                        {
                            cout << students[temp_short].subjects[a][b].mark << endl;
                        }
                        else if (students[temp_short].subjects[a][b].mark == 6)
                        {
                            cout << "зачёт" << endl;
                        }
                    }
                }
                cout << "-- конец успеваемости --" << endl;
            }
            else
            {
                cout << "студент с зачётной книжкой №" << input << " не найден!" << endl;
            }
        }
        else if (action == 3)
        {
            string temp_str;
            Student* temp_student = new Student;
            cout << endl << "------ создание студента ------" << endl;
            cout << "введите номер зачётной книжки: ";
            cin >> temp_student->zachetka;
            cout << "введите фамилию (макс. 30 символов): ";
            cin >> temp_str;
            while (temp_str.size() >= 31 || !check_name(temp_str.c_str()))
            {
                cout << "ошибка: либо введены цифры, либо слишком большая длина" << endl;
                cout << "попробуйте ещё раз: ";
                cin >> temp_str;
            }
            temp_student->surname = temp_str;
            cout << "введите имя (макс. 30 символов): ";
            cin >> temp_str;

            while (temp_str.size() >= 31 || !check_name(temp_str.c_str()))
            {
                cout << "ошибка: либо введены цифры, либо слишком большая длина" << endl;
                cout << "попробуйте ещё раз: ";
                cin >> temp_str;
            }
            temp_student->name = temp_str;
            cout << "введите отчество (макс. 30 символов): ";
            cin >> temp_str;
            while (temp_str.size() >= 31 || !check_name(temp_str.c_str()))
            {
                cout << "ошибка: либо введены цифры, либо слишком большая длина" << endl;
                cout << "попробуйте ещё раз: ";
                cin >> temp_str;
            }
            temp_student->patronymic = temp_str;
            cout << "введите день рождения (именно день): ";
            cin >> temp_student->dd;
            cout << "введите месяц рождения: ";
            cin >> temp_student->mm;
            cout << "введите год рождения: ";
            cin >> temp_student->yyyy;
            if (temp_student->dd <= 0)
            {
                temp_student->dd = 1;
            }
            if (temp_student->mm <= 0)
            {
                temp_student->mm = 1;
            }
            if (temp_student->yyyy <= 0)
            {
                temp_student->yyyy = 2000;
            }
            if (temp_student->mm == 2 && temp_student->dd > 28)
            {
                temp_student->dd = 28;
            }
            else if ((temp_student->mm == 4 || temp_student->mm == 6 || temp_student->mm == 9 || temp_student->mm == 11) && temp_student->dd > 30)
            {
                temp_student->dd = 30;
            }
            else if ((temp_student->mm == 1 || temp_student->mm == 3 || temp_student->mm == 5 || temp_student->mm == 7 || temp_student->mm == 8 || temp_student->mm == 10 || temp_student->mm == 12) && temp_student->dd > 31)
            {
                temp_student->dd = 31;
            }
            cout << "введите год рождения: ";
            cin >> temp_student->entrance_year;
            cout << "введите пол студента (м/ж): ";
            cin >> temp_str;
            while (temp_str != "м" && temp_str != "ж")
            {
                if (temp_str == "м")
                {
                    temp_student->IsMale = true;
                }
                else if (temp_str == "ж")
                {
                    temp_student->IsMale = false;
                }
                else
                {
                    cout << "ошибка: введён несущесвтующий пол, попробйте снова (м/ж): ";
                    cin >> temp_str;
                }
            }
            cout << "введите название института: ";
            cin >> temp_student->institute;
            cout << "введите название кафедры: ";
            cin >> temp_student->kafedra;
            cout << "введите название группы: ";
            cin >> temp_student->group;
            students.push_back(*temp_student);
            cout << "студент добавлен!" << endl << endl;
            delete temp_student;
        }
        else if (action == 4)
        {
            string input;
            short temp_short = -1;
            cout << endl << "------ изменение успеваемости студента ------" << endl;
            cout << "напишите номер зачётной книжки студента: ";
            cin >> input;
            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].zachetka == input)
                {
                    temp_short = i;
                }
            }
            if (temp_short >= 0)
            {
                string input_name;
                short input_mark;
                string sub_action;
                for (int a = 0; a < 9; a++)
                {
                    if (students[temp_short].subjects[a][0].name == "пустой-предмет")
                    {
                        cout << endl << "хотите изменить оценки в семестре " << a + 1 << " (да/нет)? ";
                        cin >> sub_action;
                        while (sub_action != "да" && sub_action != "нет")
                        {
                            cout << "ошибка: введено неподходящее значение, попробуйте ещё раз (да/нет): ";
                            cin >> sub_action;
                        }
                        if (sub_action == "да")
                        {
                            for (int b = 0; b < 10; b++)
                            {
                                cout << endl;
                                cout << "изменить предмет '" << students[temp_short].subjects[a][b].name << "'?" << endl;
                                cout << "напишите '-', если не хотите менять" << endl;
                                cout << "если хотите изменить, напишите название (пишите без пробелов чтобы не было ошибки): ";
                                cin >> input_name;
                                if (input_name != "-")
                                {
                                    students[temp_short].subjects[a][b].name = input_name;
                                }
                                cout << endl;
                                cout << "изменить оценку по предмету '" << students[temp_short].subjects[a][b].name << "'?" << endl;
                                cout << "напишите '0', если не хотите менять" << endl;
                                cout << "если хотите изменить, напишите оценку (2-5, 1 - незачёт, 6 - зачёт): ";
                                cin >> input_mark;
                                while (input_mark < 1 && input_mark > 6)
                                {
                                    cout << "ошибка: введено значение вне предела, попробуйте ещё раз (2-5, 1 - незачёт, 6 - зачёт): ";
                                }
                                students[temp_short].subjects[a][b].mark = input_mark;
                            }
                        }
                    }
                }
            }
            else
            {
                cout << "студент с зачётной книжкой №" << input << " не найден!" << endl;
            }
        }
        else if (action == 5)
        {
            short temp_short = -1;
            string input;
            cout << endl << "------ удаление студента ------" << endl;
            cout << "напишите номер зачётной книжки студента: ";
            cin >> input;
            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].zachetka == input)
                {
                    temp_short = i;
                    students.erase(students.begin() + i);
                }
            }
            if (temp_short == -1)
            {
                cout << "студент с зачётной книжкой №" << input << " не найден!" << endl;
            }
        }
        else if (action == 6) {
            string group_name;
            short session_number = 0;
            string gender_name;
            bool IsMale;

            cout << endl << "------ индивидуальное задание ------" << endl;
            cout << "Отсортировать группу по успеваемости в каждой сессии или вводимой по требованию пользователя, с поиском среди лиц определенного пола." << endl;

            cout << "введите название группы: ";
            cin >> group_name;

            cout << "введите номер сессии от 1 до 9 (0 сортировать по всем сессиям):";
            cin >> session_number;
            while (session_number < 0 || session_number > 9) {
                cout << "ошибка: ввёден некорректный номер сессии, попробуйте ещё раз от 1 до 9 (0 сортировать по всем сессиям): ";
                cin >> session_number;
            }

            cout << "введите пол интересующих студентов (м/ж): ";
            cin >> gender_name;
            while (gender_name != "м" && gender_name != "ж")
            {
                cout << "ошибка: ввёден несуществующий пол, попробуйте ещё раз (м/ж): ";
                cin >> gender_name;
            }
            if (gender_name == "м")
            {
                IsMale = true;
            }
            else
            {
                IsMale = false;
            }

            variant_54(students, group_name, session_number, IsMale);
        }
        else if (action == 7)
        {
            string input;
            short temp_short = -1;
            cout << endl << "------ изменение студента ------" << endl;
            cout << "напишите номер зачётной книжки студента: ";
            cin >> input;
            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].zachetka == input)
                {
                    temp_short = i;
                }
            }
            if (temp_short >= 0)
            {
                string temp_str;
                short temp_short2;
                cout << "введите номер зачётной книжки (+ если не хотите менять): ";
                cin >> temp_str;
                if (temp_str != "+")
                {
                    students[temp_short].zachetka = temp_str;
                }
                cout << "введите фамилию (+ если не хотите менять, макс. 30 символов): ";
                cin >> temp_str;
                while (temp_str.size() >= 31 || !check_name(temp_str.c_str()))
                {
                    cout << "ошибка: либо введены цифры, либо слишком большая длина" << endl;
                    cout << "попробуйте ещё раз: ";
                    cin >> temp_str;
                }
                if (temp_str != "+")
                {
                    students[temp_short].surname = temp_str;
                }
                cout << "введите имя (+ если не хотите менять, макс. 30 символов): ";
                cin >> temp_str;
                while (temp_str.size() >= 31 || !check_name(temp_str.c_str()))
                {
                    cout << "ошибка: либо введены цифры, либо слишком большая длина" << endl;
                    cout << "попробуйте ещё раз: ";
                    cin >> temp_str;
                }
                if (temp_str != "+")
                {
                    students[temp_short].name = temp_str;
                }
                cout << "введите отчество (+ если не хотите менять, макс. 30 символов): ";
                cin >> temp_str;
                while (temp_str.size() >= 31 || !check_name(temp_str.c_str()))
                {
                    cout << "ошибка: либо введены цифры, либо слишком большая длина" << endl;
                    cout << "попробуйте ещё раз: ";
                    cin >> temp_str;
                }
                if (temp_str != "+")
                {
                    students[temp_short].patronymic = temp_str;
                }
                cout << "введите день рождения (именно день) (0 если не хотите менять): ";
                cin >> temp_short2;
                if (temp_short2 != 0)
                {
                    students[temp_short].dd = temp_short2;
                }
                cout << "введите месяц рождения (0 если не хотите менять): ";
                cin >> temp_short2;
                if (temp_short2 != 0)
                {
                    students[temp_short].mm = temp_short2;
                }
                cout << "введите год рождения (0 если не хотите менять): ";
                cin >> temp_short2;
                if (temp_short2 != 0)
                {
                    students[temp_short].yyyy = temp_short2;
                }
                if (students[temp_short].dd <= 0)
                {
                    students[temp_short].dd = 1;
                }
                if (students[temp_short].mm <= 0)
                {
                    students[temp_short].mm = 1;
                }
                if (students[temp_short].yyyy <= 0)
                {
                    students[temp_short].yyyy = 2000;
                }
                if (students[temp_short].mm == 2 && students[temp_short].dd > 28)
                {
                    students[temp_short].dd = 28;
                }
                else if ((students[temp_short].mm == 4 || students[temp_short].mm == 6 || students[temp_short].mm == 9 || students[temp_short].mm == 11) && students[temp_short].dd > 30)
                {
                    students[temp_short].dd = 30;
                }
                else if ((students[temp_short].mm == 1 || students[temp_short].mm == 3 || students[temp_short].mm == 5 || students[temp_short].mm == 7 || students[temp_short].mm == 8 || students[temp_short].mm == 10 || students[temp_short].mm == 12) && students[temp_short].dd > 31)
                {
                    students[temp_short].dd = 31;
                }
                cout << "введите год поступления (0 если не хотите менять): ";
                cin >> temp_short2;
                if (temp_short2 != 0)
                {
                    students[temp_short].entrance_year = temp_short2;
                }
                cout << "введите пол студента (м/ж) (+ если не хотите менять): ";
                cin >> temp_str;
                while (temp_str != "м" && temp_str != "ж" && temp_str != "+")
                {
                    if (temp_str == "м")
                    {
                        students[temp_short].IsMale = true;
                    }
                    else if (temp_str == "ж")
                    {
                        students[temp_short].IsMale = false;
                    }
                    else if (temp_str == "+") {}
                    else
                    {
                        cout << "ошибка: введён несущесвтующий пол, попробйте снова (м/ж): ";
                        cin >> temp_str;
                    }
                }
                cout << "введите название института (+ если не хотите менять): ";
                cin >> temp_str;
                if (temp_str != "+")
                {
                    students[temp_short].institute = temp_str;
                }
                cout << "введите название кафедры (+ если не хотите менять): ";
                cin >> temp_str;
                if (temp_str != "+")
                {
                    students[temp_short].kafedra = temp_str;
                }
                cout << "введите название группы (+ если не хотите менять): ";
                cin >> temp_str;
                if (temp_str != "+")
                {
                    students[temp_short].group = temp_str;
                }
            }
        }
    }
}
