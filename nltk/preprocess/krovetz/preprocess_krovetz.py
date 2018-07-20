# coding:utf-8
import argparse

from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from krovetzstemmer import Stemmer # use krovetz for stem

import re # used for cut puncation

parser = argparse.ArgumentParser()
parser.add_argument('-f', default=None, type=str) # specify file path
parser.add_argument('-s', default='.', type=str) # save path
args = parser.parse_args()

def main():
    global args
    save_prefix = args.s

    if args.f is None:
        print('Please specify input file.')
        return
    
    # read file
    with open(args.f, 'r') as f:
        document = f.read()

    # cut puncation
    document = re.sub("[<>:;()\?\.\!\/_,&%^*(+\"\']+", " ", document)

    # stop word list, also can be replaced with to your's list
    stop_word_list = stopwords.words('english')

    # split word, lower word, filter stop word
    s = Stemmer()

    word_list = [s.stem(w.lower()) for w in word_tokenize(text=document) if w not in stop_word_list]

    with open(save_prefix + '/result.txt', 'ab') as f:
        f.write(' '.join(w for w in word_list))

if __name__=='__main__':
    main()
