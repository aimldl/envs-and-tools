* Draft: 2020-11-12 (Thu)
# 윈도우 10 제품키 찾는 방법 (How to Find My Windows 10 Product Key)
## 개요 (Overview)
### Google search
* keyword: how to check my license key on windows 10
* [How to Find Your Windows 10 Product Key Using the Command Prompt](https://www.howtogeek.com/660517/how-to-find-your-windows-10-product-key-using-the-command-prompt/), howtogeek

커맨드 프롬프트를 이용하는 첫 번째 방법은 실패
```windows
C:\WINDOWS\system32>wmic path SoftwareLicensingService get OA3xOriginalProductKey
OA3xOriginalProductKey



C:\WINDOWS\system32>
```
비주얼 베이직 스크립트를 쓰는 두 번째 방법이 성공.

## 비주얼 베이직 스크립트를 써서 제품키 찾기
### Step 1. 이 파일의 [productkey.vbs](../scripts/productkey.vbs) 내용을 복사해서 윈도우 10의 메모장에 붙입니다.
파일의 내용은 아래와 같습니다.

```
Set WshShell = CreateObject("WScript.Shell")
MsgBox ConvertToKey(WshShell.RegRead("HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\DigitalProductId"))

Function ConvertToKey(Key)
Const KeyOffset = 52
i = 28
Chars = "BCDFGHJKMPQRTVWXY2346789"
Do
Cur = 0
x = 14
Do
Cur = Cur * 256
Cur = Key(x + KeyOffset) + Cur
Key(x + KeyOffset) = (Cur \ 24) And 255
Cur = Cur Mod 24
x = x -1
Loop While x >= 0
i = i -1
KeyOutput = Mid(Chars, Cur + 1, 1) & KeyOutput
If (((29 - i) Mod 6) = 0) And (i <> -1) Then
i = i -1
KeyOutput = "-" & KeyOutput
End If
Loop While i >= 0
ConvertToKey = KeyOutput
End Function
```
### Step 2. 파일명을 `productkey.vbs`으로 파일을 저장합니다.
### Step 3. 파일을 실행하면 윈도우즈 제품번호가 보입니다.
탐색기 (Explorer)에서 `productkey.vbs`를 더블 클릭하면 파일이 실행되며, 팝업창에 제품번호가 보입니다.
### Step 4. Ctrl+C로 내용을 복사해서 제품번호를 저장해놓습니다.
이미지로 화면캡쳐를 하지 않고, 키보드로 `Ctrl+C`키를 누르면 내용이 복사됩니다.
