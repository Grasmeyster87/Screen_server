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

    // 🔹 BFS (поиск в ширину, графы)
   {L"// BFS Graph Traversal (JS)",
    L"function bfs(graph, start) {",
    L"    let queue = [start];",
    L"    let visited = new Set([start]);",
    L"    while (queue.length) {",
    L"        let node = queue.shift();",
    L"        for (let n of graph[node]) {",
    L"            if (!visited.has(n)) {",
    L"                visited.add(n);",
    L"                queue.push(n);",
    L"            }",
    L"        }",
    L"    }",
    L"}"},

    // 🔹 DFS (рекурсивный)
    {L"// DFS Recursive (Python)",
    L"def dfs(node, visited, graph):",
    L"    if node in visited: return",
    L"    visited.add(node)",
    L"    for nei in graph[node]:",
    L"        dfs(nei, visited, graph)"},


    // 🔹 Динамическое программирование (рюкзак)
   {
    L"// Knapsack DP (C++)",
    L"int knapsack(vector<int>& w, vector<int>& v, int W) {",
    L"    int n = w.size();",
    L"    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));",
    L"    for (int i = 1; i <= n; i++)",
    L"        for (int j = 0; j <= W; j++)",
    L"            if (w[i-1] <= j)",
    L"                dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i-1]] + v[i-1]);",
    L"            else",
    L"                dp[i][j] = dp[i-1][j];",
    L"    return dp[n][W];",
    L"}"},

    // 🔹 Алгоритм Кнута-Морриса-Пратта (поиск строки)
    {L"// KMP String Search (JS)",
    L"function kmp(text, pattern) {",
    L"    let lps = new Array(pattern.length).fill(0);",
    L"    for (let i = 1, j = 0; i < pattern.length;) {",
    L"        if (pattern[i] === pattern[j]) lps[i++] = ++j;",
    L"        else if (j) j = lps[j-1];",
    L"        else lps[i++] = 0;",
    L"    }",
    L"}"},

    // 🔹 Дейкстра (кратчайший путь)
    {L"// Dijkstra (Python)",
    L"import heapq",
    L"def dijkstra(graph, start):",
    L"    dist = {v: float('inf') for v in graph}",
    L"    dist[start] = 0",
    L"    pq = [(0, start)]",
    L"    while pq:",
    L"        d, node = heapq.heappop(pq)",
    L"        for nei, w in graph[node]:",
    L"            if d + w < dist[nei]:",
    L"                dist[nei] = d + w",
    L"                heapq.heappush(pq, (dist[nei], nei))"},

    // Merge Sort (C++)
    {L"void mergeSort(vector<int>& arr) {",
     L"    if (arr.size() <= 1) return;",
     L"    int mid = arr.size() / 2;",
     L"    vector<int> left(arr.begin(), arr.begin()+mid);",
     L"    vector<int> right(arr.begin()+mid, arr.end());",
     L"    mergeSort(left); mergeSort(right);",
     L"    merge(left, right, arr);",
     L"}"},

     // Sliding Window (JS)
    { L"function maxSum(arr, k) {",
     L"    let sum = 0;",
     L"    for (let i = 0; i < k; i++) sum += arr[i];",
     L"    let max = sum;",
     L"    for (let i = k; i < arr.length; i++) {",
     L"        sum += arr[i] - arr[i-k];",
     L"        max = Math.max(max, sum);",
     L"    }",
     L"    return max;",
     L"}" },

   // Union-Find (Python)
   { L"class DSU:",
    L"    def __init__(self, n):",
    L"        self.p = list(range(n))",
    L"    def find(self, x):",
    L"        if self.p[x] != x:",
    L"            self.p[x] = self.find(self.p[x])",
    L"        return self.p[x]",
    L"    def union(self, a, b):",
    L"        self.p[self.find(a)] = self.find(b)" },

    // Two Pointers (C++)
    { L"int twoSum(vector<int>& a, int target) {",
     L"    int l = 0, r = a.size()-1;",
     L"    while (l < r) {",
     L"        int s = a[l] + a[r];",
     L"        if (s == target) return 1;",
     L"        else if (s < target) l++;",
     L"        else r--;",
     L"    }",
     L"    return 0;",
     L"}" },

     // Min Heap (C++)
    { L"#include <queue>",
    L"void heapExample() {",
    L"    std::priority_queue<int, vector<int>, greater<int>> pq;",
    L"    pq.push(5); pq.push(1); pq.push(10);",
    L"    while (!pq.empty()) {",
    L"        int x = pq.top(); pq.pop();",
    L"    }",
    L"}" },

    // Topological Sort (JS)
    { L"function topoSort(n, graph) {",
     L"    let indeg = Array(n).fill(0);",
     L"    for (let u of graph)",
     L"        for (let v of u) indeg[v]++;",
     L"",
     L"    let q = [];",
     L"    for (let i = 0; i < n; i++)",
     L"        if (indeg[i] === 0) q.push(i);",
     L"",
     L"    while (q.length) {",
     L"        let u = q.shift();",
     L"        for (let v of graph[u]) {",
     L"            if (--indeg[v] === 0) q.push(v);",
     L"        }",
     L"    }",
     L"}" },

     // Segment Tree (C++)
    { L"struct SegTree {",
     L"    vector<int> t;",
     L"    int n;",
     L"",
     L"    SegTree(int n): n(n) { t.resize(4*n); }",
     L"",
     L"    void build(vector<int>& a, int v, int l, int r) {",
     L"        if (l == r) t[v] = a[l];",
     L"        else {",
     L"            int m = (l + r) / 2;",
     L"            build(a, v*2, l, m);",
     L"            build(a, v*2+1, m+1, r);",
     L"            t[v] = t[v*2] + t[v*2+1];",
     L"        }",
     L"    }",
     L"};" },
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
