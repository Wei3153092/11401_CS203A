VS Code 設定說明

本文件提供在 Visual Studio Code 中設定 C/C++ 開發環境的步驟，並連線到您的 GitHub 儲存庫，實現無縫的版本控制。

1. 必備擴充功能

請確保您安裝了以下擴充功能：

C/C++ (by Microsoft): 提供 IntelliSense、除錯和程式碼瀏覽。

C/C++ Runner (或 Code Runner): 方便單檔案快速編譯和執行（非必需，但方便）。

GitLens (或內建 Git 支援): 增強 Git 功能。

2. GitHub 儲存庫連線與克隆

開啟終端機 (Terminal): 在 VS Code 中使用 `Ctrl+`` 開啟整合終端機。

克隆儲存庫: 執行您課程提供的命令來克隆您的作業儲存庫：

git clone <repository-url>


開啟資料夾: 在 VS Code 中，使用 檔案 > 開啟資料夾 (File > Open Folder) 並選擇您克隆的 AssignmentIV 所在的目錄。

3. 建構和執行 (使用 Makefile)

我們提供的 Makefile 適用於 Linux/macOS 環境，使用 GCC/G++。

Linux/macOS

開啟終端機 (`Ctrl+``)。

編譯 C 程式:

make $(C_DIR)/c_hash_test
# 或者編譯所有目標:
make all 


執行 C 程式:

make run_c


執行 C++ 程式:

make run_cpp


清理目標檔案:

make clean


Windows (使用 MinGW 或 WSL)

選項一：使用 MinGW (cmd/PowerShell)

在終端機中，執行 Makefile.bat：

.\Makefile.bat


這將編譯並建立 .exe 檔案。您需要手動執行它們：

.\C\c_hash_test.exe
.\CXX\cpp_hash_test.exe


選項二：使用 WSL (推薦)

如果您安裝了 WSL，可以直接在 VS Code 中開啟 WSL 終端機並使用上述的 make 指令。

4. 版本控制與提交

原始控制 (Source Control): 點選左側活動欄中的「原始控制」圖示 (Source Control)。

暫存變更: 在「變更」列表上，點擊 + 號暫存您修改或新增的所有檔案。

撰寫提交訊息: 在頂部輸入欄中輸入您的提交訊息，例如：「開發提交：完成整數雜湊函數實作」。

提交: 點擊「提交」按鈕。

推送到 GitHub: 點擊底部的 同步變更 (Sync Changes) 或在 Git 選單中選擇 推送 (Push) 將您的本地提交同步到遠端儲存庫。