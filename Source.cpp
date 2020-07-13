#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include <windows.h>                   
#include <gl\glu.h>     // #include <gl\gl.h>  Заголовочный файл для OpenGL32 библиотеки
#include <tchar.h> 
#include <math.h>

HGLRC  hRC = NULL;              // Постоянный контекст рендеринга
HDC  hDC = NULL;              // Приватный контекст устройства GDI
HWND  hWnd = NULL;              // Здесь будет хранится дескриптор окна
HINSTANCE  hInstance;              // Здесь будет хранится дескриптор приложения

GLfloat	rtri;				
GLfloat	rquad;
GLfloat	Geks_size = 2.4;
GLfloat	Icos_size = 0.5;
GLfloat phi = Icos_size*((1 + sqrt(5)) / 2);

bool  keys[256]; // Массив, используемый для операций с клавиатурой
bool  active = true; // Флаг активности окна, установленный в true по умолчанию
bool  fullscreen = true; // Флаг режима окна, установленный в полноэкранный по умолчанию
LRESULT  CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Прототип функции WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) // Изменить размер и инициализировать окно GL
{
	if (height == 0) // Предотвращение деления на ноль
	{
		height = 1;
	}

	glViewport(0, 0, width, height); // Сброс текущей области вывода
	glMatrixMode(GL_PROJECTION); // Выбор матрицы проекций (применяет последующие матричные операции к стеку проекционных матриц)
	glLoadIdentity(); // Сброс матрицы проекции

	gluPerspective(70, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);//Первый параметр это охват в градусах от 0 до 180. Можете воспринимать его как обьектив на фотоаппарате. Либо все но мелкое , либо большое но одно.  Второй параметр это угол поворота по оси Y.

	glMatrixMode(GL_MODELVIEW); // Выбор матрицы вида модели(modelview)(применяет последующие матричные операции к стеку modelview)
	glLoadIdentity(); // Сброс матрицы вида модели
}

int InitGL(GLvoid)                // Все установки касаемо OpenGL происходят здесь
{
	glShadeModel(GL_SMOOTH);            // Разрешить плавное цветовое сглаживание
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);          // Очистка экрана в черный цвет
	glClearDepth(1.0f);              // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
	glDepthFunc(GL_LEQUAL);            // Тип теста глубины
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы

	return true;
}

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	//устанавливает начало системы координат в центр экрана, причем ось X идет слева направо, ось Y вверх и вниз, а ось Z к и от наблюдателя. Центр OpenGL экрана находится в точке 0, 0, 0. Координаты, расположенные слева, снизу и вглубь от него, имеют отрицательное значение, расположенные справа, сверху и по направлению к наблюдателю – положительное. 			
	
	glLoadIdentity();
	glTranslatef(1, 0.5, -6);//Функция glTranslate(x, y, z) перемещает оси координат на указанные значения. 
	glRotatef(rtri*0.5, -0.5f, 1.0f, 0.0f);//отвечает за вращения объекта вдоль оси. Угол некоторое число (обычно переменная), которое задает насколько Вы хотите повернуть объект. Xtrue, Ytrue и Ztrue или 0.0f или 1.0f. Если один из параметров равен 1.0f, OpenGL будет вращать объект вдоль соответствующей оси. Поэтому если Вы имеете glRotatef(10.0f,0.0f,1.0f,0.0f), объект будет поварачиваться на 10 градусов по оси Y. Если glRotatef(5.0f,1.0f,0.0f,1.0f), объект будет поварачиваться на 5 градусов по обеим осям X и Z. 
										   //glRotate производит вращение на заданный угол вокруг вектора (x,y,z)

	glBegin(GL_QUADS);   // КУБ

	glColor3f(1, 0, 0);											// Красный насыщенность от 0.0f до 1.0f 
	glVertex3f(-Geks_size / 2, Geks_size, Geks_size / 2);
	glVertex3f(Geks_size / 2, Geks_size, Geks_size / 2);
	glVertex3f(Geks_size / 2, 0, Geks_size / 2);
	glVertex3f(-Geks_size / 2, 0, Geks_size / 2);

	glColor3f(0, 1, 0);											// Зеленый   
	glVertex3f(-Geks_size / 2, Geks_size, -Geks_size / 2);
	glVertex3f(Geks_size / 2, Geks_size, -Geks_size / 2);
	glVertex3f(Geks_size / 2, 0, -Geks_size / 2);
	glVertex3f(-Geks_size / 2, 0, -Geks_size / 2);

	glColor3f(0, 0, 1);											// Синий  
	glVertex3f(-Geks_size / 2, Geks_size, -Geks_size / 2);
	glVertex3f(-Geks_size / 2, Geks_size, Geks_size / 2);
	glVertex3f(-Geks_size / 2, 0, Geks_size / 2);
	glVertex3f(-Geks_size / 2, 0, -Geks_size / 2);

	glColor3f(1, 1, 0);											// Желтый 
	glVertex3f(Geks_size / 2, Geks_size, -Geks_size / 2);
	glVertex3f(Geks_size / 2, Geks_size, Geks_size / 2);
	glVertex3f(Geks_size / 2, 0, Geks_size / 2);
	glVertex3f(Geks_size / 2, 0, -Geks_size / 2);

	glColor3f(1, 0, 1);											// Розовый  
	glVertex3f(-Geks_size / 2, Geks_size, -Geks_size / 2);
	glVertex3f(Geks_size / 2, Geks_size, -Geks_size / 2);
	glVertex3f(Geks_size / 2, Geks_size, Geks_size / 2);
	glVertex3f(-Geks_size / 2, Geks_size, Geks_size / 2);

	glColor3f(1, 1, 1);											// Белый  
	glVertex3f(-Geks_size / 2, 0, -Geks_size / 2);
	glVertex3f(Geks_size / 2, 0, -Geks_size / 2);
	glVertex3f(Geks_size / 2, 0, Geks_size / 2);
	glVertex3f(-Geks_size / 2, 0, Geks_size / 2);

	glEnd();
	
	rtri += 1;//скорость вращения											
	rquad -= 1;
	return true;
}

