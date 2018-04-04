# coding:utf-8
import argparse

from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
import nltk.stem

import re # used for cut puncation

parser = argparse.ArgumentParser()
parser.add_argument('--lang', default='english', type=str)
parser.add_argument('-f', default=None, type=str)
parser.add_argument('-s', default='.', type=str)
args = parser.parse_args()

def main():
    global args
    lang = args.lang
    save_prefix = args.s

    if args.f is None:
        print('Please specify input file.')
        return
    
    # read file
    with open(args.f, 'r') as f:
        document = f.read()

    # cut puncation
    document = re.sub("[\.\!\/_,&%^*(+\"\']+", "", document)

    # split word, lower word, filter stop word
    s = nltk.stem.SnowballStemmer(lang)

    word_list = [s.stem(w.lower()) for w in word_tokenize(text=document) if w not in stopwords.words(lang)]

    with open(save_prefix + '/result.txt', 'ab') as f:
        f.write(' '.join(w for w in word_list))

if __name__=='__main__':
    main()
