# YAMotion / MatildaCNC

Редактор G-кода для ЧПУ (Windows, wxWidgets, C++). Продукт называется **MatildaCNC** (matildacnc.com), репозиторий — YAMotion.
Возможности: подсветка и проверка синтаксиса G-кода, симуляция и 3D-отрисовка траектории инструмента,
язык макросов **GCMC** (генерация G-кода программно), диалоги-макросы (вырезание круга, карманы и т.д.), русская локализация.

## Структура

- `src/EditorWx/` — GUI-приложение (wxWidgets + Scintilla/wxSTC, OpenGL).
  - `app.cpp`, `appframe.cpp` — приложение и главное окно; `edit.cpp`, `editorpanel.cpp` — редактор кода;
    `LexGCode.cxx`, `LexGcmc.cxx` — лексеры подсветки (G-код и GCMC), регистрируются в app.cpp.
  - `View3D.cpp` — 3D-просмотр траектории; `executorview.cpp`, `executorlog.cpp` — реализация `IExecutor` для отрисовки/лога.
  - `workingthreads.cpp` — фоновые потоки: `GcmcRunThread` (вызов встроенного компилятора gcmc), проверка и 3D-отрисовка G-кода, симуляция.
  - `macroses.cpp`, `macrosesdlg.cpp`, `macrosparamdlg.cpp` — диалоги макросов по XML-описанию из `macroses/`.
  - `mathexpressiondlg.cpp`, `domath.*`, `muparser/` — калькулятор выражений (muParser вендорен в папку).
  - `flat*.cpp`, `them.*` — самописные «плоские» контролы и темы (black/white); `prefs.*`, `configdata.*` — настройки (JSON, `wxJson`).
    `flatsash.cpp` — разделитель панелей: перетаскивается «вживую» (панели меняют размер вместе с мышью, ничего не рисуется поверх экрана; позиция мыши считается в координатах родителя от снимка геометрии на момент нажатия).
  - `standartpaths.h` — корень ресурсов (`preferences`, `library`, `macroses`, `resources`): текущая папка, если в ней есть `preferences`; иначе папка с exe; иначе до 5 родителей exe (для запуска из `src\x64\Release`).
  - `dirtree.cpp`, `generictreectlg.cpp` — дерево файлов; `CheckUpdate.cpp` — проверка обновлений.
  - `main.cpp` — заглушка-hello, не точка входа (реальная — `app.cpp`).
- `src/Gcode/` — интерпретатор G-кода (на базе кода DynoMotion/KMotion, отсюда `CoordMotion`, `TrajectoryPlanner`, `Kinematics`).
  - `GCodeInterpreter.*`, `cmdparser.cpp`, `arc.cpp`, `straight.cpp`, `cycle.cpp` (циклы сверления), `macrob.cpp`.
  - Интерфейсы: `Iexecutor.h` (что делать: feed/traverse/arc/spindle…), `ienvironment.h` (окружение/настройки), `ilogger.h`.
    Интерпретатор не рисует сам — вызывает `IExecutor`; GUI подставляет свою реализацию.
  - Здесь же функции готовых циклов (cut circle и др., см. `CoordMotion.h`).
- `src/gcmc_vc/` — **gcmc** (G-code meta compiler, B. Stultiens, GPLv3), C, lex/yacc (`grammarl.l`, `grammary.y`). Собирается в статическую библиотеку `gcmc_lib`, встроенную в редактор (и в CLI `gcmc_vc.exe`).
  Компилирует `.gcmc` → G-код. `src/gcmcfont/` — утилита генерации шрифтов для gcmc.
- `library/*.inc.gcmc` — библиотека GCMC (cut_circle, pocket_*, mill_rect, canned_drill, engrave …); `*.tap` — результат компиляции.
- `macroses/` — макросы: `name.xml` (описание аргументов, `name_ru`/`desc_ru` для локализации, функция вызова),
  `name.gcmc` (шаблон), картинки. XML разбирается rapidxml (`src/rapidxml`).
- `Data/` — примеры (`gcmc/`, `gcode/`), `Data/work` — рабочие файлы.
- `preferences/` — JSON настройки и синтаксиса/тем (`*_syntax_*.json`, `them_*.json`), `resources/` — `code_defs.ini` (описания G/M-кодов), `ru/` (локализация).
- `src/po/` — gettext (`messages.pot`, `ru`); см. `src/readme_localization.txt`, скрипты `init_po_ru.bat`, `update_po_ru.bat`, `x_gettext.bat`, `msg_format.bat`.
- `release_pack/` — копия ресурсов для дистрибутива (library, macroses, preferences, resources, Data). **При правке `library/`, `macroses/`, `preferences/` нужно синхронизировать с `release_pack/`.**

## Сборка

- **Быстрый путь (VS Code):** `Ctrl+Shift+B` = `build.ps1` (Release x64 всё решение); задачи в `.vscode/tasks.json` (Build Debug, Rebuild Release, Build gcmc_vc only). `Ctrl+F5` / `F5` запускают выбранную конфигурацию из `.vscode/launch.json` (по умолчанию Release) с `cwd` = корень репозитория, предварительно собирая её.
- `build.ps1 [-Config Release|Debug] [-Target all|editor|gcmc] [-Clean]`: сам находит MSBuild, добавляет `C:\win_flex_bison` в `PATH`, проверяет зависимости, **отказывается собирать, пока запущен `MatildaCNC.exe`** (exe заблокирован — закройте редактор). Файл с BOM: Windows PowerShell 5.1 иначе портит кириллицу.
- Visual Studio, решение `src/EditorWx.sln`: проекты `EditorWx` (→ `MatildaCNC.exe`), `gcmc_lib` (библиотека компилятора), `gcmc_vc` (CLI-обёртка), `gcmcfont_vc`. Конфигурации Win32/x64, Debug/Release.
- Внешние зависимости **вне репозитория** (пути захардкожены в vcxproj):
  - wxWidgets **3.3.4** в `C:\WxWidgets`, собран статически: `cd C:\WxWidgets\build\msw` и `MSBuild wx_vc17.sln -p:Configuration=Release|Debug -p:Platform=x64 -m` → `lib\vc_x64_lib`. Scintilla/Lexilla берутся из `C:\WxWidgets\src\stc\{scintilla,lexilla}` (include-пути прописаны в vcxproj);
  - `glm` на два уровня выше `src` (`C:\Projects\YAMotion\glm`); muparser вендорен в `src/EditorWx/muparser`;
  - win_flex_bison в `C:\win_flex_bison` (для `gcmc_vc`/`gcmcfont_vc`; `custom_build_rules\*.props/.targets` лежат прямо в `custom_build_rules`, и папка должна быть в `PATH` при сборке).
