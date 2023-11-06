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

        bool isButtonPressed = false;

        RECT boxRect;
        GetClientRect(GetDlgItem(hwnd, 6), &boxRect);

        HDC hdc;

        // 버튼 ID를 확인하고 원하는 작업 수행
        switch (buttonID)
        {
        case 1001: // Box 버튼
        {

        }

        case 1003:
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
                int leftLine1EndY = centerY + yOffset + 10;
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
                int rightLine1StartY = centerY + yOffset + 10;
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

                hdc = NULL;

                isButtonPressed = false;
        }
        break;

        case WM_KEYDOWN:
        {
            if (wParam == VK_LSHIFT)
            {

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

                HDC hdc = GetDC(hwnd);

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
                int leftLine1EndY = centerY + yOffset + 10;
                MoveToEx(hdc, leftLine1StartX, leftLine1StartY, NULL);
                LineTo(hdc, leftLine1EndX, leftLine1EndY );

                int leftLine2StartX = centerX - whiteWidth + xOffset;
                int leftLine2StartY = centerY - whiteHeight / 4 + yOffset;
                int leftLine2EndX = centerX + xOffset - whiteWidth / 2;
                int leftLine2EndY = centerY + yOffset;
                MoveToEx(hdc, leftLine2StartX, leftLine2StartY, NULL);
                LineTo(hdc, leftLine2EndX, leftLine2EndY);

                // '>' 만들기
                int rightLine1StartX = centerX + xOffset + whiteWidth / 2;
                int rightLine1StartY = centerY + yOffset + 10;
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

                // 왼쪽눈 깜빡
                int lefteye1StartX = centerX - whiteWidth + xOffset - 90; // 90 픽셀 왼쪽으로 이동
                int lefteye1StartY = centerY + whiteHeight / 4 + yOffset;
                int lefteye1EndX = centerX + xOffset - whiteWidth / 2 - 90; // 90 픽셀 왼쪽으로 이동
                int lefteye1EndY = centerY + yOffset;
                MoveToEx(hdc, leftLine1StartX, leftLine1StartY, NULL);
                LineTo(hdc, leftLine1EndX, leftLine1EndY);

                int lefteye2StartX = centerX - whiteWidth + xOffset - 90; // 90 픽셀 왼쪽으로 이동
                int lefteye2StartY = centerY - whiteHeight / 4 + yOffset;
                int lefteye2EndX = centerX + xOffset - whiteWidth / 2 - 90; // 90 픽셀 왼쪽으로 이동
                int lefteye2EndY = centerY + yOffset;
                MoveToEx(hdc, leftLine2StartX, leftLine2StartY, NULL);
                LineTo(hdc, leftLine2EndX, leftLine2EndY);

                // 오른쪽눈 깜빡
                int righteye1StartX = centerX + xOffset + whiteWidth / 2 + 70; // 10 픽셀 오른쪽으로 이동
                int righteye1StartY = centerY + yOffset;
                int righteye1EndX = centerX + whiteWidth + xOffset + 70; // 10 픽셀 오른쪽으로 이동
                int righteye1EndY = centerY + whiteHeight / 4 + yOffset;
                MoveToEx(hdc, rightLine1StartX, rightLine1StartY, NULL);
                LineTo(hdc, rightLine1EndX, rightLine1EndY);

                int righteye2StartX = centerX + xOffset + whiteWidth / 2 + 70; // 10 픽셀 오른쪽으로 이동
                int righteye2StartY = centerY + yOffset;
                int righteye2EndX = centerX + whiteWidth + xOffset + 70; // 10 픽셀 오른쪽으로 이동
                int righteye2EndY = centerY - whiteHeight / 4 + yOffset;
                MoveToEx(hdc, rightLine2StartX, rightLine2StartY, NULL);
                LineTo(hdc, rightLine2EndX, rightLine2EndY);

                ReleaseDC(hwnd, hdc);

                hdc = NULL;
            }
        }
        break;

        case WM_KEYUP:
        {
            if (wParam == VK_LSHIFT)
            {

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
                int leftLine1EndY = centerY + yOffset + 10;
                MoveToEx(hdc, leftLine1StartX, leftLine1StartY , NULL);
                LineTo(hdc, leftLine1EndX, leftLine1EndY);

                int leftLine2StartX = centerX - whiteWidth + xOffset;
                int leftLine2StartY = centerY - whiteHeight / 4 + yOffset;
                int leftLine2EndX = centerX + xOffset - whiteWidth / 2;
                int leftLine2EndY = centerY + yOffset;
                MoveToEx(hdc, leftLine2StartX, leftLine2StartY, NULL);
                LineTo(hdc, leftLine2EndX, leftLine2EndY);

                // '>' 만들기
                int rightLine1StartX = centerX + xOffset + whiteWidth / 2;
                int rightLine1StartY = centerY + yOffset + 10;
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

                hdc = NULL;
            }
        }
        break;

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