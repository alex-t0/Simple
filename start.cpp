#if defined(_MSC_VER)
    #pragma execution_character_set("utf-8")
#endif

#include <iostream>
#include <vector>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void print_compiled_with()
{
    try
    {
        cout << "Compiled with: "; // << endl;
        #if defined(__clang__)
        std::cout << "Clang " << __clang_major__ << '.' << __clang_minor__ << '\n';

        #elif defined(__GNUC__) && defined(__GNUG__)   // GCC в режиме C++
            std::cout << "GCC " << __GNUC__ << '.' << __GNUC_MINOR__ << '.'
                    << __GNUC_PATCHLEVEL__ << '\n';

        #elif defined(_MSC_VER)                        // MSVC
            std::cout << "MSVC " << _MSC_VER << '\n';

        #else
            std::cout << "Unknown compiler\n";
        #endif
    }
    catch (...)
    {
        // std::exception_ptr ex = std::current_exception();
        // std::cout << "Caught exception: '" << ex.what() << "'\n";
        // std::rethrow_exception(ex);
    }
}

void setupUTF8()
{
    try {
        std::locale::global(std::locale("C.UTF-8"));   // Debian/Ubuntu
        return;
    } catch (...) { /* нет C.UTF-8 */ }

    try {
        std::locale::global(std::locale("en_US.UTF-8"));
        return;
    } catch (...) { /* нет и en_US.UTF-8 */ }

    // fallback: классическая локаль, но stdio в UTF-8
    std::locale::global(std::locale::classic());
    std::setlocale(LC_ALL, "C.UTF-8");   // для С-функций
}

int main() 
{
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    setupUTF8();
    std::ios::sync_with_stdio(false);
    std::cin.imbue(std::locale());
    std::cout.imbue(std::locale());

    print_compiled_with();

    std::vector<std::unique_ptr<int[]>> arrays;

    std::cout << "Управление массивами:" << endl;
    std::cout << "a - создать новый массив (1 000 000 элементов)" << endl;
    std::cout << "d - удалить последний массив" << endl;
    std::cout << "x - удалить все массивы и выйти" << endl;

    while (true) {
        char key;

        cin >> key;

        switch (key) {
        case 'a':
        case 'A':
            try {
                // Создаем новый массив через unique_ptr
                auto newArray = std::make_unique<int[]>(1'000'000);
                arrays.push_back(std::move(newArray));
                std::cout << "Создан массив #" << arrays.size() << " (1 000 000 элементов)\n";
            }
            catch (const std::bad_alloc& e) {
                std::cout << "Ошибка: не удалось выделить память!\n";
            }
            break;

        case 'd':
        case 'D':
            if (!arrays.empty()) {
                arrays.pop_back();
                std::cout << "Удален последний массив. Осталось: " << arrays.size() << "\n";
            }
            else {
                std::cout << "Нет массивов для удаления!\n";
            }
            break;

        case 'x':
        case 'X':
            arrays.clear(); // Удаляем все массивы
            std::cout << "Все массивы удалены. Нажмите любую клавишу для выхода...\n";
            cin.get();
            cin.get();
            return 0;

        default:
            // Игнорируем другие клавиши
            break;
        }
    }

    // cin.get();
    return 0;
}