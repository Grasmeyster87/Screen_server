#include <windows.h>
#include <vector>
#include <string>

// Список твоїх шматків коду
const std::vector<std::wstring> myCode = {
    L"int main() {",
    L"std::cout << \"Hello Matrix\";",
    L"for(int i=0; i<100; ++i)",
    L"if (status == OK) break;",
    L"template <typename T>",
    L"while(!window.closed())",
    L"void quickSort(vector<int>& arr,...)",   // Быстрая сортировка (C++)
};

struct Drop {
    int x, y;
    int speed;
    std::wstring text;
};

std::vector<Drop> drops;
UINT_PTR timerID;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE: {
        // Ініціалізуємо "краплі" коду по всій ширині екрану
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        for (int i = 0; i < 30; i++) { // 30 потоків коду
            drops.push_back({ rand() % screenWidth, rand() % 800, 5 + rand() % 15, myCode[rand() % myCode.size()] });
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
                drop.text = myCode[rand() % myCode.size()];
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

        for (const auto& drop : drops) {
            TextOutW(hdc, drop.x, drop.y, drop.text.c_str(), (int)drop.text.length());
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