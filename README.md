# Python3 C extension module<br>
使用的64位元Python 位於 **C:\Python36** <br>
## Visual Studio Project設定 <br>
* 平台 => x64
* 目標副檔名=> .pyd <br>
* 組態類型  => 動態程式庫(.dll)<br>
* C/C++    => 一般 => 其他Include 目錄 加上 **C:\Python36\include**  (python.h位於此) <br>
* C/C++    => 先行編輯的標頭檔 => 未使用 <br>
* 連結器   => 一般  => 其他程式庫目錄 加上 **C:\Python36\libs** <br>


編譯出來的 Cpp.pyd 拷貝到 Python程式執行目錄,就可以在Python中 import Cpp來使用了. <br>
