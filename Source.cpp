#include <iostream>
#include <Windows.h>

using namespace std;

static bool check_win(string grid[3][3], string player)
{
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) { return true; }
    }
    for (int j = 0; j < 3; j++)
    {
        if (grid[0][j] == player && grid[1][j] == player && grid[2][j] == player) { return true; }
    }
    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) { return true; }
    if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player) { return true; }

    return false;
}

static bool check_draw(string grid[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == " ") { return false; }
        }
    }
    return true;
}

static void SHOW_GRID(string grid[3][3])
{
    cout << endl << "--1-2-3-" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << i + 1 << "|";
        for (int j = 0; j < 3; j++) { cout << grid[i][j] << "|"; }
        cout << endl << "--------" << endl;
    }
}

static bool is_valid_coordinate(int x, int y, string grid[3][3])
{
    if (x < 1 || x > 3 || y < 1 || y > 3)
    {
        cout << "Ошибка: координаты должны быть в диапазоне от 1 до 3!" << endl;
        return false;
    }
    if (grid[y - 1][x - 1] != " ")
    {
        cout << "Ошибка: эта клетка уже занята!" << endl;
        return false;
    }

    return true;
}

static void handleInputError() {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Ошибка: введите числовые значения!" << endl;
}

int main()
{
    SetConsoleOutputCP(1251); SetConsoleCP(1251);
    int next_game = 0, score_X = 0, score_O = 0;
    cout << "Счёт" << endl << "(Крестики:" << score_X << ") - (Нолики:" << score_O << ")" << endl;

    do
    {
        string X_name = "крестик", O_name = "нолик", X = "x", O = "o";
        int first = 0, step = 0, x = 0, y = 0;
        string Grid[3][3] = { {" "," "," "} ,{" "," "," "} ,{" "," "," "} };
        bool set = false;

        while (step < 9 && (check_win(Grid, "o") == false && check_win(Grid, "x") == false))
        {
            SHOW_GRID(Grid);
            if (first == 0)
            {
                cout << "Выберите " << X_name << ":" << endl; first = 1;
                do
                {
                    cout << "Координата по x (1-3): "; cin >> x;
                    if (cin.fail()) { handleInputError(); continue; }
                    cout << "Координата по y (1-3): "; cin >> y;
                    if (cin.fail()) { handleInputError(); continue; }

                } while (!is_valid_coordinate(x, y, Grid));

                Grid[y - 1][x - 1] = X;
                if (check_win(Grid, "x"))
                {
                    SHOW_GRID(Grid); cout << "X Выиграли!" << endl;
                    score_X++;
                }
            }
            else
            {
                cout << "Выберите " << O_name << ":" << endl; first = 0;
                do
                {
                    cout << "Координата по x (1-3): "; cin >> x;
                    if (cin.fail()) { handleInputError(); continue; }
                    cout << "Координата по y (1-3): "; cin >> y;
                    if (cin.fail()) { handleInputError(); continue; }
                } while (!is_valid_coordinate(x, y, Grid));

                Grid[y - 1][x - 1] = O;
                if (check_win(Grid, "o"))
                {
                    SHOW_GRID(Grid); cout << "O Выиграли!" << endl;
                    score_O++;
                }
            }

            if (check_draw(Grid) && !check_win(Grid, "o") && !check_win(Grid, "x"))
            {
                SHOW_GRID(Grid); cout << "Ничья!" << endl;
            }
            step++;

        }
        cout << "Счёт" << endl << "(Крестики:" << score_X << ") - (Нолики:" << score_O << ")" << endl;
        cout << "Играть ещё?" << endl << "(1 - да)" << endl << "(2 - нет)" << endl << "Ввод: ";
        cin >> next_game;
    } while (next_game == 1);
    return 0;
}