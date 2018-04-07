## NLTK 

### Install
In your bash:
```shell
pip install nltk
python
```
```python
import nltk
nltk.download('stopwords')
nltk.download('punkt')
```

### Usage
```shell
python process.py  -f document [-s save_path] [--lang language]
```
This process.py will create a result.txt at ./ if save\_path is not specified.The defualt language is english.
