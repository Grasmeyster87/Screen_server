#include <windows.h>
#include <vector>
#include <string>

// Список твоїх шматків коду
const std::vector<std::vector<std::wstring>> myCodeBlocks = { 
    { L"int main() {",
    L"std::cout << \"Hello Matrix\";",
    L"for(int i=0; i<100; ++i)",
    L"if (status == OK) break;",
    L"template <typename T>",
    L"while(!window.closed())",
    L"void quickSort(vector<int>& arr,...)",   // Быстрая сортировка (C++)
    L"def is_palindrome(s): return s==s[::-1]", // Python Проверка палиндрома
    L"function isPrime(n){...}",                // JS Уникальная проверка на простое число (JS)
    L"auto evenFilter = [](const vector<int>& v){...}", // C++ Лямбда-выражение для фильтрации (C++)
    L"def fibonacci(n): yield ...",             // Python # Генератор Фибоначчи (Python)
    L"async function fetchData(url){...}"       // JS Асинхронная функция с await (JS)
},
   // Генератор Фибоначчи(Python)
    {
        L"def fibonacci(n):",
        L"    a, b = 0, 1",
        L"    for _ in range(n):",
        L"        yield a",
        L"        a, b = b, a + b"
     },
    // Асинхронная функция с await (JS)
    {L"async function fetchData(url) {",
     L"    const response = await fetch(url);",
     L"    return await response.json();",
     L"}"},

    // Быстрая сортировка (C++)
    {L"void quickSort(std::vector<int>& arr, int left, int right) {",
     L"    int i = left, j = right;",
     L"    int pivot = arr[(left + right) / 2];",
     L"    while (i <= j) {",
     L"        while (arr[i] < pivot) i++;",
     L"        while (arr[j] > pivot) j--;",
     L"        if (i <= j) std::swap(arr[i++], arr[j--]);",
     L"    }",
     L"    if (left < j) quickSort(arr, left, j);",
     L"    if (i < right) quickSort(arr, i, right);",
     L"}"},

    // 🔹 Бинарный поиск (C++)
   {L"// Binary Search (C++)",
    L"int binarySearch(const std::vector<int>& arr, int target) {",
    L"    int left = 0, right = arr.size() - 1;",
    L"    while (left <= right) {",
    L"        int mid = left + (right - left) / 2;",
    L"        if (arr[mid] == target) return mid;",
    L"        else if (arr[mid] < target) left = mid + 1;",
    L"        else right = mid - 1;",
    L"    }",
    L"    return -1;",
    L"}"},
};
/*
# Проверка палиндрома (Python)
// Быстрая сортировка (C++)
void quickSort(std::vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) std::swap(arr[i++], arr[j--]);
    }
    if (left < j) quickSort(arr, left, j);
    if (i < right) quickSort(arr, i, right);
}

def is_palindrome(s: str) -> bool:
    return s == s[::-1]

// Уникальная проверка на простое число (JS)
function isPrime(n) {
    if (n < 2) return false;
    for (let i = 2; i <= Math.sqrt(n); i++) {
        if (n % i === 0) return false;
    }
    return true;
}

// Лямбда-выражение для фильтрации (C++)
auto evenFilter = [](const std::vector<int>& v) {
    std::vector<int> res;
    for (auto x : v) if (x % 2 == 0) res.push_back(x);
    return res;
};

# Генератор Фибоначчи (Python)
def fibonacci(n):
    a, b = 0, 1
    for _ in range(n):
        yield a
        a, b = b, a + b


// Асинхронная функция с await (JS)
async function fetchData(url) {
    const response = await fetch(url);
    return await response.json();
}
*/

// 🔹 Структура Drop теперь хранит блок строк
struct Drop {
    int x, y;
    int speed;
    std::vector<std::wstring> textBlock;
};

std::vector<Drop> drops;
UINT_PTR timerID;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        // Ініціалізуємо "краплі" коду по всій ширині екрану
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        for (int i = 0; i < 30; i++) { // 30 потоків коду
            drops.push_back({ rand() % screenWidth, rand() % 800,
                              5 + rand() % 15,
                              myCodeBlocks[rand() % myCodeBlocks.size()] });
        }
        // Оновлення кожні 30 мс
        timerID = SetTimer(hWnd, 1, 30, NULL);
        break;
    }
    case WM_TIMER:
        // Рухаємо код вниз
        for (auto& drop : drops) {
            drop.y += drop.speed;
            if (drop.y > GetSystemMetrics(SM_CYSCREEN)) {
                drop.y = -20;
                drop.x = rand() % GetSystemMetrics(SM_CXSCREEN);
                drop.textBlock = myCodeBlocks[rand() % myCodeBlocks.size()];
            }
        }
        InvalidateRect(hWnd, NULL, TRUE); // Перемалювати
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Малюємо чорний фон
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
        FillRect(hdc, &ps.rcPaint, hBrush);
        DeleteObject(hBrush);

        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 255, 70)); // Матричний зелений

        // 🔹 Выводим многострочные блоки построчно
        for (const auto& drop : drops) {
            int offset = 0;
            for (const auto& line : drop.textBlock) {
                TextOutW(hdc, drop.x, drop.y + offset, line.c_str(), (int)line.length());
                offset += 16; // расстояние между строками
            }
        }

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_KEYDOWN:
    case WM_LBUTTONDOWN:
    case WM_DESTROY:
        KillTimer(hWnd, timerID);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
    // Режим конфігурації або превью ігноруємо для тестів
    if (wcsstr(lpCmdLine, L"/c") || wcsstr(lpCmdLine, L"/p")) return 0;

    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"MatrixScr";
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    RegisterClassW(&wc);

    HWND hWnd = CreateWindowExW(WS_EX_TOPMOST, L"MatrixScr", L"Code Matrix",
        WS_POPUP | WS_VISIBLE, 0, 0,
        GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, hInstance, NULL);

    ShowCursor(FALSE);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    ShowCursor(TRUE);
    return 0;
}
