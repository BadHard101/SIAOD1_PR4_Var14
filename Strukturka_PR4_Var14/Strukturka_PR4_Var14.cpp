#include <iostream>
using namespace std;

//  Учет пациентов поликлиники. 
//  Структура записи о пациенте: 
//  Номер полиса, фамилия, имя, отчество, дата рождения, номер телефона, дата прививки.
//  Операции:
//  1) Заполнить запись о пациенте поликлиники с клавиатуры.
//  2) Вставить новую запись в таблицу так, чтобы записи были упорядочены по возрастанию номеров полиса(сортировку не использовать).
//  3) Удалить запись по заданному номеру полиса.
//  4) Сформировать список пациентов, не имеющих прививки.

// храним информацию о дате вакцинации
struct Tdate
{
    short day;
    short month;
    short year;
};

// ФИО пациента
struct Tfio
{
    char fam[16]; // фамилия
    char name[16]; // имя
    char patr[16]; // отчество
};

struct Tpatient
{
    long long polis_num; // номер полиса
    long long phone_num; // номер телефона
    Tfio fio; // ФИО пациента
    bool vaccine_bool; // статус прививки
    Tdate vaccine_date; // дата прививки
};

// функция ввода записи о новом пациенте
void input_patient(Tpatient& one_patient) {
    cout << "Enter the Polis of patient:" << endl;
    cin >> one_patient.polis_num;
    cout << "Enter the Phone number of patient:" << endl;
    cin >> one_patient.phone_num;
    cout << "Enter the FIO of patient:" << endl;
    cin >> one_patient.fio.fam;
    cin >> one_patient.fio.name;
    cin >> one_patient.fio.patr;
    cout << "Has the patient been vaccinated? (1 - YES, 2 - NO):" << endl;

    int ans;
    cin >> ans;
    if (ans == 1)
        one_patient.vaccine_bool = true;
    else {
        one_patient.vaccine_bool = false;
        cout << endl;
    }

    if (one_patient.vaccine_bool == true){
        cout << "Enter date of vaccination (date, month, year):" << endl;
        cin >> one_patient.vaccine_date.day;
        cin >> one_patient.vaccine_date.month;
        cin >> one_patient.vaccine_date.year;
        cout << endl;
    }
}

//функция вывода записей необходимой структуры по указателю
void output_datebase(Tpatient* clinic, int N) //1
{
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        cout << "POLIS: " << clinic[i].polis_num << endl;
        cout << "PHONE NUMBER: " << clinic[i].phone_num << endl;
        cout << "FIO: " 
            << clinic[i].fio.fam << " "
            << clinic[i].fio.name << " "
            << clinic[i].fio.patr
            << endl;
        if (clinic[i].vaccine_bool == true)
            cout << "DATE OF VACCINE: "
            << clinic[i].vaccine_date.day << "."
            << clinic[i].vaccine_date.month << "."
            << clinic[i].vaccine_date.year
            << endl;
        else
            cout << "The patient hasn't been vaccinated" << endl;
    }
    cout << endl;
}

// вставка записи о новом пациенте в базу данных по возрастанию полиса
void insert_new_patient(Tpatient*& clinic, int& N, Tpatient newclass) //2
{
    int i = 0;
    while ((i < N) && (clinic[i].polis_num < newclass.polis_num))
        i++; // ищем индекс записи с полисом по возрастанию

    N++;
    clinic = (Tpatient*)realloc(clinic, N * sizeof(Tpatient));

    // сдвигаем правую часть массива
    for (int j = N-1; j > i; j--)
        clinic[j] = clinic[j - 1];

    clinic[i] = newclass;
}

// функция удаления записи о пациенте по его полису
void delete_by_polis(Tpatient*& clinic, int& N) //3
{
    cout << "Enter Patient's Polis, info about which you want to delete:" << endl;
    long long polis_num_to_del;
    cin >> polis_num_to_del;
    cout << endl;

    for (int i = 0; i < N; i++)
    {
        if (clinic[i].polis_num == polis_num_to_del)
        {
            // сдвигаем правую часть массива влево
            for (int j = i; j < N-1; j++)
                clinic[j] = clinic[j + 1];

            N--;
        }
    }

    clinic = (Tpatient*)realloc(clinic, N * sizeof(Tpatient));
}

// формируем новую структуру невакцинированных пациентов
void not_vaccinated_form(Tpatient*& clinic, int& N, Tpatient*& not_vacined, int& n) 
{
    not_vacined = {};
    n = 0;
    for (int i = 0; i < N; i++)
    {
        if (clinic[i].vaccine_bool==0)
        {
            n++;
            not_vacined = (Tpatient*)realloc(not_vacined, n * sizeof(Tpatient));
            not_vacined[n-1] = clinic[i];
        }
    }
}

int main()
{
    
    int N = 2;
    int n = 0;
    Tpatient* clinic = new Tpatient[N];
    Tpatient* clinic_not_vaccinated = new Tpatient[n];
    Tpatient one_patient{};

    clinic[0].polis_num = 1234567812345677;
    clinic[0].phone_num = 89161192555;
    clinic[0].fio = {"Ivanov", "Ivan", "Ivanovich"};
    clinic[0].vaccine_bool = false;
    clinic[0].vaccine_date = { NULL,NULL,NULL };

    clinic[1] = 
    { 
        1234567812345679, 
        89167777777, 
        {"Petrov", "Petr", "Petrovich"}, 
        true, 
        {31, 8, 1996} 
    };

    /*
    1234567812345678
    89997772233
    Nyanners Nyan Nyanovna
    1
    22 08 2003
    */

    cout << "PR#4 Kyznecov Andrey IKBO-09-21" << endl;
    cout << "Operations:" << endl;
    while (true)
    {
        cout << "1 - Input a new patient to the structure list;" << endl;
        cout << "2 - Delete a note about patient by Polis;" << endl;
        cout << "3 - Print list of patients, whose aren't vaccinated;" << endl;
        cout << "4 - Print list of all patients in database;" << endl;
        cout << "Enter: ";
        int menu;
        cin >> menu;
        switch (menu)
        {
        case (1):
            input_patient(one_patient);
            insert_new_patient(clinic, N, one_patient);
            break;
        case (2):
            delete_by_polis(clinic, N);
            break;
        case (3):
            not_vaccinated_form(clinic, N, clinic_not_vaccinated, n);
            output_datebase(clinic_not_vaccinated, n);
            break;
        case(4):
            output_datebase(clinic, N);
            break;
        default:
            break;
        }
    }
}