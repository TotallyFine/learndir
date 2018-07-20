## PREPROCESS
stop words and puncations filtering, lowercase and lemmatzation with krovetz stemmer, only support english for krovetz stemmer only support english.

### Installation
First install nltk, in your bash:
```shell
pip install nltk
python
```
```python
import nltk
nltk.download('stopwords')
nltk.download('punkt')
```
then install krovetz stemmer, in your bash:
```shell
pip install krovetzstemmer
python
```
```python
from krovetzstemmer import Stemmer
stemmer = Stemmer()
stemmer.stem('utilities')
stemmer.stem(u'utilities')
```

### Usage
```shell
python process.py  -f document_path [-s save_path] 
```
This process.py will create a result.txt at ./ if save\_path is not specified.The defualt language is english.
