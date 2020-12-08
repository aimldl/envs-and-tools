* Draft: 2020-12-07 (Mon)

# How to Use BigQuery on Google Cloud





```python
from google.cloud import bigquery

client = bigquery.Client()
```



```bash
---------------------------------------------------------------------------
DefaultCredentialsError                   Traceback (most recent call last)
<ipython-input-3-490cf645c3eb> in <module>()
----> 1 client = bigquery.Client()

5 frames
/usr/local/lib/python3.6/dist-packages/google/auth/_default.py in default(scopes, request)
    319             return credentials, effective_project_id
    320 
--> 321     raise exceptions.DefaultCredentialsError(_HELP_MESSAGE)

DefaultCredentialsError: Could not automatically determine credentials. Please set GOOGLE_APPLICATION_CREDENTIALS or explicitly create credentials and re-run the application. For more information, please see https://cloud.google.com/docs/authentication/getting-started
```



[인증 시작하기](https://cloud.google.com/docs/authentication/getting-started)

우측 상단의 언어를 한국어로 변경하면 한국어 매뉴얼을 볼 수 있습니다.

> ## 서비스 계정 만들기
>
> 
>
> [Cloud Console](https://cloud.google.com/docs/authentication/getting-started#cloud-console)[명령줄](https://cloud.google.com/docs/authentication/getting-started#명령줄)
>
> 1. Cloud Console에서 [서비스 계정 키 만들기](https://console.cloud.google.com/apis/credentials/serviceaccountkey?_ga=2.23775551.44890210.1607330474-1455141047.1607330474&pli=1) 페이지로 이동합니다.
>
> 2. **서비스 계정** 목록에서 **새 서비스 계정**을 선택합니다.
>
> 3. **서비스 계정 이름** 필드에 이름을 입력합니다.
>
> 4. **역할** 목록에서 **프로젝트** > **소유자**.
>
>    
>
>    **참고**: **역할** 필드는 서비스 계정이 프로젝트에서 액세스할 수 있는 리소스에 영향을 줍니다. 이러한 역할을 취소하거나 나중에 추가 역할을 부여할 수 있습니다. 프로덕션 환경에서는 소유자, 편집자 또는 뷰어 역할을 부여하지 마세요. 자세한 내용은 [리소스에 대한 액세스 권한 부여, 변경, 취소](https://cloud.google.com/iam/docs/granting-changing-revoking-access)를 참조하세요.
>
> 5. **만들기**를 클릭합니다. 키가 포함된 JSON 파일이 컴퓨터에 다운로드됩니다.
>
> ## 환경 변수 설정
>
> 서비스 계정을 사용하려면 [환경 변수](https://en.wikipedia.org/wiki/Environment_variable)를 설정해야 합니다.
>
> 
>
> `GOOGLE_APPLICATION_CREDENTIALS` 환경 변수를 설정하여 애플리케이션 코드에 사용자 인증 정보를 제공합니다. [PATH]를 서비스 계정 키가 포함된 JSON 파일의 파일 경로로 바꿉니다. 이 변수는 현재 셸 세션에만 적용되므로 새 세션을 연 경우 변수를 다시 설정합니다.
>
> [Linux 또는 macOS](https://cloud.google.com/docs/authentication/getting-started#linux-또는-macos)[Windows](https://cloud.google.com/docs/authentication/getting-started#windows)
>
> ```sh
> export GOOGLE_APPLICATION_CREDENTIALS="[PATH]"
> ```
>
> 예를 들면 다음과 같습니다.
>
> ```sh
> export GOOGLE_APPLICATION_CREDENTIALS="/home/user/Downloads/my-key.json"
> ```
>
> 환경 변수를 설정하면 배포할 때 애플리케이션 코드를 변경하지 않고도 애플리케이션과 별도로 사용자 인증 정보를 제공할 수 있습니다. 또는 코드에서 서비스 계정 키 파일 경로를 명시적으로 지정할 수 있습니다. 자세한 내용은 [서비스 계정으로 인증](https://cloud.google.com/docs/authentication/production)을 참조하세요.
>
> ## 인증 확인
>
> [환경 변수를 설정](https://cloud.google.com/docs/authentication/getting-started#setting_the_environment_variable)하면 Google Cloud 클라이언트 라이브러리를 사용할 때 코드에 사용자 인증 정보를 명시적으로 지정할 필요가 없습니다. 클라이언트 라이브러리는 암묵적으로 사용자 인증 정보를 확인합니다. 이러한 이유로, 환경 변수를 설정한 후 다음 예시와 같은 클라이언트 라이브러리 코드를 실행하여 인증 작동을 확인할 수 있습니다. 요청이 성공하면 인증이 작동합니다.