GLvoid KillGLWindow(GLvoid)              // Корректное разрушение окна
{
	if (fullscreen)              // Мы в полноэкранном режиме?
	{
		ChangeDisplaySettings(NULL, 0);        // Если да, то переключаемся обратно в оконный режим
		ShowCursor(true);            // Показать курсор мышки
	}
	if (hRC)                // Существует ли Контекст Рендеринга?
	{
		if (!wglMakeCurrent(NULL, NULL))        // Возможно ли освободить RC и DC?
		{
			MessageBox(NULL, L"Release Of DC And RC Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))        // Возможно ли удалить RC?
		{
			MessageBox(NULL, L"Release Rendering Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;              // Установить RC в NULL
	}
	if (hDC && !ReleaseDC(hWnd, hDC))          // Возможно ли уничтожить DC?
	{
		MessageBox(NULL, L"Release Device Context Failed.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;                // Установить DC в NULL
	}
	if (hWnd && !DestroyWindow(hWnd))            // Возможно ли уничтожить окно?
	{
		MessageBox(NULL, L"Could Not Release hWnd.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;                // Установить hWnd в NULL
	}
	if (!UnregisterClass(L"OpenGL", hInstance))        // Возможно ли разрегистрировать класс
	{
		MessageBox(NULL, L"Could Not Unregister Class.", L"SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;                // Установить hInstance в NULL
	}
}

BOOL CreateGLWindow(LPCTSTR title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint    PixelFormat;              // Хранит результат после поиска
	WNDCLASS  wc;                // Структура класса окна
	DWORD    dwExStyle;              // Расширенный стиль окна
	DWORD    dwStyle;              // Обычный стиль окна
	RECT WindowRect;                // Верхняя левая вершина прямоуглоьника и нижняя правая
	WindowRect.left = (long)0;              // Установить левую составляющую в 0
	WindowRect.right = (long)width;              // Установить правую составляющую в Width
	WindowRect.top = (long)0;                // Установить верхнюю составляющую в 0
	WindowRect.bottom = (long)height;              // Установить нижнюю составляющую в Height
	fullscreen = fullscreenflag;              // Устанавливаем значение глобальной переменной fullscreen
	hInstance = GetModuleHandle(NULL);        // Считаем дескриптор нашего приложения
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;      // Перерисуем при перемещении и создаём скрытый DC
	wc.lpfnWndProc = (WNDPROC)WndProc;          // Процедура обработки сообщений
	wc.cbClsExtra = 0;              // Нет дополнительной информации для окна
	wc.cbWndExtra = 0;              // Нет дополнительной информации для окна
	wc.hInstance = hInstance;            // Устанавливаем дескриптор
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);        // Загружаем иконку по умолчанию
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);        // Загружаем указатель мышки
	wc.hbrBackground = NULL;              // Фон не требуется для GL
	wc.lpszMenuName = NULL;              // Меню в окне не будет
	wc.lpszClassName = _T("OpenGL");            // Устанавливаем имя классу
	if (!RegisterClass(&wc))              // Пытаемся зарегистрировать класс окна
	{
		MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Выход и возвращение функцией значения false
	}
	if (fullscreen)                // Полноэкранный режим?
	{
		DEVMODE dmScreenSettings;            // Режим устройства
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));    // Очистка для хранения установок
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // Размер структуры Devmode
		dmScreenSettings.dmPelsWidth = width;        // Ширина экрана
		dmScreenSettings.dmPelsHeight = height;        // Высота экрана
		dmScreenSettings.dmBitsPerPel = bits;        // Глубина цвета
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;// Режим Пикселя
																				 // Пытаемся установить выбранный режим и получить результат.  Примечание: CDS_FULLSCREEN убирает панель управления.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// Если переключение в полноэкранный режим невозможно, будет предложено два варианта: оконный режим или выход.
			if (MessageBox(NULL, L"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				L"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = false;          // Выбор оконного режима (fullscreen = false)
			}
			else
			{
				// Выскакивающее окно, сообщающее пользователю о закрытие окна.
				MessageBox(NULL, L"Program Will Now Close.", L"ERROR", MB_OK | MB_ICONSTOP);
				return false;            // Выход и возвращение функцией false
			}
		}
	}
	if (fullscreen)                  // Мы остались в полноэкранном режиме?
	{
		dwExStyle = WS_EX_APPWINDOW;          // Расширенный стиль окна
		dwStyle = WS_POPUP;            // Обычный стиль окна
		ShowCursor(false);              // Скрыть указатель мышки
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;      // Расширенный стиль окна
		dwStyle = WS_OVERLAPPEDWINDOW;        // Обычный стиль окна
	}
	static TCHAR szTitle[] = _T("Win32");
	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);      // Подбирает окну подходящие размеры
	if (!(hWnd = CreateWindowEx(dwExStyle,          // Расширенный стиль для окна
		_T("OpenGL"),          // Имя класса
		szTitle,            // Заголовок окна
		WS_CLIPSIBLINGS |        // Требуемый стиль для окна
		WS_CLIPCHILDREN |        // Требуемый стиль для окна
		dwStyle,          // Выбираемые стили для окна
		0, 0,            // Позиция окна
		WindowRect.right - WindowRect.left,    // Вычисление подходящей ширины
		WindowRect.bottom - WindowRect.top,    // Вычисление подходящей высоты
		NULL,            // Нет родительского
		NULL,            // Нет меню
		hInstance,          // Дескриптор приложения
		NULL)))          // Не передаём ничего до WM_CREATE (???)
	{
		KillGLWindow();                // Восстановить экран
		MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	static  PIXELFORMATDESCRIPTOR pfd =            // pfd сообщает Windows каким будет вывод на экран каждого пикселя
	{
		sizeof(PIXELFORMATDESCRIPTOR),            // Размер дескриптора данного формата пикселей
		1,                  // Номер версии
		PFD_DRAW_TO_WINDOW |              // Формат для Окна
		PFD_SUPPORT_OPENGL |              // Формат для OpenGL
		PFD_DOUBLEBUFFER,              // Формат для двойного буфера
		PFD_TYPE_RGBA,                // Требуется RGBA формат
		bits,                  // Выбирается бит глубины цвета
		0, 0, 0, 0, 0, 0,              // Игнорирование цветовых битов
		0,                  // Нет буфера прозрачности
		0,                  // Сдвиговый бит игнорируется
		0,                  // Нет буфера накопления
		0, 0, 0, 0,                // Биты накопления игнорируются
		32,                  // 32 битный Z-буфер (буфер глубины)
		0,                  // Нет буфера трафарета
		0,                  // Нет вспомогательных буферов
		PFD_MAIN_PLANE,                // Главный слой рисования
		0,                  // Зарезервировано
		0, 0, 0                  // Маски слоя игнорируются
	};
	if (!(hDC = GetDC(hWnd)))              // Можем ли мы получить Контекст Устройства?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))        // Найден ли подходящий формат пикселя?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))          // Возможно ли установить Формат Пикселя?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!(hRC = wglCreateContext(hDC)))          // Возможно ли установить Контекст Рендеринга?
	{
		KillGLWindow();                // Восстановить экран
		MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	if (!wglMakeCurrent(hDC, hRC))            // Попробовать активировать Контекст Рендеринга
	{
		KillGLWindow();                // Восстановить экран
		MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	ShowWindow(hWnd, SW_SHOW);              // Показать окно
	SetForegroundWindow(hWnd);              // Слегка повысим приоритет
	SetFocus(hWnd);                // Установить фокус клавиатуры на наше окно
	ReSizeGLScene(width, height);              // Настроим перспективу для нашего OpenGL экрана.
	if (!InitGL())                  // Инициализация только что созданного окна
	{
		KillGLWindow();                // Восстановить экран
		MessageBox(NULL, _T("Initialization Failed."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;                // Вернуть false
	}
	return true;                  // Всё в порядке!
}

LRESULT CALLBACK WndProc(HWND  hWnd,            // Дескриптор нужного окна
	UINT  uMsg,            // Сообщение для этого окна
	WPARAM  wParam,            // Дополнительная информация
	LPARAM  lParam)            // Дополнительная информация
{
	switch (uMsg)                // Проверка сообщения для окна
	{
	case WM_ACTIVATE:            // Проверка сообщения активности окна
	{
		if (!HIWORD(wParam))          // Проверить состояние минимизации
		{
			active = true;          // Программа активна
		}
		else
		{
			active = false;          // Программа теперь не активна
		}

		return 0;            // Возвращаемся в цикл обработки сообщений
	}
	case WM_SYSCOMMAND:            // Перехватываем системную команду
	{
		switch (wParam)            // Останавливаем системный вызов
		{
		case SC_SCREENSAVE:        // Пытается ли запустится скринсейвер?
		case SC_MONITORPOWER:        // Пытается ли монитор перейти в режим сбережения энергии?
			return 0;          // Предотвращаем это
		}
		break;              // Выход
	}
	case WM_CLOSE:              // Мы получили сообщение о закрытие?
	{
		PostQuitMessage(0);          // Отправить сообщение о выходе
		return 0;            // Вернуться назад
	}
	case WM_KEYDOWN:            // Была ли нажата кнопка?
	{
		keys[wParam] = true;          // Если так, мы присваиваем этой ячейке true
		return 0;            // Возвращаемся
	}
	case WM_KEYUP:              // Была ли отпущена клавиша?
	{
		keys[wParam] = false;          //  Если так, мы присваиваем этой ячейке false
		return 0;            // Возвращаемся
	}
	case WM_SIZE:              // Изменены размеры OpenGL окна
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // Младшее слово=Width, старшее слово=Height
		return 0;            // Возвращаемся
	}
	}
	// пересылаем все необработанные сообщения DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE  hInstance, // Дескриптор приложения
	HINSTANCE  hPrevInstance, // Дескриптор родительского приложения
	LPSTR    lpCmdLine, // Параметры командной строки
	int    nCmdShow)        // Состояние отображения окна
{
	MSG  msg;              // Структура для хранения сообщения Windows
	BOOL  done = false;            // Логическая переменная для выхода из цикла
								   // Спрашивает пользователя, какой режим экрана он предпочитает

	fullscreen = false;          // Оконный режим

								 // Создать наше OpenGL окно
	static TCHAR name[] = _T("OpenGL");
	if (!CreateGLWindow(name, 320, 240, 32, fullscreen))
	{
		return 0;              // Выйти, если окно не может быть создано
	}
	while (!done)                // Цикл продолжается, пока done не равно true
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))    // Есть ли в очереди какое-нибудь сообщение?
		{
			if (msg.message == WM_QUIT)        // Мы поучили сообщение о выходе?
			{
				done = true;          // Если так, done=true
			}
			else              // Если нет, обрабатывает сообщения
			{
				TranslateMessage(&msg);        // Переводим сообщение
				DispatchMessage(&msg);        // Отсылаем сообщение
			}
		}
		else                // Если нет сообщений
		{
			// Прорисовываем сцену.
			if (active)          // Активна ли программа?
			{
				if (keys[VK_ESCAPE])        // Было ли нажата клавиша ESC?
				{
					done = true;      // ESC говорит об останове выполнения программы
				}
				else            // Не время для выхода, обновим экран.
				{
					DrawGLScene();        // Рисуем сцену
					SwapBuffers(hDC);    // Меняем буфер (двойная буферизация)
				}
			}
			if (keys[VK_F1])          // Была ли нажата F1?
			{
				keys[VK_F1] = false;        // Если так, меняем значение ячейки массива на false
				KillGLWindow();          // Разрушаем текущее окно
				fullscreen = !fullscreen;      // Переключаем режим
											   // Пересоздаём наше OpenGL окно
				if (!CreateGLWindow(_T("NeHe OpenGL структура"), 1024, 768, 32, fullscreen))
				{
					return 0;        // Выходим, если это невозможно
				}
			}
		}
	}

	KillGLWindow();
	return (msg.wParam);
}
