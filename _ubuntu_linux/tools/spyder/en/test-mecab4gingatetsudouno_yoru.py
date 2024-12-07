#! /usr/bin/python3
# -*- coding: utf-8 -*-
'''
packages/mecab/src/test-mecab4gingatetsudouno_yoru.py

* Draft: 2019-12-18(Wed)
* Base code: packages/mecab/src/mecab_basic_usage.py

* Prerequisite
  * Install Python Package MeCab

* Usage:
$ python test-mecab4gingatetsudouno_yoru.py
python	python	python	名詞-固有名詞-組織
が	ガ	が	助詞-格助詞-一般
大好き	ダイスキ	大好き	名詞-形容動詞語幹
です	デス	です	助動詞	特殊・デス	基本形
EOS

$
'''

import MeCab
import pandas as pd

wakati = MeCab.Tagger("-Owakati")
chasen = MeCab.Tagger("-Ochasen")

def tokenize_jp( text ):
    '''
    text
    '銀河鉄道の夜'
    tokens
    ['銀河', '鉄道', 'の', '夜']
    '''
    
    tokens = wakati.parse( text ).split()
    # or 
    #tokens = wakati.parse( text ).strip().split()
    
    return tokens

def formatted_str2list( chasen_output_str ):
    '''
    formatted_str2list reformats a formatted string to a list.
    The size of the string is 1 and it's the output of chasen.parse.
        chasen_output_str = chasen.parse( line )
    
    chasen_output_str
    銀河	ギンガ	銀河	名詞-一般		
    鉄道	テツドウ	鉄道	名詞-一般		
    の	ノ	の	助詞-連体化		
    夜	ヨル	夜	名詞-副詞可能		
    EOS
    
    output_list
    [['銀河', 'ギンガ', '銀河', '名詞-一般', '', ''],
     ['鉄道', 'テツドウ', '鉄道', '名詞-一般', '', ''],
     ['の', 'ノ', 'の', '助詞-連体化', '', ''],
     ['夜', 'ヨル', '夜', '名詞-副詞可能', '', '']]
    '''
    assert isinstance( chasen_output_str, str), "chasen_output_str must be a string"
    
    #print( chasen_output_str )
    #'銀河\tギンガ\t銀河\t名詞-一般\t\t\n鉄道\tテツドウ\t鉄道\t名詞-一般\t\t\nの\tノ\tの\t助詞-連体化\t\t\n夜\tヨル\t夜\t名詞-副詞可能\t\t\nEOS\n'

    output_list = []
    rows = chasen_output_str.split('\n')  # rows=['銀河\tギンガ\t銀河\t名詞-一般\t\t', '鉄道\tテツドウ\t鉄道\t名詞-一般\t\t', 'の\tノ\tの\t助詞-連体化\t\t', '夜\tヨル\t夜\t名詞-副詞可能\t\t', 'EOS', '']
    for row in rows:  # row='銀河\tギンガ\t銀河\t名詞-一般\t\t'
        if row == 'EOS':
            break
        columns = row.split('\t')
        output_list.append( columns )
        
        #print( columns )
        #['銀河', 'ギンガ', '銀河', '名詞-一般', '', '']
    
    return output_list
    #return df
    
#file = "../text_files/clean_gingatetsudouno_yoru.txt"
input_file  = "clean_gingatetsudouno_yoru.txt"
output_file = "gingatetsudouno_yoru.csv"
with open( input_file, 'r', encoding='utf-8' ) as f:
    
    tokens_list_list = []
    for line in f:
        line = line.rstrip()  # Remove the last character or \n.

        tokens_list = tokenize_jp( line )
        tokens_list_list.append( tokens_list )
        
        #line_str  = chasen.parse( line )  # The parsed result is a formatted string.
        #line_list = formatted_str2list( line_str )

df = pd.DataFrame( tokens_list_list )
df.to_csv( output_file )