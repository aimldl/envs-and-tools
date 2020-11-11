* Draft: 2020-11-09 (Mon)

## Quick Start Guide





```bash
$ cd ~/github/text_summarization_in_korean/project-extraction_of_korean_news/notebooks
```



> project_root
> ├── README.md
> ├── images
> └── notebooks
>     ├── 2-preliminary_eda.ipynb
>     ├── dataset
>     └── source_codes
>         ├── __pycache__
>         │   └── exploratory_data_analysis.cpython-38.pyc
>         └── exploratory_data_analysis.py

`exploratory_data_analysis.py`에 함수를 정의하고

```python
#!/usr/bin/env python
# exploratory_data_analysis.py

def hello_world():
    print('Hello, world!')
```

`2-preliminary_eda.ipynb`에서 이 함수를 사용하고자 합니다. 이 때

> from directory_name.file_basename import function_name

으로 import합니다. 예를 들면

```jupyter
from source_codes.exploratory_data_analysis import hello_world
hello_world()
```

