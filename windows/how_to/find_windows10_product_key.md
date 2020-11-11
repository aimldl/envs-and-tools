* Draft: 2020-11-12 (Thu)
# How to Find My Windows 10 Product Key

## Google search
how to check my license key on windows 10

* [How to Find Your Windows 10 Product Key Using the Command Prompt](https://www.howtogeek.com/660517/how-to-find-your-windows-10-product-key-using-the-command-prompt/), howtogeek
커맨드 프롬프트를 이용하는 첫 번째 방법은 실패
```windows
C:\WINDOWS\system32>wmic path SoftwareLicensingService get OA3xOriginalProductKey
OA3xOriginalProductKey



C:\WINDOWS\system32>
```
비쥬얼 베이직 스크립트를 쓰는 두 번째 방법이 성공.

아래 내용을 텍스트 파일로 저장한 후 실행하면 윈도우즈 제품번호가 보입니다.
파일명: productkey.vbs
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
