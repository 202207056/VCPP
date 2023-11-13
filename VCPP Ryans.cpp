#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int margin = 8;
    int boxMargin = 12;
    int boxPadding = 12;

    HDC hdc = NULL;

    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        RECT clientRect;
        GetClientRect(hwnd, &clientRect);

        int padding = 8;

        RECT marginRect = clientRect;
        InflateRect(&marginRect, -margin, -margin);

        RECT paddingRect = marginRect;
        InflateRect(&paddingRect, -padding, -padding);

        HBRUSH backgroundColor = CreateSolidBrush(RGB(255, 240, 200));
        HPEN borderPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

        SelectObject(hdc, backgroundColor);
        SelectObject(hdc, borderPen);

        Rectangle(hdc, marginRect.left, marginRect.top, marginRect.right, marginRect.bottom);
        Rectangle(hdc, paddingRect.left, paddingRect.top, paddingRect.right, paddingRect.bottom);

        DeleteObject(backgroundColor);
        DeleteObject(borderPen);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_CREATE:
    {
        // 버튼에 이름에 맞는 ID 부여
        int buttonIDs[] = { 1001, 1002, 1003, 1004, 1005 }; // 예시 ID 값
        LPCWSTR buttonLabels[] = { L"Box", L"Circle", L"Bonobono", L"Ryan", L"Cube" };

        for (int i = 0; i < 5; i++)
        {
            CreateWindow(
                L"BUTTON",
                buttonLabels[i],
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                16 + i * (130 + 16) + margin, 25, 120, 32,
                hwnd,
                (HMENU)(buttonIDs[i]), // 버튼에 ID 부여
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );
        }

        // Box 생성
        CreateWindow(
            L"STATIC",
            L"",
            WS_CHILD | WS_VISIBLE | SS_NOTIFY,
            margin + boxMargin, 25 + 32 + boxMargin, 782 - 2 * margin - 2 * boxMargin, 435 - 25 - 32 - margin - 2 * boxMargin,
            hwnd,
            (HMENU)(6), // 기존대로
            ((LPCREATESTRUCT)lParam)->hInstance,
            NULL
        );
    }
    break;
    // 추가: 버튼 클릭 이벤트 처리
    case WM_COMMAND:
    {
        int buttonID = LOWORD(wParam);

        HDC hdc;

        // 버튼 ID를 확인하고 원하는 작업 수행
        switch (buttonID)
        {
        case 1001: // Box 버튼
        {

        }

        case 1003: //Bonobono 버튼
        {
            RECT boxRect;
            GetClientRect(GetDlgItem(hwnd, 6), &boxRect);

            int centerX = (boxRect.left + boxRect.right) / 2;
            int centerY = (boxRect.top + boxRect.bottom) / 1.4;

            int largeWidth = 350; // 큰 하늘색 원의 가로 크기 (픽셀)
            int largeHeight = 350; // 큰 하늘색 원의 세로 크기 (픽셀)
            int smallWidth = 50;  // 검은색 원의 가로 크기 (픽셀)
            int smallHeight = 45; // 검은색 원의 세로 크기 (픽셀)
            int whiteWidth = 65;  // 흰색 원의 가로 크기 (픽셀)
            int whiteHeight = 55; // 흰색 원의 세로 크기 (픽셀)
            int verticalEllipseWidth = 50; // 세로로 눕힌 타원의 가로 크기 (픽셀)
            int verticalEllipseHeight = 80; // 세로로 눕힌 타원의 세로 크기 (픽셀)
            int eyeWidth = 15;    // 눈의 가로 크기 (픽셀)
            int eyeHeight = 25;   // 눈의 세로 크기 (픽셀)
            int wheyeWidth = 5;   // 눈동자 가로
            int wheyeHeight = 10;  // 눈동자 세로

            hdc = GetDC(hwnd);

            // 큰 하늘색 원 그리기
            HBRUSH blueBrush = CreateSolidBrush(RGB(91, 155, 213));
            SelectObject(hdc, blueBrush);
            Ellipse(hdc, centerX - largeWidth / 2, centerY - largeHeight / 2, centerX + largeWidth / 2, centerY + largeHeight / 2);
            DeleteObject(blueBrush);


            // 세로로 눕힌 타원 그리기 (아래에)
            HBRUSH verticalEllipseBrush = CreateSolidBrush(RGB(251, 150, 251));
            SelectObject(hdc, verticalEllipseBrush);
            Ellipse(hdc, centerX - verticalEllipseWidth / 2, centerY - 3 + smallHeight / 2, centerX + verticalEllipseWidth / 2, centerY - 3 + smallHeight / 2 + verticalEllipseHeight);
            DeleteObject(verticalEllipseBrush);


            // 흰색 원 그리기 (왼쪽)
            HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, whiteBrush);
            Ellipse(hdc, centerX - whiteWidth, centerY - 3, centerX, centerY - 3 + whiteHeight);
            // 두 번째 흰색 원 그리기 (오른쪽에 이어붙임)
            Ellipse(hdc, centerX, centerY - 3, centerX + whiteWidth, centerY - 3 + whiteHeight);
            DeleteObject(whiteBrush);

            int xOffset = -1; // 왼쪽으로 10 픽셀 이동
            int yOffset = 20;
            float angle = 45.0f;

            // '<' 만들기
            int leftLine1StartX = centerX - whiteWidth + xOffset;
            int leftLine1StartY = centerY + whiteHeight / 4 + yOffset;
            int leftLine1EndX = centerX + xOffset - whiteWidth / 2;
            int leftLine1EndY = centerY + yOffset;
            MoveToEx(hdc, leftLine1StartX, leftLine1StartY, NULL);
            LineTo(hdc, leftLine1EndX, leftLine1EndY);

            int leftLine2StartX = centerX - whiteWidth + xOffset;
            int leftLine2StartY = centerY - whiteHeight / 4 + yOffset;
            int leftLine2EndX = centerX + xOffset - whiteWidth / 2;
            int leftLine2EndY = centerY + yOffset;
            MoveToEx(hdc, leftLine2StartX, leftLine2StartY, NULL);
            LineTo(hdc, leftLine2EndX, leftLine2EndY);

            // '>' 만들기
            int rightLine1StartX = centerX + xOffset + whiteWidth / 2;
            int rightLine1StartY = centerY + yOffset;
            int rightLine1EndX = centerX + whiteWidth + xOffset;
            int rightLine1EndY = centerY + whiteHeight / 4 + yOffset;
            MoveToEx(hdc, rightLine1StartX, rightLine1StartY, NULL);
            LineTo(hdc, rightLine1EndX, rightLine1EndY);

            int rightLine2StartX = centerX + xOffset + whiteWidth / 2;
            int rightLine2StartY = centerY + yOffset;
            int rightLine2EndX = centerX + whiteWidth + xOffset;
            int rightLine2EndY = centerY - whiteHeight / 4 + yOffset;
            MoveToEx(hdc, rightLine2StartX, rightLine2StartY, NULL);
            LineTo(hdc, rightLine2EndX, rightLine2EndY);

            // 작은 검정색 원 그리기 (중앙에)
            HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, blackBrush);
            Ellipse(hdc, centerX - smallWidth / 2, centerY - smallHeight / 2, centerX + smallWidth / 2, centerY + smallHeight / 2);


            // 왼쪽 눈 그리기 (왼쪽으로 이동)
            Ellipse(hdc, centerX - whiteWidth - eyeWidth - 50, centerY - 30 - eyeHeight / 2, centerX - whiteWidth - 50, centerY - 30 + eyeHeight / 2);
            DeleteObject(blackBrush);

            // 오른쪽 눈 그리기 (오른쪽으로 이동)
            Ellipse(hdc, centerX + whiteWidth + 50, centerY - 30 - eyeHeight / 2, centerX + whiteWidth + eyeWidth + 50, centerY - 30 + eyeHeight / 2);
            DeleteObject(blackBrush);


            // 왼쪽 눈 그리기 (왼쪽으로 이동)
            HBRUSH smallwhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, smallwhiteBrush);
            Ellipse(hdc, centerX - whiteWidth - wheyeWidth - 55, centerY - 30 - wheyeHeight / 2, centerX - whiteWidth - 55, centerY - 30 + wheyeHeight / 2);
            DeleteObject(smallwhiteBrush);

            // 오른쪽 눈 그리기 (오른쪽으로 이동)
            Ellipse(hdc, centerX + whiteWidth + 55, centerY - 30 - wheyeHeight / 2, centerX + whiteWidth + wheyeWidth + 55, centerY - 30 + wheyeHeight / 2);
            DeleteObject(smallwhiteBrush);



            ReleaseDC(hwnd, hdc);

            hdc = NULL; // hdc 초기화
        }
        break;

        case 1004:
        {
            HDC hdc;

            // 큰 주황색 원 그리기
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);

            int centerX = (clientRect.right + clientRect.left) / 2;
            int centerY = (clientRect.bottom + clientRect.top) / 1.8;

            int radius = 130; // 큰 주황색 원의 반지름

            hdc = GetDC(hwnd);

            // 왼쪽 작은 주황색 원 그리기
            int leftSmallX = centerX - radius / 6 - 90; // 왼쪽 작은 원의 중심 x 좌표
            int leftSmallY = centerY - 95; // 왼쪽 작은 원의 중심 y 좌표
            int leftSmallRadius = 42; // 왼쪽 작은 원의 반지름

            HBRUSH leftSmallBrush = CreateSolidBrush(RGB(255, 200, 15)); // 주황색 원을 나타내는 색상입니다.
            SelectObject(hdc, leftSmallBrush);
            Ellipse(hdc, leftSmallX - leftSmallRadius, leftSmallY - leftSmallRadius, leftSmallX + leftSmallRadius, leftSmallY + leftSmallRadius);
            DeleteObject(leftSmallBrush);

            // 오른쪽 작은 주황색 원 그리기
            int rightSmallX = centerX + radius / 6 + 90; // 오른쪽 작은 원의 중심 x 좌표
            int rightSmallY = centerY - 95; // 오른쪽 작은 원의 중심 y 좌표
            int rightSmallRadius = 42; // 오른쪽 작은 원의 반지름

            HBRUSH rightSmallBrush = CreateSolidBrush(RGB(255, 200, 15)); // 주황색 원을 나타내는 색상입니다.
            SelectObject(hdc, rightSmallBrush);
            Ellipse(hdc, rightSmallX - rightSmallRadius, rightSmallY - rightSmallRadius, rightSmallX + rightSmallRadius, rightSmallY + rightSmallRadius);
            DeleteObject(rightSmallBrush);

            // 큰 주황색 원 그리기
            HBRUSH orangeBrush = CreateSolidBrush(RGB(255, 200, 15));
            SelectObject(hdc, orangeBrush);
            Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
            DeleteObject(orangeBrush);

            // 중앙에 하얀색 원 그리기
            int whiteRadius = 15; // 하얀색 원의 반지름
            HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // 하얀색 원을 나타내는 색상입니다.
            SelectObject(hdc, whiteBrush);

            // 첫 번째 하얀색 원 그리기 (왼쪽으로 30만큼 이동)
            Ellipse(hdc, centerX - whiteRadius - 15, centerY - whiteRadius, centerX + whiteRadius - 15, centerY + whiteRadius);

            // 두 번째 하얀색 원 그리기 (왼쪽으로 30만큼 이동)
            Ellipse(hdc, centerX - whiteRadius + 15, centerY - whiteRadius, centerX + whiteRadius + 15, centerY + whiteRadius);

            DeleteObject(whiteBrush);

            // 중앙에 검정색 원 그리기
            int blackRadius = 8; // 검정색 원의 반지름
            HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0)); // 검정색 원을 나타내는 색상입니다.
            SelectObject(hdc, blackBrush);

            // 첫 번째 검정색 원 그리기 (위로 20만큼 이동)
            Ellipse(hdc, centerX - blackRadius - 60, centerY - blackRadius - 35, centerX + blackRadius - 60, centerY + blackRadius - 35);

            // 두 번째 검정색 원 그리기 (위로 20만큼 이동)
            Ellipse(hdc, centerX - blackRadius + 60, centerY - blackRadius - 35, centerX + blackRadius + 60, centerY + blackRadius - 35);

            DeleteObject(blackBrush);

            // 왼쪽에 "=" 모양으로 세 개의 작은 직선 그리기
            HPEN blackPenLeft = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 검은색 펜을 생성합니다.
            SelectObject(hdc, blackPenLeft);

            // 첫 번째 작은 직선 (위로 20픽셀 이동, 양쪽으로 10픽셀씩 늘림)
            MoveToEx(hdc, centerX - 32 - 50, centerY - 35 - 10 - 17, NULL);
            LineTo(hdc, centerX - 32 - 10, centerY - 35 - 10 - 17);

            // 두 번째 작은 직선 (위로 20픽셀 이동, 양쪽으로 10픽셀씩 늘림)
            MoveToEx(hdc, centerX - 32 - 50, centerY - 35 - 25, NULL);
            LineTo(hdc, centerX - 32 - 10, centerY - 35 - 25);

            // 세 번째 작은 직선 (위로 20픽셀 이동, 양쪽으로 10픽셀씩 늘림)
            MoveToEx(hdc, centerX - 32 - 50, centerY - 35 + 10 - 33, NULL);
            LineTo(hdc, centerX - 32 - 10, centerY - 35 + 10 - 33);

            DeleteObject(blackPenLeft);

            // 오른쪽에 "=" 모양으로 세 개의 작은 직선 그리기
            HPEN blackPenRight = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // 검은색 펜을 생성합니다.
            SelectObject(hdc, blackPenRight);

            // 첫 번째 작은 직선 (위로 20픽셀 이동, 양쪽으로 10픽셀씩 늘림)
            MoveToEx(hdc, centerX + 30 + 10, centerY - 35 - 10 - 17, NULL);
            LineTo(hdc, centerX + 30 + 50, centerY - 35 - 10 - 17);

            // 두 번째 작은 직선 (위로 20픽셀 이동, 양쪽으로 10픽셀씩 늘림)
            MoveToEx(hdc, centerX + 30 + 10, centerY - 35 - 25, NULL);
            LineTo(hdc, centerX + 30 + 50, centerY - 35 - 25);

            // 세 번째 작은 직선 (위로 20픽셀 이동, 양쪽으로 10픽셀씩 늘림)
            MoveToEx(hdc, centerX + 30 + 10, centerY - 35 + 10 - 33, NULL);
            LineTo(hdc, centerX + 30 + 50, centerY - 35 + 10 - 33);

            DeleteObject(blackPenRight);

            ReleaseDC(hwnd, hdc);

            hdc = NULL; // hdc 초기화
        }

        // 나머지 버튼 처리
        // ...
        }
    }
    break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"SimpleWindowClass";

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"윈도우 클래스 등록 실패!", L"에러", MB_ICONERROR);
        return 1;
    }

    HWND hwnd = CreateWindowEx(
        0,
        L"SimpleWindowClass",
        L"My Window",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 480,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd)
    {
        MessageBox(NULL, L"윈도우 생성 실패!", L"에러", MB_ICONERROR);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}