- Тулсет v143: MSBuild из VS 2022 Build Tools (`C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MSBuild.exe`).
  Пример: `$env:PATH="C:\win_flex_bison;$env:PATH"; MSBuild EditorWx\EditorWx.vcxproj -p:Configuration=Release -p:Platform=x64 -p:SolutionDir=<abs>\src\ -m`
  (при сборке отдельного vcxproj `SolutionDir` обязателен). Результат: `src\x64\Release\MatildaCNC.exe`, `src\gcmc_vc\x64\Release\gcmc_vc.exe`.
- **gcmc встроен в редактор** как статическая библиотека `gcmc_lib` (`src/gcmc_vc/gcmc_lib.vcxproj`; flex/bison запускаются только из неё). `gcmc_vc.exe` — тонкая CLI-обёртка (`gcmc_exe_main.c`) над той же библиотекой.
  - API: `gcmc_api.h` → `gcmc_run(argc, argv, &params)` (workdir, колбэк лога, флаг отмены). Работает в отдельном потоке (стек 32 МБ).
  - Всё изменяемое глобальное состояние компилятора помечено `GCMC_TLS` (`__declspec(thread)`), поэтому каждый запуск начинает с чистого состояния. Новую глобальную переменную в `src/gcmc_vc` нужно тоже объявлять с `GCMC_TLS`.
  - `gcmc_alloc.h` (подключается из `config.h` и `grammary.y`) подменяет `malloc/free/strdup`, `fopen/fclose/access`, `exit`, `stderr`: память идёт из приватной кучи (уничтожается после запуска), `exit()` = `longjmp`, `stderr` собирается и отдаётся колбэком, относительные пути считаются от `workdir`. Не вызывайте в этих исходниках `abort()`/аварийные `exit` в обход этого.
  - flex/bison реентерабельны (`%option reentrant bison-bridge`, `%define api.pure full`); указатель сканера — `gcmc_scanner` (thread-local).
  - Редактор: `Worker::RunGcmc` собирает аргументы и запускает `GcmcRunThread` (`workingthreads.cpp`), он вызывает `gcmc_run`. Вывод компилятора идёт по каналу (pipe) и отдаётся колбэку построчно прямо во время работы; колбэк шлёт события `GCMC_RUN_OUTPUT` (текст) и `GCMC_RUN_FINISHED` (код возврата) в `Worker`. Отмена — `GcmcRunThread::Cancel()` (флаг проверяется в начале `interpret()`, код возврата 2).
  - Режим «изолированного процесса» убран: падение внутри компилятора (порча памяти) роняет и редактор; `exit`, ошибки скриптов и зависшие циклы обработаны.
  - Проверка: после правок в `src/gcmc_vc` прогнать `Data/gcmc/*.gcmc` через `gcmc_vc.exe -q --include=library -o out.nc file.gcmc` и сравнить с результатом до правок (побайтно).
- Лексеры GCODE/GCMC (`LexGCode.cxx`, `LexGcmc.cxx`) подключаются через `SetILexer(CreateGcodeLexer()/CreateGcmcLexer())` в `edit.cpp` (wx 3.3: `Catalogue` больше нет).
- Дерево файлов `DirTreeCtrl` наследуется от стандартного `wxGenericTreeCtrl` (wx/generic/treectlg.h) — это нужно для плоских скроллбаров. Старая копия `generictreectlg.cpp/.h` исключена из проекта и не используется.
- `src/postbuild.bat <версия>` — собирает релиз-архивы `MatildaCNCx86_*.zip` / `x64` из `release_pack` и Release-бинарников (нужен 7-Zip).
- Тестов нет. Проверять — сборкой и запуском редактора на примерах из `Data/`.

## Конвенции и нюансы

- Windows-only на практике (`__declspec(thread)`, Win32 API в `gcmc_api.c`, пути, `.bat`/`.ps1`), хотя заявлена кроссплатформенность.
- Не оставляйте в рабочей копии отладочные правки, ломающие функциональность: например, `View3D::OnPaint` с красной заливкой и закомментированной отрисовкой, рисование на рабочем столе через `GetDC(GetDesktopWindow())` в разделителях, `m_faceColour` с жёстким цветом.
- Редактор запускают из корня репозитория (или любым способом: ресурсы ищутся вверх от exe, см. `standartpaths.h`); для проверки как у пользователя — из папки с `release_pack`.
- Исходники местами в UTF-8 с BOM, комментарии частично на русском; сохраняйте кодировку и стиль (табы) файла.
- Строки UI оборачиваются в `_()` для gettext; новые строки — в `.pot`/`ru`.
- `.tap`, `.nc`, `Data/work/*` — генерируемые/рабочие файлы, не править вручную.
- Бинарники `src/*.exe`, `x64/`, `Debug/` — артефакты сборки.
