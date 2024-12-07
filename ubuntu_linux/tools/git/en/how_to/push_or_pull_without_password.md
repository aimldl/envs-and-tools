* Rev.1: 2021-01-09 (Sat)
* Draft: 2020-01-28 (Tue)

## Entering the password every single time is cumbersome
Using [an HTTPS remote URL](https://help.github.com/en/articles/which-remote-url-should-i-use/#cloning-with-https-urls-recommended) has some advantages: it's easier to set up than SSH, and usually works through strict firewalls and proxies. However, it also prompts you to enter your GitHub credentials every time you pull or push a repository. For details, refer to [Why is Git always asking for my password?](https://help.github.com/en/github/using-git/why-is-git-always-asking-for-my-password).

## Caching the password for 15 minutes may mitigate the cumbersomeness.
If you're cloning GitHub repositories using HTTPS, you can use a credential helper to tell Git to remember your GitHub username and password every time it talks to GitHub. Turn on the credential helper so that Git will save your password in memory for some time. By default, Git will cache your password for 15 minutes. For details, refer to [Caching your GitHub password in Git](https://help.github.com/en/github/using-git/caching-your-github-password-in-git).

## How to Skip Typing the ID and Password on git push or git pull Commands
> You can configure Git to store your password for you. If you'd like to set that up, read all about [setting up password caching](https://help.github.com/en/articles/caching-your-github-password-in-git).

How to set up git in order not to enter the ID and password each time is detailed in the following postings. For details, refer to

* [[Skip typing username and password on git push/pull commands](https://stackoverflow.com/questions/36818493/skip-typing-username-and-password-on-git-push-pull-commands)](https://stackoverflow.com/questions/36818493/skip-typing-username-and-password-on-git-push-pull-commands).

* [Asks for username and password each time I want to push and/or pull](https://github.com/microsoft/Git-Credential-Manager-for-Windows/issues/705)

[How to fix Git always asking for user credentials](https://www.freecodecamp.org/news/how-to-fix-git-always-asking-for-user-credentials/)
[Connecting to GitHub with SSH](https://help.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh)

[How do I ensure Git doesn't ask me for my GitHub username and password?](https://superuser.com/questions/199507/how-do-i-ensure-git-doesnt-ask-me-for-my-github-username-and-password)

[How to save username and password in git?](https://stackoverflow.com/questions/35942754/how-to-save-username-and-password-in-git)



Naver search: git 패스워드

[Git 아이디 패스워드 입력 안하는 방법](https://webisfree.com/2017-05-19/git-%EC%95%84%EC%9D%B4%EB%94%94-%ED%8C%A8%EC%8A%A4%EC%9B%8C%EB%93%9C-%EC%9E%85%EB%A0%A5-%EC%95%88%ED%95%98%EB%8A%94-%EB%B0%A9%EB%B2%95)

> Public 레퍼지토리의 경우

[GitHub 아이디/패스워드 입력 없이 사용하는 방법](https://kibua20.tistory.com/88)

> Private 레퍼지토리의 경우